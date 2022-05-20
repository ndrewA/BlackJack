#include "House.h"

#include <time.h>

int main()
{
    std::srand(time(0));
    House h;
    float totalMoney = 1000;
    h.playBlackJack(totalMoney);
    return 0;
}
