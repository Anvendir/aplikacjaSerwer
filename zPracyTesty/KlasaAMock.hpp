#include "IKlasaA.hpp"
#include "gmock/gmock.h"

class KlasaAMock : public IKlasaA
{
public:
    MOCK_METHOD2(dodaj, int (int, int));
};
