#include <stdio.h>

int count_periods(const char *filename)
{
  FILE *fp; 
  int n = 0;
  if((fp = fopen(filename, "r")) != NULL) 
  { while(fgetc(fp) != EOF)
      if(fgetc(fp) == '.')
        n++;
    fclose (fp);
  }
  return n;
}

int main (void)
{
    printf("%d\n", count_periods("file.txt"));
    return 0;
}

