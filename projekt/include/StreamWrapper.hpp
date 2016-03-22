#include "IStreamWrapper.hpp"
#include <fstream>

#pragma once

using namespace std;

class StreamWrapper : public IStreamWrapper
{
public:

    char get() override
    {
        return m_stream.get();
    }

    void close() override
    {
        m_stream.close();
    }

    void open(const char* p_filename, ios_base::openmode p_mode = ios_base::in | ios_base::out) override
    {
        m_stream.open(p_filename, p_mode);
    }

    bool is_open() const override
    {
        m_stream.is_open();
    }

    istream& seekg(streamoff p_off, ios_base::seekdir p_way) override
    {
        return m_stream.seekg(p_off, p_way);
    }

    streampos tellg() override
    {
        return m_stream.tellg();
    }

    bool good() const override
    {
        return m_stream.good();
    }

    ios_base::seekdir beg() override
    {
        return m_stream.beg;
    }

    ios_base::seekdir end() override
    {
        return m_stream.end;
    }

private:
    std::fstream& m_stream;
};
