#include"test.hpp"
#include<vector>
#include<string>

using namespace std;
void func()
{
    while(1){

    }
}

void func(char* str,int len){
    std::string strStr(str,len);
    std::cout<<strStr<<std::endl;
}


int main(int argc,char *argv[])
{

     char str[10] = {'a','b','c'};
     func(str,10);
    // int threadCount = 2;
    // if (argc == 2){
    //     threadCount = atoi(argv[1]);
    // }
    // std::cout<<"thread count "<<threadCount<<std::endl;
    // std::vector<thread> tempVec;
    // for (int i = 0; i < threadCount; i++)
    // {
    //     tempVec.emplace_back(func);
    // }
    // for (auto it = tempVec.begin(); it != tempVec.end(); it++){
    //     it->join();
    // }
}