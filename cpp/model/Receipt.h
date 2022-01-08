#ifndef CPP_RECEIPT_H
#define CPP_RECEIPT_H


#include <vector>
#include "Discount.h"
#include "ReceiptItem.h"

class Receipt {
public:
    std::vector<ReceiptItem> getItems() const;

    std::vector<Discount> getDiscounts() const;

    double getTotalPrice() const;

    void addDiscount(const Discount& discount);

    void addProduct(const Product& product, double quantity, double price);

private:
    std::vector<ReceiptItem> items;
    std::vector<Discount> discounts;

    double getTotalPriceForReceiptItem(double quantity, double price) const;
};


#endif //CPP_RECEIPT_H
