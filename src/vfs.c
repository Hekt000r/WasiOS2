#include "vfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VFSNode *root = NULL;
VFSNode *current_dir = NULL;

void vfs_init()
{
    root = (VFSNode *)malloc(sizeof(VFSNode));
    strcpy(root->name, "/");
    root->type = TYPE_DIR;
    root->parent = NULL;
    root->child_count = 0;
    current_dir = root;
}

void vfs_mkdir(const char *name)
{
    if (current_dir->child_count >= MAX_CHILDREN)
    {
        printf("ERROR: Directory full \n");
        return;
    }

    VFSNode *new_node = (VFSNode *)malloc(sizeof(VFSNode));
    strncpy(new_node->name, name, 31);
    new_node->type = TYPE_DIR;
    new_node->parent = current_dir;
    new_node->child_count = 0;

    current_dir->children[current_dir->child_count++] = new_node;
}

void vfs_ls()
{
    for (int i = 0; i < current_dir->child_count; i++)
    {
        printf("%s/ ", current_dir->children[i]->name);
    }
    printf("\n");
}

void vfs_touch(const char *name)
{
    if (current_dir->child_count >= MAX_CHILDREN)
        return;

    VFSNode *new_file = (VFSNode *)malloc(sizeof(VFSNode));
    strncpy(new_file->name, name, 31);
    new_file->type = TYPE_FILE;
    new_file->parent = current_dir;
    new_file->data = NULL;
    new_file->size = 0;

    current_dir->children[current_dir->child_count++] = new_file; // cppcheck-suppress memleak
}

void vfs_write(const char *name, const char *content)
{
    // -== Find the file in currentdir ==-
    for (int i = 0; i < current_dir->child_count; i++)
    {
        VFSNode *node = current_dir->children[i];
        if (strcmp(node->name, name) == 0 && node->type == TYPE_FILE)
        {

            if (node->data)
                free(node->data);

            node->size = strlen(content);
            node->data = (char *)malloc(node->size + 1);
            strcpy(node->data, content);
            return;
        }
    }
    printf("File not found: %s\n", name);
}

void vfs_cd(const char* name) {
    if (strcmp(name, "..") == 0) {
        if (current_dir->parent != NULL) {
            current_dir = current_dir->parent;
        }
        return;
    }

    if (strcmp(name, "/") == 0) {
        current_dir = root;
        return;
    }

    for (int i = 0; i < current_dir->child_count; i++) {
        VFSNode* node = current_dir->children[i];
        if (strcmp(node->name, name) == 0) {
            if (node->type == TYPE_DIR) {
                current_dir = node;
                return;
            } else {
                printf("bash: cd: %s: Not a directory\n", name);
                return;
            }
        }
    }
    printf("bash: cd: %s: No such file or directory\n", name);
}