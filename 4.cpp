#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;

int main(){

    vector<vector<int>> mat1 = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    vector<vector<int>> mat2 = {
        {9,8,7},
        {6,5,4},
        {3,2,1}
    };

    vector<vector<int>> ans(3, vector<int>(3));

    #pragma omp parallel for collapse(2)
    for(int i = 0; i < mat1.size(); i++){

        for(int j = 0; j < mat1[0].size(); j++){

            ans[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    cout << "Result Matrix:\n";

    for(int i = 0; i < mat1.size(); i++){

        for(int j = 0; j < mat1[0].size(); j++){

            cout << ans[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}