#pragma once 

#include "const.h"

struct data_c
{
  float mes[TIME];
  float mes2[TIME];
  float occ[CAPACITY];
  float occ2[CAPACITY];
  float prob[CAPACITY];
  float prob2[CAPACITY];
  float var;
  float var2;
  float std_dev;
  float std_dev2;
};

struct link
{
  struct v_net* link[NB_VN];
  int capacity;
  int r_capacity;
};


struct v_net
{
  int max_flow;
  int flow;
};


struct data_c* data_c_create();
struct link* link_create();
struct v_net* v_net_create();
int init_link_rand(struct link*);
int init_link_lin(struct link*, float, float);
void init_v_net(struct v_net*, int);
void link_clear(struct link*);
void v_net_clear(struct v_net*);
void data_c_clear(struct data_c*);
