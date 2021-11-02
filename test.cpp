#include "stdio.h"
#include "iostream"
#include"set"
#include<vector>

std::set<int>& newset(){
    std::set<int> s;
    return s;
}
int diff(int a , int b){
    return abs(a - b);
}

int calc_Mission_Day(std::vector<int> &D, int k, int X, int days)
{
   
    
}

int solution(std::vector<int> &D, int X) {
    // write your code in C++14 (g++ 6.2.0)
    int somme = 0;
    for (unsigned int i = 0; i < D.size(); i++)
    {
        if(i < D.size()-1){
            if(diff(D[i], D[i+1]) <= X){
                somme += 0;
            }else{
                somme += 1;
            }
        }else{
            somme += 1;
        }
    }
    std::cout << somme << "\n";
    

    
}

int main(int argc, char *argv[])
{
    std::vector<int> D;
    D.push_back(5);
    D.push_back(8);
    D.push_back(2);
    D.push_back(7);

    solution(D, 3);
    return 0;
}
