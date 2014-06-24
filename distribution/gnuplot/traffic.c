#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "const.h"
#include "calc_prob.h"
#include "tad.h"
#include "traffic.h"
#include "test_struct.h"

void simulation(struct data_c* data, struct link* link)

{
  int i = 0;
  int j = 0;
  int scale_flow = 0.0;
  int safe_flow = 0.0;
  int sum = 0;
  int sum2 = 0;
  
 

  time_t t;
  unsigned int seed = 0;
  /* FILE* fp; */
  /* fp = fopen("/dev/random", "r"); */
  /* fread(&seed, sizeof(int), 1, fp); */
  /* fclose(fp); */

  seed = time(&t);
  srand(seed); 
  sleep(1);
  
  init_data_c(data);
  //test_data_c();
  
  for(i = 0; i < TIME; i++)
    {          
      for(j = 0; j < NB_VN; j++)
	{
	  scale_flow = link->link[j]->max_flow * MIN_FLOW1;
	  safe_flow =  link->link[j]->max_flow * (1.0 - MIN_FLOW1);
	  link->link[j]->flow = (rand() % scale_flow) + safe_flow;
	  sum = sum + link->link[j]->flow;
	} 
      

      for(j = 0; j < NB_VN; j++)
	{
	  scale_flow = link->link[j]->max_flow * MIN_FLOW2;
	  safe_flow =  link->link[j]->max_flow * (1.0 - MIN_FLOW2);
	  link->link[j]->flow = (rand() % scale_flow) + safe_flow;
	  sum2 = sum2 + link->link[j]->flow;
	} 
      
      data->mes[i] = sum;
      data->nb_data1 = sum + data->nb_data1;
      data->occ[sum] = data->occ[sum] + 1;
      sum = 0;
      
      data->mes2[i] = sum2;
      data->nb_data2 = sum2 + data->nb_data2;
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


float data_lost(float* mes, int* alloc)
{
  int i = 0;
  float data_lost = 0.0;

  for(i = 0; i < TIME; i++)
    {
      if(mes[i] > alloc[1])
	{
	  data_lost = mes[i] + data_lost;
	}
    }
  return data_lost;
}


void traffic(struct data_c* data, struct link* link, int* alloc)
{
  int i = 0;
  int OMEGA = 0;
  float seuil = 0;
  float sum_prob = 0;
  float sum_prob2 = 0;
  float mean = 0.0;
  float esp = 0.0;
  float esp_sq = 0.0;
  float var1 = 0.0;
  float act_u = 0.0;


  OMEGA = alloc[0]; 
   
  printf("\n---> Requested (max traffic) : %d  (OMEGA %d)--- Allocated : %d\n", alloc[0], OMEGA, alloc[1]);
   
  simulation(data, link);


  for(i = 0; i < OMEGA; i++)
    {
      data->prob[i] = data->occ[i] / TIME;
      sum_prob += data->prob[i];
      data->prob2[i] = data->occ2[i] / TIME;
      sum_prob2 += data->prob2[i];
    }       
  
  printf("----- FROM %f to %f -----\n", 1 - MIN_FLOW1, 1.0);  
  mean = calc_mean(data->mes, OMEGA);
  esp = calc_esp(data->prob, OMEGA);
  esp_sq = calc_esp_square(data->prob, OMEGA);
  data->var = esp_sq - esp*esp;
  var1 = calc_variance_esp(data->mes, mean);
  data->std_dev = sqrt(var1);
  printf("--->%f esp --- %f mean --- %f var / %f --- standard deviation %f\n", esp, mean, data->var, var1, data->std_dev);

  cmp_gaus(mean, data->std_dev, data->prob);
      
  seuil = calc_alloc(data->prob, OMEGA, sum_prob*ADMIT_RATE);
  act_u = seuil * 100 / OMEGA;
  printf("---> %f percent used for %f percent data\n", act_u, sum_prob*ADMIT_RATE*100);
    
  data->transmission_lost1 = calc_transmission_lost(data->prob, alloc, sum_prob);
  printf("---> Lost transmission : %f percent\n", data->transmission_lost1 * 100);

  data->data_lost1 = (data_lost(data->mes, alloc) * 100 / data->nb_data1);
  printf("amount data lost1 : %f percent (flow scale = %f ~ 1.0)\n", data->data_lost1, (1 - MIN_FLOW1));
    

  printf("\n----- FORM %f to %f -----\n", 1 - MIN_FLOW2, 1.0);    
  mean = calc_mean(data->mes2, OMEGA);
  esp = calc_esp(data->prob2, OMEGA);
  esp_sq = calc_esp_square(data->prob2, OMEGA);
  data->var2 = esp_sq - esp*esp;
  var1 = calc_variance_esp(data->mes2, mean);
  data->std_dev2 = sqrt(var1);
  printf("--->%f esp --- %f mean --- %f var / %f --- standard deviation %f\n", esp, mean, data->var2, var1, data->std_dev2);

  cmp_gaus(mean, data->std_dev2, data->prob2);
      
  seuil = 0;
  seuil = calc_alloc(data->prob2, OMEGA, sum_prob2*ADMIT_RATE);
  act_u = seuil * 100 / OMEGA;
  printf("---> %f percent used for %f percent data\n", act_u, sum_prob2*ADMIT_RATE*100);
  
  data->transmission_lost2 = calc_transmission_lost(data->prob2, alloc, sum_prob2);
  printf("---> Lost transmission : %f percent\n", data->transmission_lost2 * 100);      

  data->data_lost2 = (data_lost(data->mes2, alloc) * 100 / data->nb_data2);
  printf("amount data lost2 : %f percent (flow scale = %f ~ 1.0)\n", data->data_lost2, (1 - MIN_FLOW2));

}
