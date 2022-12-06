#include <iostream>
#include <unistd.h>

using namespace std;
  
int main(int argc, char** argv)
{

    for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";
  
    while(true){
        sleep(20000);
    }
    return 0;
}