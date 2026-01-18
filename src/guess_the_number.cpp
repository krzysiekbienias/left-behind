#include<guess_the_number.hpp>
#include <stdexcept>

Guesser::Guesser(int number,int lives):number(number),lives(lives){};


bool Guesser::guess(int n) {
    if (lives<=0) throw std::invalid_argument("No more Lives");
    if (n==number) return true;

    --lives;
    return false;
}
