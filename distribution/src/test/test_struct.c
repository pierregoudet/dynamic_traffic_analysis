#include <stdio.h>
#include <stdlib.h>

#include "tad.h"
#include "const.h"
#include "allocation.h"
#include "traffic.h"
#include "calc_prob.h"

int main(int argc, char** argv)
{
  (void) argc;
  (void) argv;

  struct data_c* data;
  struct link* link;
  int alloc[2] = {0};
  int nb_sim = 0;
  int i = 0;
  int j = 0;
  int nb_vn = 0;
  int capacity = 0;
  int sim_number = 0;
  float rate = 0.0;
  float admit_rate = 0.0;
  float min_flow1 = 0.0;
  float min_flow2 = 0.0;

  nb_sim = atoi(argv[1]);
  rate = atof(argv[2]);
  nb_vn = atoi(argv[3]);
  capacity = atoi(argv[4]);
  admit_rate = atof(argv[5]);
  min_flow1 = atof(argv[6]);
  min_flow2 = atof(argv[7]);
  sim_number = atoi(argv[8]);
  
  data = data_c_create(capacity);
  link = link_create(nb_vn, capacity);
  allocation(link, rate, alloc, nb_vn, capacity);

  traffic(data, link, alloc, admit_rate, min_flow1, min_flow2, nb_vn, capacity);

  link_clear(link, nb_vn);
  data_c_clear(data);

  return EXIT_SUCCESS;
}




