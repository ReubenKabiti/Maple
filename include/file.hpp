/*
    file is a device used to read files stored on the disk
*/

#pragma once
#include <stdio.h>
#include "device.hpp"

class File : Device
{
private:
    FILE *m_fp; 
    const char * m_filename;
    bool m_isOpen = false;
public:
    enum OpenType
    {
        ReadOnly,
        WriteOnly,
        ReadAndWrite
    }; 

    File() {}
    File(const char * filename) : m_filename(filename) {}
    File(std::string filename) : m_filename(filename.c_str()) {}
    ~File();
    
    void close();
    bool open(OpenType type);
    char read() override;
    unsigned int read(char * buf, int len) override;
    bool isAtEnd() override;

    
};