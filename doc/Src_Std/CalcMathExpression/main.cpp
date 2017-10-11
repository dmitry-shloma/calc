/*

*/

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <dlfcn.h>
#include <linux/limits.h>

#include "../RpnCalc/rpncalc.h"

using namespace std;

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    char curr_path[PATH_MAX] = {0};
    getcwd(curr_path, sizeof(curr_path));

    char dl_path[PATH_MAX] = {0};
    strcpy(dl_path, curr_path);
    strcat(dl_path, "/libRpnCalc.so");

    void *handle_dl = dlopen(dl_path, RTLD_LAZY);
    if (!handle_dl) {
        cerr << dlerror() << endl;
        exit(EXIT_FAILURE);
    }

    typedef double (*calculate_t)(const string &str);
    calculate_t calculate = (calculate_t)dlsym(handle_dl, "calculate");

    char *error = dlerror();
    if (error != NULL) {
        cerr << error << endl;
        exit(EXIT_FAILURE);

    string str;
    while(cout << "Math expression: ", cin >> str) {
        if (str == "quit") {
            break;
        }
        double result;
        result = calculate(str);
        cout << "answer: " << result << endl << endl;
    }

    dlclose(handle_dl);
    return 0;
}
