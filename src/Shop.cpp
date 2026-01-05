#include "../include/Shop.h"

Shop::Shop(int PriceHeal, int PriceMana, int PriceBuff, int PriceShield) 
    : PriceHeal(PriceHeal), PriceBuff(PriceBuff), PriceMana(PriceMana), PriceShield(PriceShield) {}

int Shop::getPriceHeal() const { return PriceHeal; }
int Shop::getPriceMana() const { return PriceMana; }
int Shop::getPriceBuff() const { return PriceBuff; }
int Shop::getPriceShield() const { return PriceShield; }

void Shop::setPriceHeal(int price) { PriceHeal = price; }
void Shop::setPriceMana(int price) { PriceMana = price; }
void Shop::setPriceBuff(int price) { PriceBuff = price; }
void Shop::setPriceShield(int price) { PriceShield = price; }

