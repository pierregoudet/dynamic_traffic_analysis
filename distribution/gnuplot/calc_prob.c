#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "const.h"
#include "calc_prob.h"

float calc_esp(float* prob, float bound)
{
  int i;
  float esp = 0;
  for(i = 1; i <= bound; i++)
    {
      esp += prob[i] * i;
    }
  return esp;
}

float calc_esp_square(float* prob, float bound)
{
  int i;
  float esp = 0;
  for(i = 1; i <= bound; i++)
    {
      esp += prob[i] * i * i;
    }
  return esp;
}


float calc_mean(float* data, float nb_member)
{
  int i;
  float mean;
  float sum;

  for(i = 0; i<nb_member; i++)
    {
      sum += data[i];
    }
  
  mean = sum / nb_member;

  return mean;
}

float calc_variance_esp(float* mes, float mean)
{
  float var = 0.0;
  float sum_dev = 0.0;
  int i;

  for(i = 0; i < TIME; i++)
    {
      sum_dev += (mes[i] - mean) * (mes[i] - mean);
    }
  var = sum_dev / TIME;

  return var;
}
		     

int calc_alloc(float* prob, float size, float t)
{
  int i = 0;
  float sum = 0.0;

  while(sum <= t) 
    {
      sum += prob[i];
      i++;
      if(i >= size) 
      	{ 
	  printf(" |%d --- %f sum |", i, sum);
      	  fprintf(stderr,"calc_alloc");
	  break;
      	}
    }
  return i;
}

float calc_data_lost(float* prob, int alloc, float sum_prob)
{
  int i = 0;
  float sum = 0.0;
  float res = 0.0;

  for(i = 0; i < alloc; i++)
    {
      sum += prob[i];
    }
  
  res = sum_prob - sum;
  
  return res;  
}
