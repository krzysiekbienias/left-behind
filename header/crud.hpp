#include<unordered_map>
#include<unordered_set>
#include<vector>


class URLStore{
private:
    std::unordered_map<std::string,std::unordered_set<std::string>> storage;

public:
    void print() const;
    void saveUrl(const std::string& token, const std::string& url);
    
    
    bool isUrlSaved(const std::string& token, const std::string& url) const;
    std::vector<std::string> getURL(const std::string& token);
    bool deleteUrl (const std::string& token, const std::string& url);
};
