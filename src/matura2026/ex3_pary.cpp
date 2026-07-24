#include "matura2026/ex3_pary.hpp"
#include <algorithm>
#include <cstddef>
#include<string>
#include <vector>


int asciSum(const std::string& str){
    int suma=0;
    for (const auto& ch : str) {
        suma+=ch;
    }
    return suma;

}

int wspolneWystapienia(std::string s1, std::string s2){
    
    int arr1[26] = {};//or std::array
    int arr2[26] = {};

    for (const auto& ch : s1) {
        arr1[ch-'a']++;
    }
    int min_arr1=*std::min_element(arr1,arr1+26);

    for (const auto& ch : s2) {
        arr2[ch-'a']++;
    }
    int res=0;
    int sum_min_wystapien=0;
    for (int i = 0; i < 26; i++) {
        int curr_min=std::min(arr1[i],arr2[i]);
        sum_min_wystapien+=curr_min;
    }
    return sum_min_wystapien;


}

std::string prefixoSufiks(const std::string& s1, const std::string& s2){
    std::string res;
    size_t n=s1.size();
    size_t m=s2.size();
    int len_a=std::min(s1.size(),s2.size());
    
    std::string s1_pref=s1.substr(0,len_a);
    std::string s2_suff=s2.substr(m-len_a,len_a);
    
    while(len_a>0 && s1_pref!=s2_suff){
        len_a--;
        s1_pref=s1.substr(0,len_a);
        s2_suff=s2.substr(m-len_a,len_a);
    }
    int len_b=std::min(s1.size(),s2.size());
    std::string s2_pref=s2.substr(0,len_b);
    std::string s1_suff=s1.substr(n-len_b,len_b);
    while(len_b>0 && s2_pref!=s1_suff){
        len_b--;
        s2_pref=s2.substr(0,len_b);
        s1_suff=s1.substr(n-len_b,len_b);
    }

    if (std::max(len_a,len_b)<5){
        return "less than 5";
    }
    if (len_a>=len_b){
        return s1_pref;
    }
    return s2_pref;
}



