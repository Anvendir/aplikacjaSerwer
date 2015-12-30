#include <string>

class IErrorHandler
{
public:
    virtual void handleSoftError(std::string p_errorMessage) = 0;
    virtual void handleHardError(std::string p_errorMessage) = 0;
};
