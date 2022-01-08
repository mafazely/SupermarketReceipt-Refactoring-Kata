#ifndef CPP_SHOPPINGCART_H
#define CPP_SHOPPINGCART_H


#include <vector>
#include <map>
#include "ProductQuantity.h"
#include "Offer.h"
#include "Receipt.h"
#include "SupermarketCatalog.h"

class ShoppingCart {
public:
    std::vector<ProductQuantity> getItems() const;

    std::map<Product, double> getProductQuantities() const;

    void addItem(const Product& product);

    void addItemQuantity(const Product& product, double quantity);

    void handleOffers(Receipt& receipt, std::map<Product, Offer> offers, SupermarketCatalog* catalog);

private:
    std::vector<ProductQuantity> items;
    std::map<Product, double> productQuantities;

    int getRealQuantityBasedOnOfferType(const Offer &offer) const;

    Discount *
    getDiscountThreeForTwo(const Product &product, double quantity, double unitPrice, int quantityAsInt,
                           int numberOfXs) const;

    Discount *getDiscountFiveForAmount(const Product &product, double quantity, const Offer &offer, double unitPrice,
                                       int quantityAsInt, int realQuantity, int numberOfXs) const;

    Discount *getDiscountTwoForAmount(const Product &product, double quantity, const Offer &offer, double unitPrice,
                                      int quantityAsInt, int realQuantity) const;

    Discount *
    getDiscountTenPercent(const Product &product, double quantity, const Offer &offer, double unitPrice) const;

    Discount *
    getDiscount(const Product &product, double quantity, const Offer &offer, double unitPrice, int realQuantity) const;

    bool offersHaveProduct(std::map<Product, Offer> &offers, const Product &product) const;

    void discountHandler(Receipt &receipt, std::map<Product, Offer> &offers, SupermarketCatalog *catalog,
                         const std::pair<const Product, double> &productQuantity) const;
};


#endif //CPP_SHOPPINGCART_H
