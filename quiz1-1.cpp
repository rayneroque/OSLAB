#include <iostream>
using namespace std;
#include <unistd.h>
#include <sys/wait.h>  

int main(int argc, char *arg[])
{
    int pid= fork();
    
    if (pid < 0) {
        cout << "fork failed\n";  
        exit(1);
    }
    else if (pid == 0) {  // Child process
        cout << "Child Process ID: " << getpid() << endl;
        int pid2 = fork();
        if (pid2 < 0) {
            cout << "fork failed\n";    
            exit(1);
        } else if (pid2 == 0) {  // Grandchild process
            cout << "Grandchild Process ID: " << getpid() << endl;
            execlp("whoami", "whoami", NULL);
            exit(1);
        } else {  // Still child process
            wait(NULL);
            exit(0);
        }
    }
    else {  // Parent process
        cout << "Parent Process ID: " << getpid() << endl;
        wait(NULL);  
        exit(0);
    }
}
