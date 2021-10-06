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
vector<int> MinSort(vector<int> list){

    int length = list.size();
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

vector<int> BubbleSortEscape(vector<int> list){

    int length = list.size() -1 ;
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

vector<int> BubbleSort(vector<int> list){

    int length = list.size() -1 ;

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
        vector<long long > times(3,0);
        
        //5 runs on each size of data
        for(int run=0;run<5;run++){

            //creating a list of random numbers using i as the size of the list
            vector<int> list = RandomGenerator(i);
            
            //loop through each sorting algorithm
            for(int j=0;j<3;j++){
                vector<int> sorted;
                if(j==0){
                    auto start = chrono::high_resolution_clock::now();
                    sorted = MinSort(list);
                    auto finish = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
                    times[j] += timeTaken;
                }
                else if(j==1){
                    auto start1 = chrono::high_resolution_clock::now();
                    sorted = BubbleSort(list);
                    auto finish1 = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish1 - start1).count();
                    times[j] += timeTaken;
                }
                else{
                    auto start2 = chrono::high_resolution_clock::now();
                    sorted = BubbleSortEscape(list);
                    auto finish2 = chrono::high_resolution_clock::now();
                    long long timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish2 - start2).count();
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
    string MinSort,BubbleSort,BubbleSortEscape ="";
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
            else{
                if(count ==20){
                  BubbleSortEscape += to_string(v[i]/5);
                }
                else{
                    BubbleSortEscape += to_string(v[i]/5);
                    BubbleSortEscape += ",";
                }
                
            }
        }
        count ++;
    }
    ofstream MyFile("data.txt");
    MyFile<<MinSort<<"\n";
    MyFile<<BubbleSort<<"\n";
    MyFile<<BubbleSortEscape<<"\n";
    MyFile.close();
}

int main(){

    vector<vector<long long>>  myTimes;
    times(myTimes);
    writeToFile(myTimes);
    
    return 0;
}