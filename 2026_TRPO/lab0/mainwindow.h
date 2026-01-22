#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QGridLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QPushButton>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSetMatrixSize();
    void onCalculate();
    void onClearAll();
    void onExample();
    void onExportTSV();   // Экспорт в TSV
    void onExportXLSX();  // Экспорт в XLSX (на самом деле TSV)

private:
    Ui::MainWindow *ui;

    // Матрицы
    std::vector<std::vector<int>> matrixA;
    std::vector<std::vector<int>> matrixB;
    std::vector<std::vector<int>> matrixC;

    // Размеры матриц
    int n, k, m;

    // Виджеты для интерфейса
    QSpinBox *spinN;
    QSpinBox *spinK;
    QSpinBox *spinM;
    QPushButton *btnCalc;
    QPushButton *btnClear;
    QPushButton *btnExample;
    QPushButton *btnExportTSV;
    QPushButton *btnExportXLSX;
    QTextEdit *textResult;

    // Контейнеры для матриц
    QGroupBox *matrixGroup;
    QGroupBox *groupA;
    QGroupBox *groupB;
    QHBoxLayout *matrixLayout;
    QScrollArea *scrollA;
    QScrollArea *scrollB;
    QWidget *widgetA;
    QWidget *widgetB;
    QGridLayout *layoutA;
    QGridLayout *layoutB;

    // Методы
    void updateMatrixInputs();
    void showError(const QString& message);
    void showInfo(const QString& message);
    bool exportToTSV(const QString& filename);   // Экспорт в TSV
    bool exportToXLSX(const QString& filename);  // Экспорт в XLSX (будет TSV)
    bool exportToCSV(const QString& filename);   // Экспорт в CSV - ТОЛЬКО ОДНА ФУНКЦИЯ!
};

#endif // MAINWINDOW_H
