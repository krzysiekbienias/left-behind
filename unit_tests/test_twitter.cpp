#include <twitter.hpp>

#include <gtest/gtest.h>
#include <vector>

TEST(TwitterTest, EmptyFeedWhenNobodyPosted) {
    Twitter twitter;
    EXPECT_EQ(twitter.getNewsFeed(1), std::vector<int>{});
}

TEST(TwitterTest, OwnTweetAppearsInFeed) {
    Twitter twitter;
    twitter.postTweet(1, 5);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{5}));
}

TEST(TwitterTest, OwnTweetsNewestFirst) {
    Twitter twitter;
    twitter.postTweet(1, 5);
    twitter.postTweet(1, 7);
    twitter.postTweet(1, 9);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{9, 7, 5}));
}

TEST(TwitterTest, LeetCodeExampleSequence) {
    Twitter twitter;
    twitter.postTweet(1, 5);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{5}));

    twitter.follow(1, 2);
    twitter.postTweet(2, 6);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{6, 5}));

    twitter.unfollow(1, 2);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{5}));
}

TEST(TwitterTest, DoesNotSeeStrangerTweetsUntilFollow) {
    Twitter twitter;
    twitter.postTweet(1, 10);
    twitter.postTweet(2, 20);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{10}));

    twitter.follow(1, 2);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{20, 10}));
}

TEST(TwitterTest, FolloweeWithNoTweetsDoesNotBreakFeed) {
    Twitter twitter;
    twitter.postTweet(1, 3);
    twitter.follow(1, 99);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{3}));
}

TEST(TwitterTest, FollowerWithNoOwnTweetsSeesFollowee) {
    Twitter twitter;
    twitter.postTweet(2, 8);
    twitter.follow(1, 2);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{8}));
}

TEST(TwitterTest, MergesTwoUsersByPostTime) {
    Twitter twitter;
    twitter.postTweet(1, 1);
    twitter.postTweet(2, 2);
    twitter.postTweet(1, 3);
    twitter.postTweet(2, 4);
    twitter.follow(1, 2);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{4, 3, 2, 1}));
}

TEST(TwitterTest, FeedCappedAtTenNewest) {
    Twitter twitter;
    for (int tweet_id = 1; tweet_id <= 15; ++tweet_id) {
        twitter.postTweet(1, tweet_id);
    }
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6}));
}

TEST(TwitterTest, FeedCapAcrossSeveralFollowees) {
    Twitter twitter;
    twitter.follow(1, 2);
    twitter.follow(1, 3);
    for (int tweet_id = 1; tweet_id <= 6; ++tweet_id) {
        twitter.postTweet(2, tweet_id);
        twitter.postTweet(3, 100 + tweet_id);
    }
    EXPECT_EQ(twitter.getNewsFeed(1),
              (std::vector<int>{106, 6, 105, 5, 104, 4, 103, 3, 102, 2}));
}

TEST(TwitterTest, UnfollowUnknownUserIsNoOp) {
    Twitter twitter;
    twitter.postTweet(1, 1);
    twitter.unfollow(1, 2);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{1}));
}

TEST(TwitterTest, FollowSelfDoesNotDuplicateOwnTweets) {
    Twitter twitter;
    twitter.postTweet(1, 5);
    twitter.follow(1, 1);
    EXPECT_EQ(twitter.getNewsFeed(1), (std::vector<int>{5}));
}

TEST(TwitterTest, OtherUsersFeedStaysIsolated) {
    Twitter twitter;
    twitter.postTweet(1, 5);
    twitter.postTweet(2, 6);
    twitter.follow(1, 2);
    EXPECT_EQ(twitter.getNewsFeed(2), (std::vector<int>{6}));
    EXPECT_EQ(twitter.getNewsFeed(3), (std::vector<int>{}));
}
