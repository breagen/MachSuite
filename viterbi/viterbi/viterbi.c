#include "viterbi.h"

int viterbi(int Obs[numObs], float transMat[numStates*numObs],
  float obsLik[numStates*numObs], float v[numStates*numObs]){
    int i, j, k, finalState;
    float maxProb, temp;

    finalState = 0;

    v[0] = 1.0;

    v1 : for(i=0; i<numObs;i++){  //for each observation
       int baseObs =  Obs[i];
        v2 : for(j=0; j<numStates; j++){    //for each possible state
            v3 : for(k=0; k<numStates; k++){    //for each
                temp = v[j*numObs + i] * transMat[j*numObs + k] * obsLik[k*numObs + baseObs];
                if(temp > v[k*numObs + i+1]){
                    v[k*numObs + i+1] = temp;
                }
            }
        }
    }

    maxProb = (float)0.0;

    v4 : for(i=1;i<numStates+1;i++){
        if(v[i*numObs-1] > maxProb){
            finalState = i - 1;
            maxProb = v[i*numObs-1];
        }
    }

    return finalState;
}
