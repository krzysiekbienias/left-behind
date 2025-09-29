#include<vector>
#include "browser_history.hpp"


BrowserHistory::BrowserHistory(const std::string &homepage):currentIndex(0),len(1) {
    m_browserHistory.reserve(1024);
    m_browserHistory.push_back(homepage);
};

void BrowserHistory::visit(const std::string& url) {
    //override potential forward that to be cleared up after call 'visit'
    if (currentIndex+1<(int)m_browserHistory.size())
        m_browserHistory[currentIndex+1]=url;
    else
        m_browserHistory.push_back(url);
    ++currentIndex;
    len=currentIndex+1;
}

std::string BrowserHistory::back(int steps) {
    currentIndex=std::max(0,currentIndex-steps);
    return m_browserHistory[currentIndex];
}

std::string BrowserHistory::forward(int steps) {
    currentIndex=std::min(len-1,currentIndex+steps);
    return m_browserHistory[currentIndex];
}