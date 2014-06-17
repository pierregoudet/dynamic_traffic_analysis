#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "const.h"
#include "calc_prob.h"
#include "tad.h"

int main (int argc, char **argv)
{
  FILE* f;
  FILE* f2;
  int sum = 0;
  int i = 0;
  int j = 0;
  int k = 1;
  int a = 1;
  int b = 1;
  int OMEGA = 0;
  int borne_inf = 0;
  int borne_sup = 0; 
  float info = 0.0;
  float mean = 0.0;
  float esp = 0.0;
  float esp_sq = 0.0;
  float var1 = 0.0;
  float sum_dev = 0.0;
   float dev = 0.0;
  char tmp[SIZE];
  
  if(argc != 3)
    {
      fprintf(stderr,"Please enter two data file as argument\n");
      return EXIT_SUCCESS;
    }
  
  if((f = fopen(argv[1], "w+")) == NULL)
    {
      perror("fopen");
    }
  
  if((f2 = fopen(argv[2], "w+")) == NULL)
    {
      perror("fopen");
    }
 
  time_t t;
  srand((unsigned) time(&t));
  
  struct data_c* data;
  struct link* link;
  
  data =  data_c_create();
  link = link_create();

  /* for(k = 1; k <= 200; k++) */
  /* { */
  /*   a = k; */
  /*   b= 10; */
  /* init_link_lin(link, a, b); */

   init_link_rand(link);
  
  OMEGA = 0;
  
    for(i = 0; i < NB_VN; i++)
      {
	OMEGA += link->link[i]->max_flow;
      }
    printf("---> Reserved (max traffic) : %d\n", OMEGA);
    
    
  
    for(i = 0; i < TIME -1; i++)
      {
	sprintf(tmp, "%d ", i);
	for(j = 0; j < NB_VN - 1; j++)
	  {
	    link->link[j]->flow = rand() % link->link[j]->max_flow ;
	    sum = sum + link->link[j]->flow;
	  }

	data->mes[i] = sum;
	data->occ[sum] = data->occ[sum] + 1;
	sum = 0;
      }

    /*--- Calculation part ---*/
    for(i = 0; i < OMEGA; i++)
      {
	data->prob[i] = (float)data->occ[i] / TIME;
	sprintf(tmp,"%d %f\n", i, data->prob[i]);
	fprintf(f, tmp);
      }  
 
    mean = calc_mean(data->mes, OMEGA);
    esp = calc_esp(data->prob, OMEGA);
    esp_sq = calc_esp_square(data->prob, OMEGA);

    data->var = esp_sq - esp*esp;
    data->std_dev = sqrt(data->var);
    
    for(i = 0; i < TIME; i++)
      {
	sum_dev += (data->mes[i] - mean)*(data->mes[i] - mean);
      }
    var1 = sum_dev / TIME;
    
    printf("--->%f esp --- %f mean --- %f var / %f --- standard deviation %f\n", esp, mean, data->var, var1, data->std_dev);
  


    borne_sup = (mean - data->std_dev);
    borne_sup = (mean + data->std_dev);
    info = 0;
    for(i = borne_inf; i <= borne_sup; i++)
      {
	info += data->prob[i];
      }
    printf("---> mean - std_dev = %f (should be ~=68) \n", info);


    borne_inf = (mean - 2*data->std_dev);
    borne_sup = (mean + 2*data->std_dev);
    info = 0;

    for(i = borne_inf; i <= borne_sup; i++)
      {
	info += data->prob[i];
      }
    printf("---> mean - 2*std_dev = %f (should be ~=95) \n", info);


    borne_inf = (mean - 3*data->std_dev);
    borne_sup = (mean + 3*data->std_dev); 
    info = 0;
    for(i = borne_inf; i <= borne_sup; i++)
      {
	info += data->prob[i];
      }
    printf("---> mean - 3*std_dev = %f (should be ~=99,7) \n", info);
    
   /*  dev = 0; */
  /*   dev = OMEGA - mean; */
  /*   printf("---> OMEGA %d --- dev %f --- k %d\n", OMEGA, dev, k); */
    
  /*   sprintf(tmp,"%d %f\n", OMEGA, dev); */
  /*   fprintf(f2, tmp); */
  /* } */

  fclose(f);
  fclose(f2);
  link_clear(link);
  data_c_clear(data);
  return EXIT_SUCCESS;
}
