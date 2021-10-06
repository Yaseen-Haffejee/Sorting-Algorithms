#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

vector<int> & MaxSort(vector<int>& list){
    int length = list.size();
    int maxPos;
    for(int i = length-1;i>0;i--){
        maxPos = i ;
        for(int j=0;j<i;j++){
            if(list[j]>list[maxPos]){
                maxPos = j ;
            }
        }
        int temp = list[i];
        list[i] = list[maxPos];
        list[maxPos] = temp;
    }
    return list;
}
//aka selection sort
vector<int> MinSort(vector<int> list,int length){

    // int length = list.size();
    int minPos;

    for(int i =0;i<length -2;i++){
        minPos = i ;

        for(int j = i+1; j<length;j++){
            if(list[j] < list[minPos]){
                minPos = j ;
            }
        }
        int temp = list[i];
        list[i] = list[minPos];
        list[minPos] = temp;
    }


    return list;
}

vector<int> BubbleSortEscape(vector<int> list,int length){

    // int length = list.size() -1 ;
    length--;
    bool sorted = true;

    while(length >=1 && sorted){
        bool swapped = false;
        for(int j=0; j<length; j++){
            if(list[j] > list[j+1]){
                int temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp ;
                swapped = true;
            }

        }
        if(!swapped){
            sorted = false;
        }
        else{
            length--;
        }
    }
    


    return list;
}

vector<int> BubbleSort(vector<int> list,int length){

    // int length = list.size() -1 ;
    length--;
    for (int i =length; i>0;i--){
        for(int j=0; j<i; j++){
            if(list[j] > list[j+1]){
                int temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp ;
            }

        }
    }

    return list;
}

vector<int> InsertionSort(vector<int>list,int length){
    // int length = list.size() ;

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

vector<int> RandomGenerator(int N){
    random_device rd;
    mt19937 generator(rd());
    vector<int> values;
    uniform_int_distribution<> dist(1,1000000);
    for(int i=0;i<N;i++){
        values.push_back(dist(generator));
    }

    return values;
}
void Print(vector<int>& list){
    for (int x : list){
        cout <<x<<endl;
    }
}

vector<vector<long long>>& times( vector<vector<long long>> &allTimes){
    int runs = 5;
   
    for(int i=1000;i<=20000;i+=1000){
        vector<long long > times(6,0);
        
        //5 runs on each size of data
        for(int run=0;run<5;run++){

            //creating a list of random numbers using i as the size of the list
            vector<int> list = RandomGenerator(i);
            int len = list.size();
            //loop through each sorting algorithm
            for(int j=0;j<6;j++){
                vector<int> sorted;
                if(j==0){
                    auto start = chrono::high_resolution_clock::now();
                    sorted = MinSort(list,len);
                    auto finish = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
                    times[j] += timeTaken;
                }
                else if(j==1){
                    auto start1 = chrono::high_resolution_clock::now();
                    sorted = BubbleSort(list,len);
                    auto finish1 = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish1 - start1).count();
                    times[j] += timeTaken;
                }
                else if (j==2){
                    auto start2 = chrono::high_resolution_clock::now();
                    sorted = BubbleSortEscape(list,len);
                    auto finish2 = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish2 - start2).count();
                    times[j] += timeTaken;
                }
                else if (j==3){
                    auto start3 = chrono::high_resolution_clock::now();
                    sorted = InsertionSort(list,len);
                    auto finish3 = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish3 - start3).count();
                    times[j] += timeTaken;
                }
                else if (j==4){
                    vector<int> list2(list);
                    vector<int>temp(list.size(),0);
                    auto start4 = chrono::high_resolution_clock::now();
                    MergeSort(list2,0,list2.size()-1,temp);
                    auto finish4 = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish4 - start4).count();
                    times[j] += timeTaken;

                }
                else{
                    vector<int> list3(list);
                    auto start5 = chrono::high_resolution_clock::now();
                    QuickSort(list3,0,list3.size()-1);
                    auto finish5 = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish5 - start5).count();
                    times[j] += timeTaken;
                }
            }
        }
        allTimes.push_back(times);
    }
    return allTimes;
}

void writeToFile(vector<vector<long long>>& allTimes){
    int count =1;
    string MinSort,BubbleSort,BubbleSortEscape,InsertionSort,MergeSort,QuickSort="";
    for(auto v : allTimes){
        for(int i = 0; i < v.size(); i++){
            if( i == 0){
                if(count ==20){
                    MinSort += to_string(v[i]/5);
                }
                else{
                    MinSort += to_string(v[i]/5);
                    MinSort += ",";
                }
            }
            else if(i ==1){
                if(count ==20){
                    BubbleSort += to_string(v[i]/5);
                }
                else{
                    BubbleSort += to_string(v[i]/5);
                    BubbleSort += ",";
                }
                
            }
            else if(i==2){
                if(count ==20){
                  BubbleSortEscape += to_string(v[i]/5);
                }
                else{
                    BubbleSortEscape += to_string(v[i]/5);
                    BubbleSortEscape += ",";
                }
            }
            else if(i==3){
                if(count ==20){
                  InsertionSort += to_string(v[i]/5);
                }
                else{
                    InsertionSort += to_string(v[i]/5);
                    InsertionSort += ",";
                }
            }
            else if(i==4){
                if(count ==20){
                  MergeSort += to_string(v[i]/5);
                }
                else{
                    MergeSort += to_string(v[i]/5);
                    MergeSort += ",";
                }
            }
            else{
                if(count ==20){
                  QuickSort += to_string(v[i]/5);
                }
                else{
                    QuickSort += to_string(v[i]/5);
                    QuickSort += ",";
                }
            }
        }
        count ++;
    }
    ofstream MyFile("data2.txt");
    MyFile<<MinSort<<"\n";
    MyFile<<BubbleSort<<"\n";
    MyFile<<BubbleSortEscape<<"\n";
    MyFile<<InsertionSort<<"\n";
    MyFile<<MergeSort<<"\n";
    MyFile<<QuickSort<<"\n";
    MyFile.close();
}

int main(){

    vector<vector<long long>>  myTimes;
    times(myTimes);
    writeToFile(myTimes);
    
    return 0;
}