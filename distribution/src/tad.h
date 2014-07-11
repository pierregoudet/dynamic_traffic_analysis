#pragma once 

#include "const.h"

struct data_c
{
  float mes[TIME];
  float mes2[TIME];
  float* occ;
  float* occ2;
  float* prob;
  float* prob2;
  float nb_data1;
  float nb_data2;
  float var;
  float var2;
  float std_dev;
  float std_dev2;
  float transmission_lost1;
  float transmission_lost2;
  float data_lost1;
  float data_lost2;
};

struct link
{
  struct v_net** link;
  int capacity;
  int r_capacity;
};


struct v_net
{
  int max_flow;
  int flow;
};


struct data_c* data_c_create(int);
struct link* link_create(int, int);
struct v_net* v_net_create(void);
int init_link_blank(struct link*, int);
int init_link_rand(struct link*, int, int);
int init_link_lin(struct link*, float, float, int, int);
int init_link_eco(struct link*, float, int, int);
int init_data_c(struct data_c*, int);
void init_v_net(struct v_net*, int);
void link_clear(struct link*, int);
void v_net_clear(struct v_net*);
void data_c_clear(struct data_c*);
