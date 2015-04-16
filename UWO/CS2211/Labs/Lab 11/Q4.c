# include <stdio.h>

struct data
{ int   value_1;
  float value_2;
};

int create_data(const char *filename)
{ FILE *fp;
  struct data my_data[100];
  int i, n = 0;

  for(i=0; i<100; i++)
  { my_data[i].value_1 = i;
    (my_data + i)->value_2 = i;
  }

  if((fp = fopen(filename, "w")) != NULL)
  { n = fwrite(my_data, sizeof(struct data),100, fp);
    fclose (fp);
  }
  return n;
}

int main (void)
{
  printf("%d\n", create_data("file.binary"));
  return 0;
}
