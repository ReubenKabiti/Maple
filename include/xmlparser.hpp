#pragma once
#include "device.hpp"

class XMLParser
{
private:
    Device m_device;
public:
    XMLParser();
    XMLParser(Device & device);
    ~XMLParser();

    void setDevice(Device &device);
};