#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;    

int p1,p2,stat;

int main(){

    p1=fork();

    if(p1==0){

        cout<<"CHILD 1 SUCCESFULL"<<endl;

        cout<<"In child 1 :)"<<endl;

        p2=fork();

        if(p2==0){

                      cout<<"In child 2 :)"<<endl;

                   char* ls = "ls";

               char* arr[] = {"ls", "-l", NULL};



            execvp(ls, arr);

                      if(execvp(ls, arr)==-1){

                 stat= -1;

            exit(stat);

            }

            stat= 1;


            exit(stat);
        }

        else if(p2>0){

                     wait(&stat);

           int x=WEXITSTATUS(stat);

           if(x==-1){

                cout<<"Child 2 failed"<<endl;

                   cout << "execvp() failed." << endl;

           }

        cout<<"CHILD 2 SUCCESFULL"<<endl; 

                        cout<<  "PARENT 2"<<endl;

        }

        else    {

                cout<<"FORK 2 FAILED!!!!!!"<<endl;

       }

    }   

        else if(p1>0){

            wait(NULL);

        cout<<"PARENT 1"<<endl;

        }

        else{

        cout<<"FORK FAILED!!!!!!"<<endl;

    }

}