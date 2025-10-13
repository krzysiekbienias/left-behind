#include "std_aliases.hpp"
#include "encode_and_decode_url.hpp"


using namespace rnd;
using namespace stl;
using namespace custom_alias;

//constructor
DecodeEncodeURL::DecodeEncodeURL(string baseURL,u32 seed):m_baseURL(baseURL),
                                                        m_rng(seed),
                                                        m_dist(pow62(6)-1){};

string DecodeEncodeURL::encode(string longURL) {
    //here in this function we update also m_id2Url map and return encoded string
    string res="";
    u64 id = generateId_();
    m_id2Url[id]=longURL;
    m_url2Id[longURL]=id;
    if (id == 0) res.push_back(ALPH[0]);
    while (id>0) {
        int reminder=id%62;
        res.push_back(ALPH[reminder]);
        id/=62;
    }
    std::reverse(res.begin(),res.end());
    return res;
}



u64 DecodeEncodeURL :: pow62(int exp) {
    int result=1;
    if (exp>10)  throw std::out_of_range( "exp>10-> 62^11 overlflows u64");
    for (int i=0;i<=exp;i++)
        result*=62;
    return result;
}


u64 DecodeEncodeURL::generateId_() {
    while (true){ //in theory infinite
        u64 id=m_dist(m_rng);
        if (!m_id2Url.count(id)) //check if already id exists in the map. If not exists then return it otherwise
            return id;

    }
}
