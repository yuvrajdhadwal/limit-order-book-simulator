#ifndef MATCHING_ENGINE_HPP
#define MATCHING_ENGINE_HPP

#include <map>
#include <deque>
#include <unordered_map>
#include <iostream>
#include <memory>

enum Side { BUY, SELL };

struct Order
{
    int id;
    Side side;
    int quantity;
    double price;
    long timestamp;
};

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();

    // Delete copy constructor and copy assignment
    MatchingEngine(const MatchingEngine&) = delete;
    MatchingEngine& operator=(const MatchingEngine) = delete;

    // Allow move construtor and move assignment
    MatchingEngine(MatchingEngine&&) noexcept = default;
    MatchingEngine& operator=(MatchingEngine&&) noexcept = default;

    void placeLimitOrder(const Order& order);
    void placeMarketOrder(Order order);
    void cancelOrder(int orderId);

private:
    // order_book<price, FIFO Orders>
    std::map<double, std::deque<Order>, std::greater<>> bids;   // buy side (highest first)
    std::map<double, std::deque<Order>> asks;                   // sell side (lowest first)

    // order_book<id, (price, iterator)> for fast cancel
    std::unordered_map<int, std::pair<double, std::deque<Order>::iterator>> orderLookup;

    template <typename Comparator>
    void match(Order& incoming, std::map<double, std::deque<Order>, Comparator>& book, bool isBuy);
    void executeTrade(const Order& resting, Order& incoming, double price);
};

template <typename Comparator>
void MatchingEngine::match(Order& incoming, std::map<double, std::deque<Order>, Comparator>& book, bool isBuy) {
    auto it = book.begin();
    while (incoming.quantity > 0 && it != book.end()) {
        double priceLevel = it->first;

        // limit order logic
        if (incoming.price > 0.0) {
            if ((isBuy && incoming.price < priceLevel) || (!isBuy && incoming.price > priceLevel)) {
                break;
            }
        }

        auto& queue = it->second;
        while (!queue.empty() && incoming.quantity > 0) {
            Order& resting = queue.front();
            executeTrade(resting, incoming, priceLevel);

            if (resting.quantity == 0) {
                orderLookup.erase(resting.id);
                queue.pop_front();
            }
        }

        if (queue.empty()) {
            it = book.erase(it);
        } else {
            ++it;
        }
    }
}

#endif  // MATCHING_ENGINE_HPP