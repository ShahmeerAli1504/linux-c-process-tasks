#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

void merge(int tobesortedarray[], int start, int end, int right)
{   

    
    int n1 = end - start + 1;
    int n2 = right - end;
    int i = 0,j = 0,k;
    int left[n1], middle[n2];

    while ( i < n1 ){
        left[i] = tobesortedarray[start + i];
        i++;
}
    while ( j < n2){
        middle[j] = tobesortedarray[end + 1 + j];
         j++;
         }

    i = 0;
    j = 0;
    k = start;

    
    while (i < n1 && j < n2)
    {
        if (left[i] <= middle[j])
        {
            tobesortedarray[k] = left[i];
            i++;
        }
        else
        {
            tobesortedarray[k] = middle[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        tobesortedarray[k] = left[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        tobesortedarray[k] = middle[j];
        j++;
        k++;
    }
}

void mergeSort(int tobesortedarray[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        int filedescriptor[2];
        pipe(filedescriptor);

        int P = fork();

        if (P == 0)
        {
            // Child process
            close(filedescriptor[0]);
            mergeSort(tobesortedarray, left, middle);
            write(filedescriptor[1], tobesortedarray + left, (middle - left + 1) * sizeof(int));
            close(filedescriptor[1]);
            exit (0);
        }
        else
        {

            mergeSort(tobesortedarray, middle + 1, right);

            
            wait(NULL);

            
            read(filedescriptor[0], tobesortedarray + left, (middle - left + 1) * sizeof(int));
            close(filedescriptor[0]);

            
            merge(tobesortedarray, left, middle, right);
        }
    }
}

int main()
{
    int S;
    cout << "\nHOW MANY NUMBERS DO YOU WANT TO ENTER : ";cin >> S;   
    
    int * tobesortedarray = new int[S];
    int i = 0;
    while ( i < S)
    {
        cout << "\nNUMBER " << i+1 << " : " ;cin >> tobesortedarray[i];
        i++;
    }

    mergeSort(tobesortedarray, 0, S - 1);

    cout << "\n\nArray after sorting alogrithm:  \n"<<"[";

for (int i = 0; i < S; i++)
    {
        cout << tobesortedarray[i] << " , ";
    }
    cout<<"]";
    cout << endl;

    return 0;
}