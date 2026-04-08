#include "design_stack_with_increment_operation.hpp"


CustomStack::CustomStack(int maxSize) : m_maxSize(maxSize) {
    st.reserve(maxSize);
    lazy.reserve(maxSize);
}

void CustomStack:: push(int x) {
    if (st.size() < m_maxSize) {
        st.push_back(x);
        lazy.push_back(0);
    }
}

void CustomStack::increment(int k, int val) {
    if (st.empty()) return ;
    int indexCut=std::min(k,(int)st.size());
    lazy[indexCut-1]+=val;
}


int CustomStack:: pop() {
    if (st.empty()) return -1;
    int n=lazy.size();
    int res=st.back()+lazy.back();
    if (lazy.size()>1) {
        lazy[n-2]+=lazy[n-1];
    }
    lazy.pop_back();
    st.pop_back();
    return res;

}



