#ifndef VFS_H
#define VFS_H

#define MAX_CHILDREN 16

typedef enum {TYPE_FILE, TYPE_DIR} EntryType;

typedef struct VFSNode {
    char name[32];
    EntryType type;
    struct VFSNode* parent;
    struct VFSNode* children[MAX_CHILDREN];
    int child_count;
} VFSNode;

// -== Globals ==-
extern VFSNode* root;
extern VFSNode* current_dir;

void vfs_init();
void vfs_mkdir(const char* name);
void vfs_ls();

#endif