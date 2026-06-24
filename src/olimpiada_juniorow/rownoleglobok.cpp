#include <iostream>

void rownoleglobok(int n, int m){
    int i=0;
    while(i<n){
        int j=0;
        while(j<i){
            std::cout<<' ';
            j++;
        }
        j=0; //to tylko zerowanie kursora a nie cofanie kursora.
        while (j<m){
            std::cout<<'*';
            j++;
        }
        std::cout<<'\n';
        i++;
    }

}