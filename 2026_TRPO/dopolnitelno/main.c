#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int c, char ** v) {
  
#if 0
  if(c <= 1)
    return 0;

  int a = -RAND_MAX, b=0, ck=0,dk=0, beg=0,step=0,end=0;
  double arg=0;
  //Парсинг
  for(int d = 1; d < c; d++) {
    if(v[d][0] == '-')
      if(strcmp(v[d],"-a") == 0)
	{
	  a = 1;
	}
      else if(strcmp(v[d],"-b") == 0)
	{
	  sscanf(v[++d],"%d", &b);
	}
      else if(v[d][1] == 'c')
	{
	  sscanf(v[d],"-c:%d", &ck);
	}
      else if(v[d][1] == 'd')
	{
	  sscanf(v[d],"-d=%d", &dk);	  
	}
      else if(strcmp(v[d],"-e") == 0)
	{
	  sscanf(v[++d],"%d:%d:%d", &beg,&step,&end);	  
	}
      else
	{
	}
    else if(v[d][0]>47 && v[d][0] < 58)
      {
	printf("qwe %s\n", v[d]);
	sscanf(v[d],"%lg",&arg);
      }
    else
      printf("Хрень\n");
  }
  //Конец парсинга


  printf("a?: %d\n b=%d\n c=%d\n d=%d\n e=\n start=%d step=%d end=%d\n arg=%f\n", a,b,ck,dk,beg,step,end, arg);
#else
  long a;
  for(a = 1; a>=0;a*=2)
    printf("%ld %d\n",a-1, RAND_MAX+1);
  printf("%ld\n", 0x7fffffffffffffff);
#endif
  return 0;
}


#if 0
./a.out -a -b 3 2 1 -c:4 -d=0 -e 1:2:3
#endif
