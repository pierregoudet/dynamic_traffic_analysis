#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "const.h"
#include "calc_prob.h"
#include "tad.h"
#include "traffic.h"



void simulation(struct data_c* data, struct link* link)
{
  int i = 0;
  int j = 0;
  int sum = 0;
  int sum2 = 0;
  for(i = 0; i <= TIME -1; i++)
    {
      for(j = 0; j < NB_VN - 1; j++)
	{
	  link->link[j]->flow = rand() % (link->link[j]->max_flow);
	  sum = sum + link->link[j]->flow;
	}
      
      for(j = 0; j < NB_VN - 1; j++)
      	  {
      	    link->link[j]->flow = (rand() % (link->link[j]->max_flow * 4/5)) + link->link[j]->max_flow * 1/5;
      	    sum2 = sum2 + link->link[j]->flow;
	  } 
      
	data->mes[i] = sum;
	data->occ[sum] = data->occ[sum] + 1;
	sum = 0;
	
	data->mes2[i] = sum2;
	data->occ2[sum2] = data->occ2[sum2] + 1;
	sum2 = 0;
      }
}


void cmp_gaus(int mean, float std_dev, float* prob)
{
  int i = 0;
  float info = 0.0;

  int borne_inf = 0;
  int borne_sup = 0;
  
  borne_inf = (mean - std_dev);
  borne_sup = (mean + std_dev);
  for(i = borne_inf; i <= borne_sup; i++)
    {
      info += prob[i];
    }

  printf("---> mean - std_dev = %f : distribution --- (gaussian ~= 68 percent) \n", info);
    
  borne_inf = (mean - 2*std_dev);
  borne_sup = (mean + 2*std_dev);
  info = 0;
  for(i = borne_inf; i <= borne_sup; i++)
    {
      info += prob[i];
    }
  printf("---> mean - 2*std_dev = %f : distribution --- (gaussian ~= 95 percent) \n", info);


  borne_inf = (mean - 3*std_dev);
  borne_sup = (mean + 3*std_dev);
  info = 0;

  for(i = borne_inf; i <= borne_sup; i++)
    {
      info += prob[i];
    }
  printf("---> mean - 3*std_dev = %f : distribution (gaussian ~= 99,7 percent) \n", info);
}



void traffic(int nb_file, char** file)
{
  FILE* f;
  FILE* f2;
  int i = 0;
  int OMEGA = 0;
  float seuil = 0;
  float sum_occ = 0;
  float sum_occ2 = 0;
  float sum_prob = 0.0;
  float sum_prob2 = 0.0;
  float mean = 0.0;
  float esp = 0.0;
  float esp_sq = 0.0;
  float var1 = 0.0;
  float act_u = 1.0;
  char tmp[SIZE];
  
  if(nb_file != 3)
    {
      fprintf(stderr,"Please enter two data file as argument\n");
      exit(EXIT_FAILURE);
    }
  
  if((f = fopen(file[1], "w+")) == NULL)
    {
      perror("fopen");
    }
  
  if((f2 = fopen(file[2], "w+")) == NULL)
    {
      perror("fopen");
    }
 
  time_t t;
  srand((unsigned) time(&t));
  
  struct data_c* data;
  struct link* link;
  
  data =  data_c_create();
  link = link_create();

  /* int j = 0; */
  /* int a = 1; */
  /* int b = 1; */
  /* float dev = 0.0; */
  /* for(k = 1; k <= 200; k++) */
  /* { */
  /*   a = k; */
  /*   b= 10; */
  /* init_link_lin(link, a, b); */

  init_link_rand(link);
   
  OMEGA = 0;
  
  for(i = 0; i < NB_VN; i++)
    {
      OMEGA = link->link[i]->max_flow + OMEGA;
    }
  printf("---> Reserved (max traffic) : %d\n", OMEGA);
        
  simulation(data, link);

  /*--- Calculation part ---*/
  for(i = 0; i < OMEGA; i++)
    {
      data->prob[i] = data->occ[i] / TIME;
      sum_prob += data->prob[i];
      data->prob2[i] = data->occ2[i] / TIME;
      sum_prob2 += data->prob2[i];
      sum_occ += data->occ[i];
      sum_occ2 += data->occ2[i];
      sprintf(tmp,"%d %f %f\n", i, data->prob[i], data->prob2[i]);
      fprintf(f, tmp);
    }    
  printf("---> %f sum of prob (shoudld be ~= 1) )\n", sum_prob);
  printf("---> %f sum of prob2 (shoudld be ~= 1) \n", sum_prob2);
    
    mean = calc_mean(data->mes, OMEGA);
    esp = calc_esp(data->prob, OMEGA);
    esp_sq = calc_esp_square(data->prob, OMEGA);
    data->var = esp_sq - esp*esp;  
    
    printf("\n----- FROM 0 to MAX_FLOW -----\n");
    
    var1 = calc_variance_esp(data->mes, mean);
    data->std_dev = sqrt(var1);
    printf("--->%f esp --- %f mean --- %f var / %f --- standard deviation %f\n", esp, mean, data->var, var1, data->std_dev);

    cmp_gaus(mean, data->std_dev, data->prob);
      
    seuil = calc_alloc(data->prob, OMEGA, sum_prob*99);
    act_u = seuil * 100 / OMEGA;
    printf("---> %f percent used for %f percent data\n", act_u, sum_prob*0.90);
    
    printf("\n----- FORM MAX_FLOW/10 to MAX_FLOW -----\n");
    
    mean = calc_mean(data->mes2, OMEGA);
    esp = calc_esp(data->prob2, OMEGA);
    esp_sq = calc_esp_square(data->prob2, OMEGA);
    data->var2 = esp_sq - esp*esp;  
    
    var1 = calc_variance_esp(data->mes2, mean);
    data->std_dev2 = sqrt(var1);
    printf("--->%f esp --- %f mean --- %f var / %f --- standard deviation %f\n", esp, mean, data->var2, var1, data->std_dev2);

    cmp_gaus(mean, data->std_dev2, data->prob2);
      
    seuil = 0;
    seuil = calc_alloc(data->prob2, OMEGA, sum_prob2*0.99);
    act_u = seuil * 100 / OMEGA;
    printf("---> %f percent used for %f percent data\n", act_u, sum_prob2*90);
    
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
}
