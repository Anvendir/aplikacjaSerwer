#include "KlasaA.hpp"

class KlasaB
{
public:
    KlasaB(IKlasaA& a) : m(a)
    {
    }
    int huj();

private:
    IKlasaA & m;
};
