#pragma once 

#include "tad.h"

void cmp_gaus(int, float, float*);
void simulation(struct data_c*, struct link*, float, float, int, int);
void traffic(struct data_c*, struct link*, int*, float, float, float, int, int);
float data_lost(float*, int*);
