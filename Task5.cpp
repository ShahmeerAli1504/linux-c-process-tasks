#include <iostream>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

vector<string> readDir(char* dir)
{
    vector<string> files;
    DIR* d;
    dirent* dp;
    d = opendir(dir);
    while((dp = readdir(d)) != NULL)
    {
        if(!(strcmp(dp->d_name,"..") == 0 || strcmp(dp->d_name,".") == 0))
        {
            files.push_back(dp->d_name);
        }
    }

    return files;
}

string changeExtension(string file)
{
    string name = "\0";
    string extension = "\0";
    int i=0;
    for(i=0;file[i]!='.';i++)
    {
        name+=file[i];
    }
    for(i++;file[i]!='\0';i++)
    {
        extension+=file[i];
    }

    if(strcmp(extension.c_str(),"enc") == 0)
    {
        return name+".txt";
    }
    else
    {
        return name+".enc";
    }
}

void crypt(string file,string dir)
{

    string newfileName = changeExtension(file);
    string temp = file+'t';
    ifstream f1(file);
    ofstream f2(temp);
    char buffer;
    if(!f1.is_open())
    {
        cout << "Unable to open file: " << file << endl;
        exit(0);
    }
    if(!f2.is_open())
    {
        cout << "Unable to open temp file" << endl;
        exit(0);
    }

    while(f1 >> buffer)
    {
        
        if((buffer >= 'A' && buffer <= 'M') || (buffer >= 'a' && buffer <= 'm'))
        {
            buffer+=13;
        }
        else if((buffer >= 'N' && buffer <= 'Z') || (buffer >= 'n' && buffer <= 'z'))
        {
            buffer-=13;
        }
        else if((buffer >= '0' && buffer <= '4'))
        {
            buffer+=5;
        }
        else if((buffer >= '5' && buffer <= '9'))
        {
            buffer-=5;
        }
        f2 << buffer;
    }

    f1.close();
    f2.close();
    remove(file.c_str());
    rename(temp.c_str(),newfileName.c_str());
}


int main()
{
    vector<int> selectedFiles;
    vector<string> files;
    char* dir = new char[50];
    int temp;
    string temp2;
    pid_t* pids;
    cout << "-----------File Encrypter & Decrypter----------" << endl;
    cout << "Enter Directory: ";
    cin >> dir;

    cout << "\nFiles:" << endl;
    files = readDir(dir);
    for(int i=0 ;i<files.size();i++)
    {
        cout << "[" << i << "]" << files[i] << endl;
    }

    cout << "Enter Files: " << endl;;
    cin.ignore();
    while(getline(cin,temp2) && (istringstream(temp2) >> temp))
    {
        selectedFiles.push_back(temp);
    }

    pids = new pid_t[selectedFiles.size()];

    for(int i=0;i<selectedFiles.size();i++)
    {
        int pid = fork();
        if(pid==0)
        {
            string location = dir;
            location+="/"+files[selectedFiles[i]];
            crypt(location,dir);
            exit(1);
        }
        else
        {
            pids[i]=pid;
        }
    }

    for(int i=0;i<selectedFiles.size();i++)
    {
        int status;
        waitpid(pids[i],&status,0);
    }
    
    return 0;
}