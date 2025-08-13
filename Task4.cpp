#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main() {

    
    char* user_name,*term,*file_path; 

    user_name = getenv("USER");
    
    term = getenv("TERM");
    
    file_path = getenv("PATH");

    
            cout << "Environment Variables:" << endl;
    
            cout << "USER: " << user_name << endl;
    
            cout << "TERM: " << term  << endl;
    
         cout << "PATH: " << file_path  << endl;


    char* x ="script.sh";

    char* y = user_name ;

    char* z = term ;



    char* Array1[] = {x, y, z, nullptr};



    char* Array2[] = {"OS2022=5ma32zw", nullptr};


    if (execve("script.sh", Array1, Array2) == -1) 

    {

        cout<<"ERROR USING EXECVE()";

    }



    return 0;

}



