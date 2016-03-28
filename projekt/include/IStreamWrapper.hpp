#include <fstream>

#pragma once

using namespace std;

class IStreamWrapper
{
public:
    virtual char get() = 0;
    virtual bool get(char& p_readByte) = 0;
    virtual char peek() = 0;
    virtual void clear() = 0;
    virtual void close() = 0;
    virtual void open (const char* filename, ios_base::openmode mode = ios_base::in | ios_base::out) = 0;
    virtual bool is_open() const = 0;
    virtual istream& seekg (streamoff off, ios_base::seekdir way) = 0;
    virtual streampos tellg() = 0;
    virtual bool good() const = 0;
    virtual ios_base::seekdir beg() = 0;
    virtual ios_base::seekdir end() = 0;
};
