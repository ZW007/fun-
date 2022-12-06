#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <unordered_set>
#include <vector>
using namespace std;
  
string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main()
{
    const string command = "ps";
    string allreturn = "";
    size_t found;
    int COUNT_ALL = 0;
    int start_init = 0;
    int found_init = 0;
    unordered_set<string> hash;

    allreturn = exec(command.c_str());
    while (true){
        found_init = allreturn.find("./forever",start_init);
        if(found_init == -1)
            break;
        start_init = found_init + 8;
        COUNT_ALL++;
        string to_insert = allreturn.substr(found_init+12,3);
        hash.insert(to_insert);
    }
        
    while (true)
    {
        unordered_set<string> cur_hash;
        int count = 0;
        allreturn = exec(command.c_str());
        int start = 0;
        int found = 0;
        while (true){
            found = allreturn.find("./forever",start);
            if(found == -1)
                break;
            start = found + 8;
            count++;
            string to_insert = allreturn.substr(found+12,3);
            cur_hash.insert(to_insert);
        }
        string first = "./forever 1 ";
        for (unordered_set<string>::iterator i = hash.begin(); i != hash.end(); ++i){
            if(cur_hash.find(*i) == cur_hash.end()){
                cout << "para missing is: " << *i << endl;
                const string last = " &";
                const string reboot = first + *i + last;      
                system(reboot.data());
            }
        }   
        cur_hash.clear();
        
    }
    return 0;   
}



