#include "IUnixWrappers.hpp"
#include "ErrorHandler.hpp"

class UnixWrappers : public IUnixWrappers
{
public:
    UnixWrappers(IErrorHandler& p_errorHandler);

private:
    IErrorHandler& m_error;
};
