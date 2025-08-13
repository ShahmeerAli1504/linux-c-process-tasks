#include<iostream>
#include<unistd.h>
using namespace std;

int main(){
     cout<<"P1: ID = "<<getpid()<<","<<"Parent ID = "<<getppid()<<endl;
    int P1=fork();
 
    if(P1>0){
        cout<<"P2: ID = "<<getpid()<<","<<"Parent ID = "<<getppid()<<endl;
    int P2=fork();

     if(P2>0){
            cout<<"P4: ID = "<<getpid()<<","<<"Parent ID = "<<getppid()<<endl;
    }
    else if (P2==0){
        cout<<"P5: ID = "<<getpid()<<", Parent ID = "<<getppid()<<endl; 
    }
    else{
        cout<<"FORK FAILED";
    }
    }
    else if(P1==0){
            cout<<"P3: ID = "<<getpid()<<","<<"Parent ID = "<<getppid()<<endl;
    }
    else{
        cout<<"FORK FAILED";
    }


}