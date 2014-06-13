#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "calc_prob.h"

float esp(float* prob, int bound)
{
  int i;
  float esp;
  for(i = 1; i <= bound; i++)
    {
      esp += prob[i] * i;
    }
  return esp;
}

float variance(float* prob, int bound)
{
  int i;
  float var;
  float esp_sq;
  for(i = 1; i <= bound; i++)
    {
      esp_sq += prob[i] * i * i;
    }

  var = esp_sq - esp(prob, bound)*esp(prob,i);
  return var;
}


void store_variance(float* prob, FILE* f)
{
  int i;
  float var;
  char tmp[SIZE];
  for(i = 1; i < OMEGA; i++)
    {
      var = variance(prob, i);
      printf("---> var %f --- prob %f\n", var, prob[i]);
      sprintf(tmp, "%d %f\n", i, var);
      fprintf(f, tmp);
    }
}
