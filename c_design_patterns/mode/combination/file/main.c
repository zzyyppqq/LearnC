#include "file.h"
#include "folder.h"


int main() {
    struct FileSystemNode root;
    struct FileSystemNode folder1;
    struct FileSystemNode folder2;
    struct FileSystemNode folder3;
    struct FileSystemNode file1;
    struct FileSystemNode file2;
    struct FileSystemNode file3;

    Folder(&root, "root");
    Folder(&folder1, "folder1");
    Folder(&folder2, "folder2");
    Folder(&folder3, "folder3");
    File(&file1, "file1");
    File(&file2, "file2");
    File(&file3, "file3");

    root.Add(&root, &folder1);
    root.Add(&root, &folder2);
    root.Add(&root, &file1);
    folder1.Add(&folder1, &file2);
    folder1.Add(&folder1, &file3);
    folder2.Add(&folder2, &folder3);

    root.Operation(&root);
}