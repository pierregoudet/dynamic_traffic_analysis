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
  int i = 0;
  int j = 0;
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
 
  if((file = fopen(argv[3], "a+")) == NULL)
    {
      perror("fopen");
      return EXIT_FAILURE;
    }

 

  sim = atoi(argv[1]);

  data = data_c_create();
  link = link_create();
   
  allocation(link, atof(argv[2]), alloc);

  for(i = 0; i < sim; i++)
   { 
     traffic(data, link, alloc);
     mean_lost1 = data->transmission_lost1 + mean_lost1;
     mean_lost2 = data->transmission_lost2 + mean_lost2;
     data_lost1 = data->data_lost1 + data_lost1;
     data_lost2 = data->data_lost2 + data_lost2;
     printf("----->simulation %s %d\n", argv[4], i);

     sprintf(tmp, "%s_%d.dat",argv[4], i);

     if((file2 = fopen(tmp, "w+")) == NULL)
       {
     	 perror("fopen");
     	 return EXIT_FAILURE;
       }
     for(j = 0; j < alloc[0]; j++)
       {
      	  sprintf(tmp, "%d %f %f %f %f \n",j ,data->prob[j], data->occ[j], data->prob2[j], data->occ2[j]);
      	  fprintf(file2, tmp);
       }
      fclose(file2);
   } 
  
  
  data_lost1 = data_lost1 / sim;
  data_lost2 = data_lost2 / sim;
  printf("\n mean data lost1 : %f percent (flow scale = %f ~ 1.0) | mean data lost2 : %f percent (flow scale = %f ~ 1.0)\n", data_lost1, (1 - MIN_FLOW1), data_lost2, (1 - MIN_FLOW2));


  mean_lost1 = mean_lost1*100 / sim;
  mean_lost2 = mean_lost2*100 / sim;  
  printf("\n mean transmission lost1 : %f percent (flow scale = %f ~ 1.0) | mean transmission lost2 : %f percent (flow scale = %f ~ 1.0)\n", mean_lost1, (1 - MIN_FLOW1), mean_lost2, (1 - MIN_FLOW2));

 
  sprintf(tmp,"%s %f %f\n", argv[4], mean_lost1, mean_lost2);
  fprintf(file, tmp);

  printf("alloc[0] = %d, alloc[1] = %d\n", alloc[0], alloc[1]);

  link_clear(link);
  data_c_clear(data);
  fclose(file);
  return EXIT_SUCCESS;
}
