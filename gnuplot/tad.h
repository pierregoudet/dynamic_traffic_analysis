#pragma once 

#include "const.h"

struct data_c
{
  int mes[TIME];
  int occ[CAPACITY];
  float prob[CAPACITY];  
  float var;
  float std_dev;
};

struct link
{
  struct v_net* link[NB_VN];
  int capacity;
  int r_capacity;
  int used_capacity;
};


struct v_net
{
  unsigned int max_flow;
  unsigned int flow;
};


struct data_c* data_c_create();
struct link* link_create();
struct v_net* v_net_create();
int init_link_rand(struct link*);
void init_link_rand_loop(struct link*);
int init_link_lin(struct link*, unsigned int, unsigned int);
void init_v_net(struct v_net*, int);
void link_clear(struct link*);
void v_net_clear(struct v_net*);
void data_c_clear(struct data_c*);
