#pragma once
#include <unordered_map>
#include<utility>
#include <unordered_set>
#include <vector>

using std::unordered_map;
using std::pair;
using std::vector;
using std::unordered_set;

class Twitter {

public:
    Twitter()=default;

    void postTweet(int user_id, int tweet_id);
    vector<int> getNewsFeed(int user_id);
    void follow(int follower_id, int followee_id);
    void unfollow(int follower_id, int followee_id);

private:
    unordered_map<int,vector<pair<int,int>>> tweets_;
    unordered_map<int,unordered_set<int>> following_;
    int time_=0;
    static constexpr int k_max_feed_size=10;

};
