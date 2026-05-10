#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;

void bubbleSort(vector<int>&arr){
    int n = arr.size();

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){

            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void bubbleSortParallel(vector<int>&arr){
    int n = arr.size();

    for(int i=0;i<n-1;i++){

        #pragma omp parallel for
        for(int j=0;j<n-i-1;j++){

            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


//merge sort
void merge(vector<int>&arr, int l, int r, int mid){

    vector<int>left(mid-l+1);
    vector<int>right(r-mid);

    int idx = l;
    for(int i=0;i<left.size();i++){

        left[i] = arr[idx++];
    }

    for(int i=0;i<right.size();i++){
        right[i] = arr[idx++];
    }

    int i=0, j=0, k=l;
    while(i < left.size() && j < right.size()){

        if(left[i] < right[j]){
            arr[k++] = left[i++];
        }
        else{
            arr[k++] = right[j++];
        }
    }

    while(i < left.size()){
        arr[k++] = left[i++];
    }
    while(j < right.size()){
        arr[k++] = right[j++];
    }

}

void mergeSort(vector<int>&arr, int l, int r){

    if(l >= r) return;

    int mid = l + (r-l) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mergeSort(arr, l, mid);
        }

        #pragma omp section
        {
            mergeSort(arr, mid+1, r);
        }
    }

    merge(arr, l, r, mid);
}


int main(){

    vector<int>arr = {50,62,12,45,78,23};

    vector<int>arr2 = arr;

    double st, end;

    // st = omp_get_wtime();

    bubbleSort(arr);

    // end = omp_get_wtime();

    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    // cout<<"Sequential Time: "<<end-st<<endl;

    // st = omp_get_wtime();

    bubbleSortParallel(arr2);

    // end = omp_get_wtime();

    // cout<<"Parallel Time: "<<end-st<<endl;

    for(int i=0;i<arr2.size();i++){
        cout<<arr2[i]<<" ";
    }

    cout<<"\n\n";
    cout<<"Merge Sort :\n";
    
    arr = {50,62,12,45,78,23};
    mergeSort(arr, 0, arr.size()-1);
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }

    return 0;
}