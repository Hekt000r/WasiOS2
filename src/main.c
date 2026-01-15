#include <stdio.h>
#include <string.h>
#include "vfs.h"

int main()
{
    vfs_init();
    char input[100];

    printf("Welcome to WasiOS-2! Type 'help' for commands.\n");

    while (1)
    {
        printf("wasm_os:%s$ ", current_dir->name);
        if (!fgets(input, 100, stdin))
            break;
        input[strcspn(input, "\r\n")] = 0;

        // -== Split into Command and Argument ==-

        char *cmd = strtok(input, " \r\n");
        char *arg = strtok(NULL, " \r\n");

        if (!cmd)
            continue; // ENTER is pressed

        // -== Handle commands ==-

        if (strcmp(cmd, "exit") == 0)
        {
            break;
        }
        else if (strcmp(cmd, "ls") == 0)
        {
            vfs_ls();
        }
        else if (strcmp(cmd, "mkdir") == 0)
        {
            if (arg)
            {
                vfs_mkdir(arg);
            }
            else
            {
                printf("Usage: mkdir <name>\n");
            }
        }
        else if (strcmp(cmd, "help") == 0)
        {
            printf("Commands: ls, mkdir, exit\n");
        }
        else
        {
            printf("Unknown command: %s\n", cmd);
        }
    }

    return 0;
}