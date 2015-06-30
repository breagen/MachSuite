#include "nw.h"

void needwun(char SEQA[N], char SEQB[M],
             char alignedA[N+M], char alignedB[N+M],
             int A[(N+1)*(M+1)], char ptr[(N+1)*(M+1)]){

    int score, match, mismatch, gap, choice1, choice2, choice3, max;
    int i, j, i_t, j_t, Mul1, Mul2, Mul3;

    match    = 1;
    mismatch = -1;
    gap      = -1;

    init_row: for(i=0; i<(N+1); i++){
        A[i] = i * mismatch;
    }

    init_col: for(i=0; i<(M+1); i++){
        A[i*(N+1)] = i * mismatch;
    }

    //matrix Filling Loop
    fill_out: for(i=1; i<(M+1); i++){
        fill_in: for(j=1; j<(N+1); j++){
            if(SEQA[j-1] == SEQB[i-1]){
                score = match;
            } else {
                score = mismatch;
            }

            Mul1 = (i-1) * (N+1);
            Mul2 = (i*(N+1));

            choice1 = A[Mul1 + (j-1)] + score;
            choice2 = A[Mul1 + (j)]   + gap;
            choice3 = A[Mul2 + (j-1)] + gap;

            if(choice1 > choice2){
                max = choice1;
            } else{
                max = choice2;
            }
            if(choice3 > max){
                max = choice3;
            }

            A[Mul2 + j] = max;
            if(max == choice1){
                ptr[Mul2 + j] = 0;
            } else if(max == choice2){
                ptr[Mul2 + j] = 1;
            } else{
                ptr[Mul2 + j] = -1;
            }
        }
    }

    //TraceBack
    i = M;
    j = N;
    i_t = 0;
    j_t = 0;

    trace: while(i > 0 || j > 0){
        Mul3 = j*M;
        if (ptr[i + Mul3] == 0){
            alignedA[i_t] = SEQA[i];
            alignedB[j_t] = SEQB[j];
            j_t++;
            i_t++;
            i--;
            j--;
        }
        else if(ptr[i + Mul3] == 1){
            alignedA[i_t] = SEQA[i];
            alignedB[j_t] = 'X';
            j_t++;
            i_t++;
            i--;
        }
        else{
            alignedA[i_t] = 'X';
            alignedB[j_t] = SEQB[j];
            j_t++;
            i_t++;
            j--;
        }
    }
}
