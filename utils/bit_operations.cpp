# include<string>
# include "bit_operations.hpp"

std::string toBinary(int n){
    std::string bitRepr="";
    while (n>0) {
        int reminder=n%2;
        bitRepr+=std::to_string(reminder);
        n=n/2;
    }
    std::reverse(bitRepr.begin(), bitRepr.end());
    return bitRepr;
}
