#pragma once

class IServer
{
public:
    virtual void start() const = 0;
    virtual void stop() const = 0;
};
