#include "Receipt.h"

std::vector<ReceiptItem> Receipt::getItems() const {
    return items;
}

void Receipt::addDiscount(const Discount& discount) {
    discounts.push_back(discount);
}

void Receipt::addProduct(const Product& product, double quantity, double price) {
    items.push_back(ReceiptItem(product, quantity, price, getTotalPriceForReceiptItem(quantity, price)));
}

double Receipt::getTotalPriceForReceiptItem(double quantity, double price) const { return quantity * price; }

std::vector<Discount> Receipt::getDiscounts() const {
    return discounts;
}

double Receipt::getTotalPrice() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.getTotalPrice();
    }
    for (const auto& discount : discounts) {
        total += discount.getDiscountAmount();
    }
    return total;
}
