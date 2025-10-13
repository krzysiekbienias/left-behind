# pragma once
#include "std_aliases.hpp"


using namespace rnd;
using namespace stl;
using namespace custom_alias;

class DecodeEncodeURL {
public:
    DecodeEncodeURL(string baseURL="http://",
                    u32 seed=10);

    string encode(string longURL);
    string decode(string shortURL);

    void setBase(string baseURL) {
        m_baseURL=baseURL;
    }
    static u64 pow62(int exp=6);

    string getBase() const{
        return m_baseURL;
    }






private:
    static   constexpr const char* ALPH= "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string m_baseURL;

    rnd::RNG64 m_rng;
    rnd :: UniformInt<int> m_dist;

    unordered_map<u64,string> m_id2Url;
    unordered_map<string,u64> m_url2Id;

    u64 generateId_();


};