#pragma once

class Device
{
public:
    virtual char read() = 0;
    virtual unsigned int read(char * buf, int len) = 0;
    virtual bool isAtEnd() = 0;
};