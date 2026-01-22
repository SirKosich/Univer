#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
#if 0
  FILE *cmd=popen("seq 4 10", "r");
  char result[24]={0x0};
  while (fgets(result, sizeof(result), cmd) !=NULL)
    printf("%s\n", result);
  pclose(cmd);
#endif


  char *fname = "filename.fname";
  char *str;
  int a;

  str = malloc(sizeof(char) * 160);
  for(int cnt = 10; cnt < 30; cnt++) {
    sprintf(str,"seq %d %d > %s", cnt, cnt, fname);
    printf("+%s\n", str);
    system(str);
    FILE *f = fopen(fname, "r");
    fgets(str, sizeof(char) * 160, f);
    sscanf(str, "%d", &a);
    printf("number is %d\n", a);
    fclose(f);
  }
  return 0;
}


// "seq " "4 20" " > out.dat"
