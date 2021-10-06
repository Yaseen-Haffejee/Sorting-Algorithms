#include <iostream>
#include <vector>


using namespace std;

vector<int> InsertionSort(vector<int>list){
    int length = list.size() ;

    for(int i = 1; i < length; i++){
        int x = list[i];
        int j = i-1;
        while(j>=0 && list[j]>x){
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = x;
    }

    return list;
}



int main(){

    vector<int> list = {8,7,54,12,25,0,1};

    vector<int> sorted = InsertionSort(list);
    for(int x : sorted){
        cout<<x<<endl;
    }

    return 0;
}