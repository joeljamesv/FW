/*
The console function this function runs, untill manually is exited using command - exit
*/

#include <iostream>

using namespace std;

int main()
{
     std::cout<<"hello world";

     std::string command;
     while(1)
     {
          std::cin>>command;
          if(command != "exit")
          {
               std::cout<<command<<" ";
          }
          else
          {
               break;
          }
     }

}