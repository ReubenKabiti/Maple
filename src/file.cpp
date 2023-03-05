#include "file.hpp"
#include <string.h>
/*
    Why the heck I am writing my own File Class when the c++ standard library already has one?
    Tbh, 
    I don't know.
*/

File::~File()
{
    // make sure to release the file when the class goes out of scope
    if (m_isOpen)
        fclose(m_fp);
}

bool File::open(OpenType type)
{
    const char * openType;
    // map the open type to a format that fopen will understand 
    switch(type)
    {
        case ReadOnly:
            openType = "r";
            break;
        case WriteOnly:
            openType = "w";
            break;
        case ReadAndWrite:
            openType = "rw";
            break;
        default:
            return false;
    }
    
    // check if a filename has been provided
    if (!strlen(m_filename))
        return false;
    m_fp = fopen(m_filename, openType);
    if (m_fp == NULL)    
        return false;
    m_isOpen = true;
    return true;
}
void File::close()
{
    if (m_isOpen)
        fclose(m_fp);
}
char File::read()
{
    return fgetc(m_fp);
}

unsigned int File::read(char * buf, int len)
{
    return fread(buf, 1, len, m_fp);
}

bool File::isAtEnd()
{
    char c = fgetc(m_fp);
    if (c == EOF)
        return true;
    fseek(m_fp, -1, SEEK_CUR);
    return false;
}
