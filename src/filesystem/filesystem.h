#pragma once

class FileSystem 
{
public:
    static void Init();
    static void Shutdown();

    int CreateDir(const char* dirName);
    int RemoveDir(const char* dirName);

    //list<const char*> ListDir(const char* dirName);

    int CreateFile(const char* filename);
    int RemoveFile(const char* filename);
    bool FileExists(const char* filename);

    int GetFreeSpace();
    int GetTotalSpace();

    const char* GetCurrentDir();
    int ChangeDir(const char* filename);

    int SetPermissions(const char* path, int permissions);
    int GetPermissions(const char* path);
};