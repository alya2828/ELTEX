#ifndef IP_H_
#define IP_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
__uint32_t matchingIP(__uint32_t Net_Dst, __uint32_t *Net_Src, int num);
__uint32_t compareIP(char *IP_Dst,__uint32_t mask);
__uint32_t *compareNet_Src(__uint32_t mask, int num, __uint32_t *IP_Src, __uint32_t *Net_Src);
__uint32_t *generation(int num);

#endif