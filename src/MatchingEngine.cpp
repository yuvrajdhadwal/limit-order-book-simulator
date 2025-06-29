#include "MatchingEngine.hpp"

MatchingEngine::MatchingEngine() {}

MatchingEngine::~MatchingEngine() = default;

void MatchingEngine::placeLimitOrder(const Order& order) {
    Order incoming = order;  // creates a copy
    if (order.side == Side::BUY) {
        match(incoming, asks, true);
        if (incoming.quantity > 0) {
            bids[incoming.price].push_back(incoming);
            orderLookup[incoming.id] = {incoming.price, std::prev(bids[incoming.price].end())};
        }
    } else {
        match(incoming, bids, false);
        if (incoming.quantity > 0) {
            asks[incoming.price].push_back(incoming);
            orderLookup[incoming.id] = {incoming.price, std::prev(asks[incoming.price].end())};
        }
    }
}

void MatchingEngine::placeMarketOrder(Order order) {
    if (order.side == Side::BUY) {
        match(order, asks, true);
    } else {
        match(order, bids, false);
    }
}

void MatchingEngine::cancelOrder(int orderId) {
    if (orderLookup.count(orderId)) {
        auto [price, it] = orderLookup[orderId];
        Side side = it->side;
        if (side == Side::BUY) {
            auto& queue = bids[price];
            queue.erase(it);
            if (queue.empty()) bids.erase(price);
        } else {
            auto& queue = asks[price];
            queue.erase(it);
            if (queue.empty()) asks.erase(price);
        }
        orderLookup.erase(orderId);
    }
}

void MatchingEngine::executeTrade(const Order& resting, Order& incoming, double price) {
    int tradeQty = std::min(resting.quantity, incoming.quantity);
    const_cast<Order&>(resting).quantity -= tradeQty;
    incoming.quantity -= tradeQty;

    std::cout << "TRADE: " << tradeQty << " @ " << price
              << " (resting ID: " << resting.id
              << ", incoming ID: " << incoming.id << ")" << std::endl;
}