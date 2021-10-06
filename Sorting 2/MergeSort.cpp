#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void MergeSort(vector<int>&list, int left, int right, vector<int>&temp){
    
    if(right-left>0){
        
        
        int mid = floor((left+right)/2);
        MergeSort(list,left,mid,temp);
        MergeSort(list,mid+1,right,temp);
    
        //populating temp list from left to right 
        for(int i= mid;i>=left;i--){
            temp[i] = list[i];
        }

        for(int j =mid+1;j<=right;j++ ){
            temp[mid +1 +right -j] =list[j];
        }

        int i = left;
        int j = right;
        
        for(int k = left;k<=right;k++){
            if(temp[i]<temp[j]){
                list[k] = temp[i];
                i++;
            }
            else{
                list[k] = temp[j];
                j--;
            }
        }
    }
        
}



int main(){

    vector<int> list = {8,7,54,12,25,0,1};
    vector<int> temp (list.size(),0);
    MergeSort(list,0,list.size()-1,temp);
    for(int x : list){
        cout<<x<<endl;
    }

    return 0;
}