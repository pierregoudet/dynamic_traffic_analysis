#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "const.h"
#include "tad.h"
#include "traffic.h"
#include "allocation.h"


int main(int argc, char** argv)
{
  int sim;
  int i;
  int alloc[2] = {0};
  float mean_lost1 = 0.0;
  float data_lost1 = 0.0;
  float data_lost2 = 0.0;
  float mean_lost2 = 0.0;

  char tmp[SIZE];
  FILE* file;
  FILE* file2;
  struct data_c* data;
  struct link* link;
  
  printf("alloc[0] = %d, alloc[1] = %d\n", alloc[0], alloc[1]); 
 
  if((file = fopen(argv[3], "a+")) == NULL)
    {
      perror("fopen");
      return EXIT_FAILURE;
    }

  if((file2 = fopen(argv[4], "w+")) == NULL)
    {
      perror("fopen");
      return EXIT_FAILURE;
    }

  sim = atoi(argv[1]);
  data = data_c_create();
  link = link_create();
   
  allocation(link, atof(argv[2]), alloc);

  for(i = 1; i <= sim; i ++)
    {
      traffic(data, link, alloc);
      mean_lost1 = data->transmission_lost1 + mean_lost1;
      mean_lost2 = data->transmission_lost2 + mean_lost2;
      data_lost1 = data->data_lost1 + data_lost1;
      data_lost2 = data->data_lost2 + data_lost2;
    }
 
  
  data_lost1 = data_lost1 / sim;
  data_lost2 = data_lost2 / sim;
  printf("\n mean data lost1 : %f percent (flow scale = %f ~ 1.0) | mean data lost2 : %f percent (flow scale = %f ~ 1.0)\n", data_lost1, (1 - MIN_FLOW1), data_lost2, (1 - MIN_FLOW2));


  mean_lost1 = mean_lost1*100 / sim;
  mean_lost2 = mean_lost2*100 / sim;  
  printf("\n mean transmission lost1 : %f percent (flow scale = %f ~ 1.0) | mean transmission lost2 : %f percent (flow scale = %f ~ 1.0)\n", mean_lost1, (1 - MIN_FLOW1), mean_lost2, (1 - MIN_FLOW2));

 
  sprintf(tmp,"%s %f %f\n", argv[5], mean_lost1, mean_lost2);
  fprintf(file, tmp);


  for(i = 0; i < alloc[0]; i++)
    {
      sprintf(tmp,"%d %f %f\n",i ,data->prob[i], data->prob2[i]);
      fprintf(file2, tmp);
    }
  
  printf("alloc[0] = %d, alloc[1] = %d\n", alloc[0], alloc[1]);

  data_c_clear(data);
  link_clear(link);
  fclose(file);
  fclose(file2);
  return EXIT_SUCCESS;
}
