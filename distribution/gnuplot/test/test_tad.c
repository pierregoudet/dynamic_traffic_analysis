#include <stdio.h>
#include <stdlib.h>

#include "tad.h"
#include "const.h"

int main(int argc, char ** argv)
{
  (void)argc;
  (void)argv;
  
  int i;

  /* ---- MEMORY CHECK struct data_c : OK ---- */
  struct data_c* d;
  
  d = data_c_create();

  for(i = 0; i < TIME; i++)
    {
      d->mes[i] = 1;
    }

  for(i = 0; i < CAPACITY; i++)
    {
      d->occ[i] = 1;
      d->prob[i] = 1;
    }
  d->var = 0.0;
  d->std_dev= 0.0;

  data_c_clear(d);

  /* ---- MEMORY CHECK struct link :  ---- */
  struct link* l;
 
  l = link_create();
 
  init_link_rand(l);

  link_clear(l);


  /* ---- MEMORY CHECK struct v_net :  OK ---- */
  struct v_net* v;
 
  v = v_net_create();
 
  init_v_net(v, 5);

  v_net_clear(v);


  return EXIT_SUCCESS;
}
