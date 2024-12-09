#pragma once

class FileSystem 
{
public:
    static void Init();
    static void Shutdown();

    static int CreateDir(const char* dirName);
    static int RemoveDir(const char* dirName);

    //static list<const char*> ListDir(const char* dirName);

    static int CreateFile(const char* filename);
    static int RemoveFile(const char* filename);
    static bool FileExists(const char* filename);

    static int GetFreeSpace();
    static int GetTotalSpace();

    static const char* GetCurrentDir();
    static int ChangeDir(const char* filename);

    static int SetPermissions(const char* path, int permissions);
    static int GetPermissions(const char* path);
};