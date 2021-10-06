#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void QuickSort(vector<int>&list, int left, int right){

    if(right > left){
        int v = list[right];
        int i = left;
        int j = right;
        // checking if they pass each other
        while(i<j){
            //checking for value > v from the start
            while(list[i]<v){
                i++;
            }
            //checking for values < v from the end 
            while(j>i && list[j]>=v){
                j--;
            }

            // if we find an element larger than v and element less than v, swap them
            if(j>i){
                int t = list[i];
                list[i] = list[j];
                list[j] = t;
            }
            //pointers swapped positions
            else{
                int t  =list[i];
                list[i] = list[right];
                list[right] = t;
            }
        }
        QuickSort(list,left,i-1);
        QuickSort(list,i+1,right);
    }
        
}



int main(){

    vector<int> list = {8,7,54,12,25,0,1,-1};
    vector<int> temp (list.size(),0);
    QuickSort(list,0,list.size()-1);
    for(int x : list){
        cout<<x<<endl;
    }

    return 0;
}