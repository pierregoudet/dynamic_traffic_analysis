#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "const.h"
#include "calc_prob.h"

float calc_esp(float* prob, int bound)
{
  int i;
  float esp = 0;
  for(i = 1; i <= bound; i++)
    {
      esp += prob[i] * i;
    }
  return esp;
}

float calc_esp_square(float* prob, int bound)
{
  int i;
  float esp = 0;
  for(i = 1; i <= bound; i++)
    {
      esp += prob[i] * i * i;
    }
  return esp;
}


float calc_mean(int* data, int nb_member)
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


