//Varun Chennamadhava
#include <vector>
#include <stdio.h>
#include <stdlib.h>

bool thereIsAPath(int start, int target, int **matrix, int path[], int size) {
    bool *visited = new bool[size];
    for (int j = 0; j < size; j++) {
        visited[j] = false;
    }
    std::vector <int> V;
    V.push_back(start);
    visited[start] = true;
    while (V.size() != 0) {
        int i = V.back();
        V.pop_back();
        for (int k = 1; k < size; k++) {
            if (visited[k] == false && matrix[i][k] > 0) {
                V.push_back(k);
                path[k] = i;
                visited[k] = true;
            }
        }
    }
    delete[] visited;
    return visited[target];
}

int** createDynamic2DArray(int &size) {
    int ** array = new int* [size];
    for(int i = 0; i < size; i++)
    array[i] = new int[size];
    return array;
}

void intializeFlowToZero(int *capacity, int ** residualCapacity, int * flow, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            residualCapacity[i][j] = *(capacity + i * size + j);
            *(flow + i * size + j) = 0;
        }
    }
}

void fordFulkersonAlgorthim(int start, int target,int *capacity, int *flow, int **residualCapacity, int n) {
    int i, j;
    int *path = new int[n];
    long minFlowPath = 10000000000000000;
    while (thereIsAPath(start, target, residualCapacity, path, n)) {
        j = target;
        while(j != start) {
            i = path[j];
            if(minFlowPath > residualCapacity[i][j])
            minFlowPath = residualCapacity[i][j];
            j = path[j];
        }
        j = target;
        while(j != start) {
            i = path[j];
            if (*(capacity + i * n + j) > 0)
            *(flow + i * n + j) += minFlowPath;
            else
            *(flow + j * n+ i) -= minFlowPath;
            residualCapacity[i][j] -= minFlowPath;
            residualCapacity[j][i] += minFlowPath;
            j = path[j];
        }
    }
    delete [] path;
}

void maximum_flow(int n, int s, int t, int *capacity, int *flow) {
    int** residualCapacity = createDynamic2DArray(n);
    intializeFlowToZero(capacity, residualCapacity, flow, n);
    fordFulkersonAlgorthim(s,t,capacity, flow, residualCapacity, n);
    delete [] residualCapacity;
}


int main(void)
{  int cap[1000][1000], flow[1000][1000];
    int i,j, flowsum;
    for(i=0; i< 1000; i++)
    for( j =0; j< 1000; j++ )
    cap[i][j] = 0;
    
    for(i=0; i<499; i++)
    for( j=i+1; j<500; j++)
    cap[i][j] = 2;
    for(i=1; i<500; i++)
    cap[i][500 + (i/2)] =4;
    for(i=500; i < 750; i++ )
    { cap[i][i-250]=3;
        cap[i][750] = 1;
        cap[i][751] = 1;
        cap[i][752] = 5;
    }
    cap[751][753] = 5;
    cap[752][753] = 5;
    cap[753][750] = 20;
    for( i=754; i< 999; i++)
    {  cap[753][i]=1;
        cap[i][500]=3;
        cap[i][498]=5;
        cap[i][1] = 100;
    }
    cap[900][999] = 1;
    cap[910][999] = 1;
    cap[920][999] = 1;
    cap[930][999] = 1;
    cap[940][999] = 1;
    cap[950][999] = 1;
    cap[960][999] = 1;
    cap[970][999] = 1;
    cap[980][999] = 1;
    cap[990][999] = 1;
    printf("prepared capacity matrix, now executing maxflow code\n");
    maximum_flow(1000,0,999,&(cap[0][0]),&(flow[0][0]));
    for(i=0; i<=999; i++)
    for(j=0; j<=999; j++)
    {  if( flow[i][j] > cap[i][j] )
        {  printf("Capacity violated\n"); exit(0);}
    }
    for(i=0; i<=999; i++)
    for(j=0; j<=999; j++)
    {  if( flow[i][j] < 0 )
        {  printf("Flow value negative\n"); exit(0);}
    }
    for(i=1; i<999; i++)
    {  int inflow, outflow;
        inflow = 0;
        for( j=0; j <= 999; j++ )
        inflow += flow[j][i];
        outflow = 0;
        for( j=0; j <= 999; j++ )
        outflow += flow[i][j];
        if( inflow != outflow )
        {  printf("Flow conservation fails at vertex %d\n",i); exit(0);}
    }
    printf("Flow is a valid flow\n");
    flowsum = 0;
    for(i=0; i<=999; i++)
    flowsum += flow[0][i];
    printf("Outflow of  0 is %d, should be 10\n", flowsum);
    flowsum = 0;
    for(i=0; i<=999; i++)
    flowsum += flow[i][999];
    printf("Inflow of 999 is %d, should be 10\n", flowsum);
    
    printf("End Test\n");
}
