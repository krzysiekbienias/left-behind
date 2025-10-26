# include <cmath>
#include <limits>

double wellBehaved(double x){
    const double epsilon=1e-4;
    if(std::abs(x)<epsilon){
        double x2=x*x;
        return 1.0-x2/6.0 +x2*x2/120.0;
    }
    else{
        return std::sin(x)/x;
    }
}
