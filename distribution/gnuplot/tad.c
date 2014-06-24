#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad.h"

struct data_c* data_c_create()
{
  struct data_c* d;
  if((d = malloc(sizeof(struct data_c))) == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
  return d;
}

void data_c_clear(struct data_c* d)
{
  free(d);
}


int init_data_c(struct data_c* data)
{
  int i = 0;  
  
  for(i = 0; i < TIME; i++)
    {
      data->mes[i] = 0;
      data->mes2[i] = 0;
    }

  for(i = 0; i < CAPACITY; i++)
    {
      data->occ[i] = 0.0;
      data->occ2[i] = 0.0;
      data->prob[i] = 0.0;
      data->prob2[i] = 0.0;
    }

  data->nb_data1 = 0.0;
  data->nb_data2 = 0.0;
  data->var= 0.0;
  data->var2 = 0.0;
  data->std_dev = 0.0;
  data->std_dev2 = 0.0;
  data->transmission_lost1 = 0.0;
  data->transmission_lost2 = 0.0;
  data->data_lost1 = 0.0;
  data->data_lost2 = 0.0;
 
  return EXIT_SUCCESS;
}


struct link* link_create()
{
  int i;
  struct link * l;
  
  if((l = malloc(sizeof(struct link))) == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

  for(i = 0; i <  NB_VN; i++)
    {
      l->link[i] = v_net_create();
    }
  l->capacity = CAPACITY;
  l->r_capacity = CAPACITY;

  return l;
}
      
struct v_net* v_net_create()
{
  struct v_net* v;
  
  if((v = malloc(sizeof(struct v_net))) == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

  return v;
}

int init_link_blank(struct link * link)
{
  int i;
  for(i = 0; i < NB_VN; i++)
    {
      init_v_net(link->link[i], 0);
    }
  return EXIT_SUCCESS;
}

int init_link_rand(struct link* link)
{
  int i;
  time_t t;
  srand((unsigned) time(&t));

  int lim = 0;
  for(i = 0; i < NB_VN; i++)
    {
      while(lim == 0)
	{
	  lim = rand() % (link->r_capacity / 2); 
	}
      if((link->r_capacity = link->r_capacity - lim) <= 0)
      	{
	  link->r_capacity = CAPACITY;
	  return EXIT_FAILURE;
      	}
      
      init_v_net(link->link[i], lim);
      printf("---> VN : %d --- Resources : %d\n", i, link->link[i]->max_flow);
      lim = 0;
    }
  return EXIT_SUCCESS;
}

int init_link_eco(struct link* link, float rate, int req)
{
  int i;
  int n_req = 1;
  
  if(req <= link->r_capacity)
    {
      n_req = rate * n_req;
      for(i = 0; i <= NB_VN; i++)
	{
	  if(link->link[i]->max_flow == 0)
	    {
	      link->r_capacity = link->r_capacity - n_req;	
	      init_v_net(link->link[i], req);
	      return EXIT_SUCCESS;
	    }
	}
    }
  return EXIT_FAILURE;
}

int init_link_lin(struct link* l, float a, float b)
{
  int i;
  int lim;
  l->r_capacity = CAPACITY;
  
  for(i = 0; i < NB_VN; i++)
    {
      lim = a*i + b;
      init_v_net(l->link[i], lim);
      if((l->r_capacity = l->r_capacity - lim) <= 0)
      	{
	  l->r_capacity = CAPACITY;
	  return EXIT_FAILURE;
      	}      
      printf("---> VN : %d --- VN Request : %d\n", i, lim);
    }
  return EXIT_SUCCESS;
}


void init_v_net(struct v_net* v, int r)
{
  if(v == NULL)
    {
      fprintf(stderr, "init_v_net");
      exit(EXIT_FAILURE);
    }
  v->max_flow = r;
  v->flow = 0;
}
    
void v_net_clear(struct v_net* v)
{
 if(v == NULL)
    {
      fprintf(stderr, "v_net_clear");
      exit(EXIT_FAILURE);
    }
  free(v);
}


void link_clear(struct link *l) 
{
   if(l == NULL)
    {
      fprintf(stderr, "link_clear");
      exit(EXIT_FAILURE);
    }
   
  int i;

  for(i = 0; i < NB_VN; i ++)
    {
      v_net_clear(l->link[i]);
    }
  
  free(l);
}
