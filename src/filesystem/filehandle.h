#pragma once

class FileHandle
{
private:
public:
    FileHandle() = default;
    FileHandle(const char* filename, const char* mode);
    
    void Open(const char* filename, const char* mode);
    void Close();

    int Read(const unsigned char* buffer, int size);
    int Write(const unsigned char* buffer, int size);

    int Seek(int offset, int origin);
    int Tell();

    int GetSize();
    int Truncate(int size);
};