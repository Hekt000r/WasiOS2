#include "vfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VFSNode* root = NULL;
VFSNode* current_dir = NULL;

void vfs_init() {
    root = (VFSNode*)malloc(sizeof(VFSNode));
    strcpy(root->name, "/");
    root->type = TYPE_DIR;
    root->parent = NULL;
    root->child_count = 0;
    current_dir = root;
}

void vfs_mkdir(const char* name) {
    if (current_dir->child_count >= MAX_CHILDREN) {
        printf("ERROR: Directory full \n");
        return;
    }

    VFSNode* new_node = (VFSNode*)malloc(sizeof(VFSNode));
    strncpy(new_node->name,name,31);
    new_node->type = TYPE_DIR;
    new_node->parent = current_dir;
    new_node->child_count = 0;

    current_dir-> children[current_dir->child_count++] = new_node;
}

void vfs_ls() {
    for (int i = 0; i < current_dir->child_count; i++) {
        printf("%s/ ", current_dir->children[i]->name);
    }
    printf("\n");
}