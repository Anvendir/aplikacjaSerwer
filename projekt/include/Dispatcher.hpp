#include "IDispatcher.hpp"

class Dispatcher : public IDispatcher
{
public:
    Dispatcher();
    void dispatch() override;
};
