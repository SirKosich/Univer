#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "screensize.h"
#include "center.h"
#include "matrixcalculate.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QScrollArea>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , n(2), k(2), m(2)
{
    ui->setupUi(this);

    // Устанавливаем размер и позицию окна
    int width_screen = Screensize::width() / 2;
    int height_screen = Screensize::height() / 2;
    QPoint center = QPoint(
        qMax(0, (Screensize::width() - width_screen) / 2),
        qMax(0, (Screensize::height() - height_screen) / 2)
        );

    this->setWindowTitle("lab0__safronov_52052 - Калькулятор матриц");
    this->move(center);
    this->resize(width_screen, height_screen);
    this->setMinimumSize(700, 600);

    // Создаём центральный виджет с прокруткой
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *centralWidget = new QWidget(scrollArea);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    scrollArea->setWidget(centralWidget);
    scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);

    // 1. Группа для ввода размеров матриц
    QGroupBox *sizeGroup = new QGroupBox("Размеры матриц");
    QGridLayout *sizeLayout = new QGridLayout(sizeGroup);

    QLabel *labelA = new QLabel("Матрица A (n × k):", sizeGroup);
    spinN = new QSpinBox(sizeGroup);
    spinK = new QSpinBox(sizeGroup);
    QLabel *labelB = new QLabel("Матрица B (k × m):", sizeGroup);
    spinM = new QSpinBox(sizeGroup);

    spinN->setRange(1, 10); spinN->setValue(n);
    spinK->setRange(1, 10); spinK->setValue(k);
    spinM->setRange(1, 10); spinM->setValue(m);

    QPushButton *btnSetSize = new QPushButton("Установить размеры", sizeGroup);

    sizeLayout->addWidget(labelA, 0, 0);
    sizeLayout->addWidget(new QLabel("n:"), 0, 1);
    sizeLayout->addWidget(spinN, 0, 2);
    sizeLayout->addWidget(new QLabel("k:"), 0, 3);
    sizeLayout->addWidget(spinK, 0, 4);
    sizeLayout->addWidget(labelB, 1, 0);
    sizeLayout->addWidget(new QLabel("k:"), 1, 1);
    sizeLayout->addWidget(spinK, 1, 2);
    sizeLayout->addWidget(new QLabel("m:"), 1, 3);
    sizeLayout->addWidget(spinM, 1, 4);
    sizeLayout->addWidget(btnSetSize, 2, 0, 1, 5);

    // 2. Контейнеры для матриц (будут заполняться динамически)
    matrixGroup = new QGroupBox("Ввод матриц");
    matrixLayout = new QHBoxLayout(matrixGroup);

    groupA = new QGroupBox("Матрица A");
    groupB = new QGroupBox("Матрица B");

    scrollA = new QScrollArea(groupA);
    scrollB = new QScrollArea(groupB);

    widgetA = new QWidget(scrollA);
    widgetB = new QWidget(scrollB);

    layoutA = new QGridLayout(widgetA);
    layoutB = new QGridLayout(widgetB);

    scrollA->setWidget(widgetA);
    scrollA->setWidgetResizable(true);
    scrollB->setWidget(widgetB);
    scrollB->setWidgetResizable(true);

    QVBoxLayout *layoutGroupA = new QVBoxLayout(groupA);
    QVBoxLayout *layoutGroupB = new QVBoxLayout(groupB);

    layoutGroupA->addWidget(scrollA);
    layoutGroupB->addWidget(scrollB);

    matrixLayout->addWidget(groupA);
    matrixLayout->addWidget(groupB);

    // 3. Группа для кнопок управления
    QGroupBox *controlGroup = new QGroupBox("Управление");
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);

    btnCalc = new QPushButton("Вычислить A × B");
    btnClear = new QPushButton("Очистить всё");
    btnExample = new QPushButton("Пример");


    btnExportTSV = new QPushButton("Экспорт TSV");
    btnExportXLSX = new QPushButton("Экспорт Excel");

    controlLayout->addWidget(btnCalc);
    controlLayout->addWidget(btnClear);
    controlLayout->addWidget(btnExample);
    controlLayout->addWidget(btnExportTSV);
    controlLayout->addWidget(btnExportXLSX);

    // 4. Группа для отображения результата
    QGroupBox *resultGroup = new QGroupBox("Результат A × B = C");
    QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);

    textResult = new QTextEdit(resultGroup);
    textResult->setReadOnly(true);
    textResult->setMaximumHeight(200);
    resultLayout->addWidget(textResult);

    // 5. Собираем все группы вместе
    mainLayout->addWidget(sizeGroup);
    mainLayout->addWidget(matrixGroup);
    mainLayout->addWidget(controlGroup);
    mainLayout->addWidget(resultGroup);

    // Создаём начальные поля ввода
    updateMatrixInputs();

    // Подключаем сигналы и слоты
    connect(btnSetSize, &QPushButton::clicked, this, &MainWindow::onSetMatrixSize);
    connect(btnCalc, &QPushButton::clicked, this, &MainWindow::onCalculate);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClearAll);
    connect(btnExample, &QPushButton::clicked, this, &MainWindow::onExample);
    connect(btnExportTSV, &QPushButton::clicked, this, &MainWindow::onExportTSV);
    connect(btnExportXLSX, &QPushButton::clicked, this, &MainWindow::onExportXLSX);

    // Инициализируем матрицы
    matrixA = MatrixCalculator::createMatrix(n, k);
    matrixB = MatrixCalculator::createMatrix(k, m);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ОБНОВЛЕНИЕ ПОЛЕЙ ВВОДА ДЛЯ МАТРИЦ
void MainWindow::updateMatrixInputs()
{
    // Очищаем старые поля
    QLayoutItem* item;
    while ((item = layoutA->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    while ((item = layoutB->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Создаём новые поля для матрицы A (n×k)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            QLineEdit *edit = new QLineEdit(widgetA);
            edit->setMaximumWidth(60);
            edit->setMaximumHeight(30);

            // Если значение уже есть в матрице - отображаем его
            if (static_cast<size_t>(i) < matrixA.size() &&
    static_cast<size_t>(j) < matrixA[i].size()) {
                edit->setText(QString::number(matrixA[i][j]));
            } else {
                edit->setText("0");
            }

            layoutA->addWidget(edit, i, j);
        }
    }

    // Создаём новые поля для матрицы B (k×m)
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < m; j++) {
            QLineEdit *edit = new QLineEdit(widgetB);
            edit->setMaximumWidth(60);
            edit->setMaximumHeight(30);

            // Если значение уже есть в матрице - отображаем его
            if (static_cast<size_t>(i) < matrixB.size() &&
    static_cast<size_t>(j) < matrixB[i].size()) {
                edit->setText(QString::number(matrixB[i][j]));
            } else {
                edit->setText("0");
            }

            layoutB->addWidget(edit, i, j);
        }
    }

    // Обновляем размеры контейнеров
    widgetA->adjustSize();
    widgetB->adjustSize();
}

void MainWindow::onSetMatrixSize()
{
    int newN = spinN->value();
    int newK = spinK->value();
    int newM = spinM->value();

    // Сохраняем старые значения (если размеры не менялись - значения сохранятся)
    std::vector<std::vector<int>> oldA = matrixA;
    std::vector<std::vector<int>> oldB = matrixB;

    // Создаём новые матрицы
    matrixA = MatrixCalculator::createMatrix(newN, newK);
    matrixB = MatrixCalculator::createMatrix(newK, newM);

    // Копируем старые значения в новые матрицы (если размеры позволяют)
    int minRows = std::min(newN, static_cast<int>(oldA.size()));
    int minColsA = std::min(newK, static_cast<int>(oldA.empty() ? 0 : oldA[0].size()));

    for (int i = 0; i < minRows; i++) {
        for (int j = 0; j < minColsA; j++) {
            matrixA[i][j] = oldA[i][j];
        }
    }

    int minRowsB = std::min(newK, static_cast<int>(oldB.size()));
    int minColsB = std::min(newM, static_cast<int>(oldB.empty() ? 0 : oldB[0].size()));

    for (int i = 0; i < minRowsB; i++) {
        for (int j = 0; j < minColsB; j++) {
            matrixB[i][j] = oldB[i][j];
        }
    }

    // Обновляем размеры
    n = newN;
    k = newK;
    m = newM;

    // Обновляем поля ввода
    updateMatrixInputs();

    showInfo(QString("Размеры установлены: A(%1×%2), B(%2×%3)").arg(n).arg(k).arg(m));
}

void MainWindow::onCalculate()
{
    // 1. Считываем матрицу A из полей ввода
    matrixA.clear();
    for (int i = 0; i < n; i++) {
        std::vector<int> row;
        for (int j = 0; j < k; j++) {
            QLayoutItem *item = layoutA->itemAtPosition(i, j);
            if (item) {
                QLineEdit *edit = qobject_cast<QLineEdit*>(item->widget());
                if (edit && !edit->text().isEmpty()) {
                    bool ok;
                    int value = edit->text().toInt(&ok);
                    row.push_back(ok ? value : 0);
                } else {
                    row.push_back(0);
                }
            } else {
                row.push_back(0);
            }
        }
        matrixA.push_back(row);
    }

    // 2. Считываем матрицу B
    matrixB.clear();
    for (int i = 0; i < k; i++) {
        std::vector<int> row;
        for (int j = 0; j < m; j++) {
            QLayoutItem *item = layoutB->itemAtPosition(i, j);
            if (item) {
                QLineEdit *edit = qobject_cast<QLineEdit*>(item->widget());
                if (edit && !edit->text().isEmpty()) {
                    bool ok;
                    int value = edit->text().toInt(&ok);
                    row.push_back(ok ? value : 0);
                } else {
                    row.push_back(0);
                }
            } else {
                row.push_back(0);
            }
        }
        matrixB.push_back(row);
    }

    // 3. Проверяем возможность умножения
    if (matrixA.empty() || matrixB.empty()) {
        showError("Матрицы не могут быть пустыми!");
        return;
    }

    if (!MatrixCalculator::canMultiply(matrixA[0].size(), matrixB.size())) {
        showError("Нельзя умножить матрицы: количество столбцов A (" +
                  QString::number(matrixA[0].size()) +
                  ") должно равняться количеству строк B (" +
                  QString::number(matrixB.size()) + ")");
        return;
    }

    // 4. Выполняем умножение
    try {
        matrixC = MatrixCalculator::multiply(matrixA, matrixB);

        // 5. Отображаем результат
        QString result = QString("Результат умножения C (%1×%2):\n")
                             .arg(matrixC.size())
                             .arg(matrixC.empty() ? 0 : matrixC[0].size());
        result += MatrixCalculator::matrixToString(matrixC);

        textResult->setText(result);
        showInfo("Умножение выполнено успешно!");

    } catch (const std::exception& e) {
        showError("Ошибка при умножении матриц: " + QString(e.what()));
    }
}

void MainWindow::onClearAll()
{
    // Очищаем матрицы
    matrixA = MatrixCalculator::createMatrix(n, k, 0);
    matrixB = MatrixCalculator::createMatrix(k, m, 0);
    matrixC.clear();

    // Очищаем поля ввода
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            QLayoutItem *item = layoutA->itemAtPosition(i, j);
            if (item) {
                QLineEdit *edit = qobject_cast<QLineEdit*>(item->widget());
                if (edit) edit->setText("0");
            }
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < m; j++) {
            QLayoutItem *item = layoutB->itemAtPosition(i, j);
            if (item) {
                QLineEdit *edit = qobject_cast<QLineEdit*>(item->widget());
                if (edit) edit->setText("0");
            }
        }
    }

    textResult->clear();
    showInfo("Все поля очищены");
}

void MainWindow::onExample()
{
    // Пример матриц 3×3 и 3×2
    spinN->setValue(3);
    spinK->setValue(3);
    spinM->setValue(2);

    onSetMatrixSize();

    // Заполняем примером
    matrixA = {{1, 2, 3},
               {4, 5, 6},
               {7, 8, 9}};

    matrixB = {{1, 0},
               {0, 1},
               {1, 1}};

    // Отображаем в полях ввода
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QLayoutItem *item = layoutA->itemAtPosition(i, j);
            if (item) {
                QLineEdit *edit = qobject_cast<QLineEdit*>(item->widget());
                if (edit && static_cast<size_t>(i) < matrixA.size() &&
    static_cast<size_t>(j) < matrixA[i].size()) {
                    edit->setText(QString::number(matrixA[i][j]));
                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            QLayoutItem *item = layoutB->itemAtPosition(i, j);
            if (item) {
                QLineEdit *edit = qobject_cast<QLineEdit*>(item->widget());
                if (edit && static_cast<size_t>(i) < matrixB.size() &&
    static_cast<size_t>(j) < matrixB[i].size()) {
                    edit->setText(QString::number(matrixB[i][j]));
                }
            }
        }
    }

    showInfo("Загружен пример: матрицы 3×3 и 3×2");
}

void MainWindow::showError(const QString& message)
{
    QMessageBox::critical(this, "Ошибка", message);
}

void MainWindow::showInfo(const QString& message)
{
    QMessageBox::information(this, "Информация", message);
}

// ЭКСПОРТ В TSV (Tab-Separated Values) - самый простой
void MainWindow::onExportTSV()
{
    if (matrixC.empty()) {
        showError("Нет данных для экспорта! Сначала вычислите матрицу.");
        return;
    }

    // Диалог выбора файла
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Сохранить как TSV",
                                                    QDir::homePath() + "/матрица_результат.tsv",
                                                    "TSV файлы (*.tsv);;Все файлы (*)");

    if (filename.isEmpty()) return;

    // Если не указано расширение, добавляем .tsv
    if (!filename.endsWith(".tsv", Qt::CaseInsensitive)) {
        filename += ".tsv";
    }

    if (exportToTSV(filename)) {
        showInfo("Матрица успешно экспортирована в:\n" + filename);
    }
}

// ЭКСПОРТ В XLSX (Excel)
void MainWindow::onExportXLSX()
{
    if (matrixC.empty()) {
        showError("Нет данных для экспорта! Сначала вычислите матрицу.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Сохранить как Excel",
                                                    QDir::homePath() + "/матрица_результат.xlsx",
                                                    "Excel файлы (*.xlsx);;Все файлы (*)");

    if (filename.isEmpty()) return;

    if (!filename.endsWith(".xlsx", Qt::CaseInsensitive)) {
        filename += ".xlsx";
    }

    // Пробуем экспорт в XLSX, если не получается - используем TSV
    if (exportToXLSX(filename)) {
        showInfo("Матрица успешно экспортирована в Excel:\n" + filename);
    } else {
        // Если XLSX не поддерживается, предлагаем TSV
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Библиотека не найдена",
                                      "Библиотека QtXlsx не установлена. Экспортировать в TSV?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            filename.replace(".xlsx", ".tsv");
            if (exportToTSV(filename)) {
                showInfo("Матрица экспортирована в TSV:\n" + filename);
            }
        }
    }
}

// РЕАЛИЗАЦИЯ ЭКСПОРТА В TSV
bool MainWindow::exportToTSV(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        showError("Не удалось создать файл: " + filename);
        return false;
    }

    QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    out.setCodec("UTF-8");  // Для Qt5
#else
    out.setEncoding(QStringConverter::Utf8);  // Для Qt6
#endif

    // Записываем матрицу C
    for (const auto& row : matrixC) {
        for (size_t j = 0; j < row.size(); j++) {
            out << row[j];
            if (j < row.size() - 1) {
                out << "\t";  // Табуляция как разделитель
            }
        }
        out << "\n";
    }

    file.close();
    return true;
}

bool MainWindow::exportToCSV(const QString& filename)
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            showError("Не удалось создать файл: " + filename);
            return false;
        }

        QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        out.setCodec("UTF-8");  // Для Qt5
#else
        out.setEncoding(QStringConverter::Utf8);  // Для Qt6
#endif

        // Записываем матрицу C
        for (const auto& row : matrixC) {
            for (size_t j = 0; j < row.size(); j++) {
                out << row[j];
                if (j < row.size() - 1) {
                    out << ",";  // Запятая как разделитель
                }
            }
            out << "\n";
        }

        file.close();
        return true;
    }

// РЕАЛИЗАЦИЯ ЭКСПОРТА В XLSX (с QtXlsx)
bool MainWindow::exportToXLSX(const QString& filename)
{
    // Вместо XLSX сохраняем как TSV (Excel откроет)
    QString tsvFilename = filename;
    tsvFilename.replace(".xlsx", ".tsv");

    return exportToTSV(tsvFilename);  // Сохраняем как TSV
}
