#include"test.hpp"
#include<vector>

using namespace std;
void func()
{
    while(1){

    }
}



int main(int argc,char *argv[])
{
    int threadCount = 2;
    if (argc == 2){
        threadCount = atoi(argv[1]);
    }
    std::cout<<"thread count "<<threadCount<<std::endl;
    std::vector<thread> tempVec;
    for (int i = 0; i < threadCount; i++)
    {
        tempVec.emplace_back(func);
    }
    for (auto it = tempVec.begin(); it != tempVec.end(); it++){
        it->join();
    }
}