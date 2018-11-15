#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

int check(int32_t streamSize, int32_t matrixSize, float *expectedQ, float *expectedR, float *outMatricesQ, float *outMatricesR)
{
	int status = 0;
	for (int i = 0; i < streamSize * matrixSize; i++)
	{
    if (expectedQ[i] != outMatricesQ[i])
		{
      fprintf(stderr, "Error detected expectedQ[%d] != %d\n", expectedQ[i], outMatricesQ);
			status = 1;
		}
    if (expectedR[i] != outMatricesR[i])
		{
      fprintf(stderr, "Error detected expectedR[%d] != %d\n", expectedR[i], outMatricesR);
			status = 1;
		}
  }
	return status;
}

void qr(int start, int32_t matrixSize , float *inMatrices, float *expectedQ, float *expectedR)
{
  int i,j,k,n;
  float s;
  n = (int)sqrt(matrixSize);
  for(k = start; k < start + n; k++)
	{
    s = 0.0;
    for(j = start; j < start + n; j++){s += inMatrices[j*n+k]*inMatrices[j*n+k];}
    expectedR[k*n+k] = sqrt(s);
    for(j = start; j < start + n; j++){expectedQ[j*n+k] = inMatrices[j*n+k]/expectedR[k*n+k];}
    for(i = k + 1; i < start + n; i++)
		{
      s = 0.0;
      for(j = start; j < start + n; j++){s += inMatrices[j*n+i]*expectedQ[j*n+k];}
      expectedR[k*n+i] = s;
      for(j = start; j < start + n; j++){inMatrices[j*n+i] -= expectedR[k*n+i]*expectedQ[j*n+k];}
    }
  }
}
void qrDecompCPU(int32_t streamSize, int32_t matrixSize, float *inMatrices, float *expectedQ, float *expectedR)
{
  int i,start;
  for(i=0;i<streamSize;i++)
	{
    start=i*matrixSize;
    qr(start,matrixSize,inMatrices,expectedQ,expectedR);
  }
}
int main(void)
{
        const int matrixSize = qeDecomp_matrixSize;
        const int streamSize=2;
        int sizeBytes = streamSize * matrixSize * sizeof(int32_t);
        float *inMatrices = malloc(sizeBytes);
        float *outMatricesQ = malloc(sizeBytes);
        float *outMatricesR = malloc(sizeBytes);
        float *expectedQ = malloc(sizeBytes);
        float *expectedR = malloc(sizeBytes);

        for(int i = 0; i < matrixSize*streamSize; i++)
				{
                inMatrices[i] = (float) i;
                expectedQ[i] = 0.0;
                expectedR[i] = 0.0;
        }
        qrDecompCPU(streamSize, matrixSize, inMatrices, expectedQ, expectedR);
				for (int i = 0; i < matrixSize * streamSize; i++) {inMatrices[i]=(float)i;}
        printf("Running on DFE.\n");
        qrDecomp(streamSize, inMatrices, outMatricesQ, outMatricesR);
        int status = check(streamSize, matrixSize, expectedQ, expectedR, outMatricesQ, outMatricesR);
      	if (status)	printf("Test failed.\n");
      	else printf("Test passed OK!\n");
      	return status;
}
