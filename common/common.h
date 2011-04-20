#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int select_cmp_type(const char *type);
int valcmp(int type, void *a_addr, void *b_addr); 
void cmptest(const char *type, void *a_addr, void *b_addr);
