#pragma once

class Shop {
private:
    int PriceHeal;
    int PriceMana;
    int PriceBuff;
    int PriceShield;

public:
    Shop(int PriceHeal, int PriceMana, int PriceBuff, int PriceShield);
    
    int getPriceHeal() const;
    int getPriceMana() const;
    int getPriceBuff() const;
    int getPriceShield() const;
    
    void setPriceHeal(int price);
    void setPriceMana(int price);
    void setPriceBuff(int price);
    void setPriceShield(int price);
};

