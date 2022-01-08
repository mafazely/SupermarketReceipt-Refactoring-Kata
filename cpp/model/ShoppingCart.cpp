#include "ShoppingCart.h"

void addItemQuantity(const Product& product, double quantity);

std::vector<ProductQuantity> ShoppingCart::getItems() const {
    return items;
}

std::map<Product, double> ShoppingCart::getProductQuantities() const {
    return productQuantities;
}

void ShoppingCart::addItem(const Product& product) {
    addItemQuantity(product, 1.0);
}

void ShoppingCart::addItemQuantity(const Product& product, double quantity) {
    items.emplace_back(product, quantity);
    if (productQuantities.find(product) != productQuantities.end()) {
        productQuantities[product] += quantity;
    } else {
        productQuantities[product] = quantity;
    }
}

void ShoppingCart::handleOffers(Receipt& receipt, std::map<Product, Offer> offers, SupermarketCatalog* catalog) {
    for (const auto& productQuantity : productQuantities) {
        Product product = productQuantity.first;
        double quantity = productQuantity.second;
        if (offers.find(product) != offers.end()) {
            auto offer = offers[product];
            double unitPrice = catalog->getUnitPrice(product);
            int quantityAsInt = (int) quantity;

            Discount* discount = nullptr;

            int realQuantity = getRealQuantityBasedOnOfferType(offer);

            int numberOfXs = quantityAsInt / realQuantity;

            if (offer.getOfferType() == SpecialOfferType::ThreeForTwo && quantityAsInt > 2) {
                discount = getDiscountThreeForTwo(product, quantity, unitPrice, quantityAsInt, numberOfXs);
            }

            if (offer.getOfferType() == SpecialOfferType::FiveForAmount && quantityAsInt >= 5) {
                discount = getDiscountFiveForAmount(product, quantity, offer, unitPrice, quantityAsInt, realQuantity,
                                                    numberOfXs);
            }

            if (offer.getOfferType() == SpecialOfferType::TwoForAmount && quantityAsInt >= 2) {
                discount = getDiscountTwoForAmount(product, quantity, offer, unitPrice, quantityAsInt, realQuantity);
            }

            if (offer.getOfferType() == SpecialOfferType::TenPercentDiscount) {
                discount = getDiscountTenPercent(product, quantity, offer, unitPrice);
            }

            if (discount != nullptr)
                receipt.addDiscount(*discount);
        }
    }
}

Discount *
ShoppingCart::getDiscountTenPercent(const Product &product, double quantity, const Offer &offer,
                                    double unitPrice) const {
    Discount *discount;
    discount = new Discount(std::to_string(offer.getArgument()) + "% off", -quantity * unitPrice * offer.getArgument() / 100.0, product);
    return discount;
}

Discount *
ShoppingCart::getDiscountTwoForAmount(const Product &product, double quantity, const Offer &offer, double unitPrice,
                                      int quantityAsInt, int realQuantity) const {
    Discount *discount;
    double total = offer.getArgument() * (quantityAsInt / realQuantity) + quantityAsInt % 2 * unitPrice;
    double discountN = unitPrice * quantity - total;
    discount = new Discount("2 for " + std::to_string(offer.getArgument()), -discountN, product);
    return discount;
}

Discount *
ShoppingCart::getDiscountFiveForAmount(const Product &product, double quantity, const Offer &offer, double unitPrice,
                                       int quantityAsInt, int realQuantity, int numberOfXs) const {
    Discount *discount;
    double discountTotal = unitPrice * quantity - (offer.getArgument() * numberOfXs + quantityAsInt % 5 * unitPrice);
    discount = new Discount(std::to_string(realQuantity) + " for " + std::to_string(offer.getArgument()), -discountTotal, product);
    return discount;
}

Discount *
ShoppingCart::getDiscountThreeForTwo(const Product &product, double quantity, double unitPrice, int quantityAsInt,
                                     int numberOfXs) const {
    Discount *discount;
    double discountAmount = quantity * unitPrice - ((numberOfXs * 2 * unitPrice) + quantityAsInt % 3 * unitPrice);
    discount = new Discount("3 for 2", -discountAmount, product);
    return discount;
}

int ShoppingCart::getRealQuantityBasedOnOfferType(const Offer &offer) const {
    int realQuantity = 1;

    if (offer.getOfferType() == SpecialOfferType::ThreeForTwo) {
        realQuantity = 3;
    } else if (offer.getOfferType() == SpecialOfferType::TwoForAmount) {
        realQuantity = 2;
    } else if (offer.getOfferType() == SpecialOfferType::FiveForAmount) {
        realQuantity = 5;
    }
    return realQuantity;
}
