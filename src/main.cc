#include "common.hh"
#include "hangman.hh"
#include "test.hh"

int main(void)
{
    test();

    Game{}.play();

    return 0;
}
