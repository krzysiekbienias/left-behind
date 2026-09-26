#include <twitter.hpp>
#include <tuple>
#include <queue>

using std::tuple;
using std::priority_queue;


void Twitter::postTweet(int user_id, int tweet_id) {
    tweets_[user_id].emplace_back(time_,tweet_id);
    time_++;
}

vector<int> Twitter::getNewsFeed(int user_id) {
    priority_queue<tuple<int,int,int,int>> latestes_tweets;//time,tweet_id,user_id,idx
    //zasiej kopiec sam bedize pilnowal po czasie.
    unordered_set<int>scope =following_[user_id];//copy by value to seperate
    scope.insert(user_id);
    for (int id:scope){
        auto it=tweets_.find(id);
        if (it==tweets_.end() || it->second.empty()) {
            continue;
}
        const auto & user_tweers=it->second;
        auto [time,tweet_id]=user_tweers.back();
        int idx=user_tweers.size()-1;
        latestes_tweets.emplace(time,tweet_id,id,idx);
    }
    vector<int> res;
    while(res.size()<k_max_feed_size && !latestes_tweets.empty()){
         auto [time,tweet_id,uid,idx]=latestes_tweets.top();
        latestes_tweets.pop();
        res.push_back(tweet_id);
        if (idx>0){
            //teraz robisz znow tdajes cosnt bo tu nic nie modyfikujesz

            const auto &user_tweers=tweets_.at(uid);
            auto [prev_time,prev_id]=user_tweers[idx-1];
            latestes_tweets.emplace(prev_time,prev_id,uid,idx-1);
        }

    }
    return res;

}


void Twitter::follow(int follower_id, int followee_id) {
    following_[follower_id].insert(followee_id);
}

void Twitter:: unfollow(int follower_id, int followee_id) {
    following_[follower_id].erase(followee_id);
}