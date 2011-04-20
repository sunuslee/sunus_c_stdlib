#include <string.h>
#include "include/MyAlgo.h"
const char val_type[][8] = 
{
        {"char"},
        {"uint8"},
        {"uint16"},
        {"int16"},
        {"uint32"},
        {"int32"},
        {"float"},
        {"double"},
        {"e"}, //end
};
int select_cmp_type(const char *type)
{
        int i;
        for(i = 0; val_type[i][0] != 'e'; i++)
                if(strcmp((const char *)val_type[i], type) == 0)
                        break;
        printf("%s : type = %s , index = %d\n",__func__,(const char *)val_type[i],i);
        return val_type[i][0] == 'e' ? -1 : i;
}

// if   a > b return 1 
// if   a == b return 0
// if   a < b return -1
#define _VALCMP(type, a_addr, b_addr)   \
({                                      \
(*((type *)a_addr) - *((type *)b_addr));   \
 })
int valcmp(int type, void *a_addr, void *b_addr) 
{
        int ri;
        double rd;
        if(type >= 8 || type < 0)
                printf("valcmp ERROR!\n");
        switch(type)
        {
                case 0  :       
                                ;//FALL THROUGH
                case 1  :
                                ri = _VALCMP(uint8_t, a_addr, b_addr);break;
                case 2  :
                                ri = _VALCMP(uint16_t, a_addr, b_addr);break;
                case 3  :
                                ri = _VALCMP(int16_t, a_addr, b_addr); break;
                case 4  :
                                ri = _VALCMP(uint32_t, a_addr, b_addr);break;
                case 5  :
                                ri = _VALCMP(int32_t, a_addr, b_addr); break;
                case 6  :
                                rd = _VALCMP(double, a_addr, b_addr); break;
                case 7  :
                                rd = _VALCMP(double, a_addr, b_addr); break;
        }
        if(type <= 5)
                return ri;
        if(rd == 0.00000001)
                return 0;
        else if(rd > 0.000001)
                return 1;
        else 
                return -1;
}

void cmptest(const char *type, void *a_addr, void *b_addr)
{
        int type_i;
        int r;
        type_i = select_cmp_type(type);
        r = valcmp(type_i, a_addr, b_addr);
        printf("r = %d \n",r);
}
