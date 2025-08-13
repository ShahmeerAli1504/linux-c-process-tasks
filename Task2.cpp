#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
// Adding '.' at end if not already done 

void dotcheck(string& str) {

    if (!str.empty() && str.back() != '.') {

        str.push_back('.');

    }

}

int main() {
    string Fname[] = {"F1.txt", "F2.txt", "F3.txt"};

    string Tname[] = {"Tfile1.txt", "Tfile2.txt", "Tfile3.txt"};
    
    int childs[3];
    
    int i = 0;
    
    while (i < 3) {
      
        int C = fork();

      
        if (C == 0) { 
      
           cout<<"In child "<<i+1<<endl;
      
            ifstream file(Fname[i]);
      
            if (!file.is_open()) {
      
                cout<<"Error opening file";
      
                exit(1);
      
            }

            // Read content
      
            string read_child;
      
            getline(file, read_child);
      
            dotcheck(read_child);
      
            file.close();

      
            ofstream temporary(Tname[i]);
      
      
            if (!temporary.is_open()) {
      
                cout<<"Error opening temporary file";
      
                exit(1);
      
            }
      
            temporary << read_child;
      
            temporary.close();

            exit(0);
      
        } 
      
        else if (C > 0) { // Parent process
      
            childs[i] = C;
      
        } 
      
        else {
      
            cout<<"Error creating child process";
      
            exit(1);
      
        }
      
        i++;
    
    }

    
    for (int i = 0; i < 3; i++) {
    
        int check;
    
        waitpid(childs[i], &check, 0);
    
        if (!WIFEXITED(check) || WEXITSTATUS(check) != 0) {
    
            cout << "Child process " << i + 1 << " exited with an error" << endl;
    
            exit(1);
    
        }
    
    }

    
    string content;
    
     i = 0;
    
    while ( i < 3) {
    
        ifstream temporary(Tname[i]);
    
        if (!temporary.is_open()) {
    
            cout<<"Error opening file";
    
            exit(1);
    
        }
    
        string Tcontent;
    
        getline(temporary, Tcontent);
    
        content += Tcontent;
    
        temporary.close();
    
        i++;
    
    }

    ofstream out("outputbash.txt");
    if (!out.is_open()) {
        cout<<"Error opening output file";
        exit(1);
    }
    out << content;
    out.close();

    // Deleting files
     i = 0;
    while ( i < 3 ) {
        remove(Tname[i].c_str());
        i++;
    }

   cout << "Question complete!!!!!!!" << endl;

    return 0;
}