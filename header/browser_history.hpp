# pragma once
#include<vector>
#include<string>

class BrowserHistory {
public:
    explicit BrowserHistory(const std::string &homepage);
    void visit(const std::string& url);
    std::string back(int steps);
    std::string forward(int steps);

private:
    std::vector<std::string> m_browserHistory;
    int currentIndex=0;
    int len=0;
};