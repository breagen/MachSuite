#include "stencil.h"

void stencil (TYPE orig[row_size * col_size], TYPE sol[row_size * col_size], TYPE filter[f_size]){
    int i, j, k1, k2;
    TYPE temp, mul;

    stencil_label1:for (i=0; i<row_size-2; i++) {
        stencil_label2:for (j=0; j<col_size-2; j++) {
            temp = (TYPE)0;
            stencil_label3:for (k1=0;k1<3;k1++){
                stencil_label4:for (k2=0;k2<3;k2++){
                    mul = filter[k1*3 + k2] * orig[(i * col_size) + j + k1*col_size + k2];
                    temp += mul;
                }
            }
            sol[(i * col_size) + j] = temp;
        }
    }
}
