#include "lsh.h"

int main() {
    // Initialize shell state on startup
    Shell sh;

    getcwd(sh.root_dir, sizeof(sh.root_dir));

    lsh_loop(&sh);
    
    return 0;
}