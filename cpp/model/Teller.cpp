#include "Teller.h"

Teller::Teller(SupermarketCatalog *catalog) : catalog(catalog) {}

void Teller::addSpecialOffer(SpecialOfferType offerType, const Product& product, double argument) {
    offers[product] = Offer(offerType, product, argument);
}

Receipt Teller::checksOutArticlesFrom(ShoppingCart theCart) {
    Receipt receipt{};
    for (const auto& pq: theCart.getItems()) {
        receipt.addProduct(pq.getProduct(), pq.getQuantity(), catalog->getUnitPrice(pq.getProduct()));
    }
    theCart.handleOffers(receipt, offers, catalog);

    return receipt;
}
