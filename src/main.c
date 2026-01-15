#include <stdio.h>
#include <string.h>
#include "vfs.h"

int main() {
    vfs_init();
    char input[100];

    printf("Welcome to WasiOS-2! Type 'help' for commands.\n");

    while (1) {
        printf("wasm_os:%s$ ", current_dir->name);
        if (!fgets(input, 100, stdin)) break;
        input[strcspn(input, "\n")] = 0;

        if (strncmp(input, "mkdir",5) == 0) {
            vfs_mkdir(input + 5);
        } else if (strcmp(input, "ls") == 0) {
            vfs_ls();
        } else if (strcmp(input, "exit") == 0) {
            break;
        } else {
            printf("Command not found. \n");
        }
    }
    
    return 0;
}