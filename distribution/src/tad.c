#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad.h"

struct data_c* data_c_create(int capacity)
{
  struct data_c* d;
  if((d = malloc(sizeof(struct data_c))) == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
  
  if(((d->occ = malloc(capacity * sizeof(float))) == NULL) ||
     ((d->occ2 = malloc(capacity * sizeof(float))) == NULL) ||
     ((d->prob = malloc(capacity * sizeof(float))) == NULL) ||
     ((d->prob2 = malloc(capacity * sizeof(float))) == NULL)
     )
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

  return d;
}

void data_c_clear(struct data_c* d)
{
  free(d->occ);
  free(d->occ2);
  free(d->prob);
  free(d->prob2);
  free(d);
}


int init_data_c(struct data_c* data, int capacity)
{
  int i = 0;  
  
  for(i = 0; i < TIME; i++)
    {
      data->mes[i] = 0;
      data->mes2[i] = 0;
    }

  for(i = 0; i < capacity; i++)
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


struct link* link_create(int nb_vn, int capacity)
{
  int i;
  struct link * l;
  
  if((l = malloc(sizeof(struct link))) == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

  if((l->link = malloc(nb_vn * sizeof(struct v_net))) == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }


  for(i = 0; i <  nb_vn; i++)
    {
      l->link[i] = v_net_create();
    }
  l->capacity = capacity;
  l->r_capacity = capacity;

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

int init_link_blank(struct link * link, int nb_vn)
{
  int i;
  for(i = 0; i < nb_vn; i++)
    {
      init_v_net(link->link[i], 0);
    }
  return EXIT_SUCCESS;
}

int init_link_rand(struct link* link, int nb_vn, int capacity)
{
  int i;
  time_t t;
  srand((unsigned) time(&t));

  int lim = 0;
  for(i = 0; i < nb_vn; i++)
    {
      while(lim == 0)
	{
	  lim = rand() % (link->r_capacity / 2); 
	}
      if((link->r_capacity = link->r_capacity - lim) <= 0)
      	{
	  link->r_capacity = capacity;
	  return EXIT_FAILURE;
      	}
      
      init_v_net(link->link[i], lim);
      printf("---> VN : %d --- Resources : %d\n", i, link->link[i]->max_flow);
      lim = 0;
    }
  return EXIT_SUCCESS;
}

int init_link_eco(struct link* link, float rate, int req, int nb_vn)
{
  int i;
  int n_req = 1;
  
  if(req <= link->r_capacity)
    {
      n_req = rate * n_req;
      for(i = 0; i <= nb_vn; i++)
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

int init_link_lin(struct link* l, float a, float b, int nb_vn, int capacity)
{
  int i;
  int lim;
  l->r_capacity = capacity;
  
  for(i = 0; i < nb_vn; i++)
    {
      lim = a*i + b;
      init_v_net(l->link[i], lim);
      if((l->r_capacity = l->r_capacity - lim) <= 0)
      	{
	  l->r_capacity = capacity;
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


void link_clear(struct link *l, int nb_vn) 
{
   if(l == NULL)
    {
      fprintf(stderr, "link_clear");
      exit(EXIT_FAILURE);
    }
   
  int i;

  for(i = 0; i < nb_vn; i ++)
    {
      v_net_clear(l->link[i]);
    }

  free(l->link); 
  free(l);
}
