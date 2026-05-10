#include<iostream>
#include<omp.h>

using namespace std;

int main(){

    int * arr = new int[10];

    int temp[] = {90, 23, 45, 67, 12, 34, 56, 78, 89, 10};

    for(int i = 0; i < 10; i++) arr[i] = temp[i];

    //min element in array
    int min = arr[0];
    #pragma omp parallel for reduction(min:min)
    for(int i=1;i<10;i++){
        if(arr[i] < min) min = arr[i];
    }


    cout<<"Minimum element in array is : "<<min<<endl;

    //max element in array
    int max = arr[0];
    #pragma omp parallel for reduction(max:max)
    for(int i=1;i<10;i++){
        if(arr[i] > max) max = arr[i];
    }

    cout<<"Maximum element in array is : "<<max<<endl;

    //sum of elements in array
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<10;i++){
        sum += arr[i];
    }

    cout<<"Sum of elements in array is : "<<sum<<endl;

    double avg = (double)sum/10;

    cout<<"Average of elements in array is : "<<avg<<endl;

    return 0;

}