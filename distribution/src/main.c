#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "main.h"
#include "const.h"
#include "tad.h"
#include "traffic.h"
#include "allocation.h"


void foo(char **s) {
  printf("Hello world %s %s!\n", s[0], s[1]);
}

int main(int argc, char** argv)
{
  (void)argc;
  struct data_c* data;
  struct link* link;
  int alloc[2] = {0};
  int nb_sim = 0;
  int i = 1;
  int j = 0;
  int nb_vn = 0;
  int capacity = 0;
  int sim_number = 0;
  float rate = 0.0;
  float admit_rate = 0.0;
  float min_flow1 = 0.0;
  float min_flow2 = 0.0;
  float mean_trans_lost1 = 0.0;
  float mean_data_lost1 = 0.0;
  float mean_trans_lost2 = 0.0;
  float mean_data_lost2 = 0.0;
  char tmp[SIZE] = "";
  FILE* file;
  FILE* file2;

  nb_sim = atoi(argv[1]);
  rate = atof(argv[2]);
  nb_vn = atoi(argv[3]);
  capacity = atoi(argv[4]);
  admit_rate = atof(argv[5]);
  min_flow1 = atof(argv[6]);
  min_flow2 = atof(argv[7]);
  sim_number = atoi(argv[8]);

  if((file = fopen("measure.dat", "a+")) == NULL)
    {
      perror("fopen");
      return EXIT_FAILURE;
    }

  data = data_c_create(capacity);
  link = link_create(nb_vn, capacity);
  allocation(link, rate, alloc, nb_vn, capacity);

  
  for(i = 1; i <= nb_sim; i++)
    {
      sprintf(tmp,"sim_%d.dat", i);
      if((file2 = fopen(tmp, "w+")) == NULL)
	{
	  perror("fopen");
	  return EXIT_FAILURE;
	}

      traffic(data, link, alloc, admit_rate, min_flow1, min_flow2, nb_vn, capacity);
      
      for(j = 0; j < alloc[0]; j++)
	{
	  sprintf(tmp,"%d %f %f %f %f\n", j, data->occ[j], data->prob[j], data->occ2[j], data->prob2[j]);
	  fprintf(file2, tmp);
	}
      mean_trans_lost1 += data->transmission_lost1;
      mean_data_lost1 +=  data->data_lost1;
      mean_trans_lost2 += data->transmission_lost2;
      mean_data_lost2 +=  data->data_lost2;
      fclose(file2);
    }
  printf("\n--->Transmission mean lost 1 = %f || Transmission mean lost 2 = %f\n", mean_trans_lost1, mean_trans_lost2);
  printf("--->Data mean lost 1 = %f || Data mean lost 2 = %f\n", mean_data_lost1, mean_data_lost2);

  sprintf(tmp,"%d %f %f\n", sim_number, mean_data_lost1, mean_data_lost2); 
  fprintf(file, tmp);
  
  link_clear(link, nb_vn);
  data_c_clear(data);
  fclose(file);

  return EXIT_SUCCESS;
}

