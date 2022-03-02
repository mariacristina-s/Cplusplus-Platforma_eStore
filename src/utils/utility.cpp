#include "utility.h"

bool Utility::compareProductsbyPrice(Product* p1, Product *p2)
{

    NonFoodProduct *aux1 = dynamic_cast<NonFoodProduct*>(p1);
    NonFoodProduct *aux2 = dynamic_cast<NonFoodProduct*>(p2);
    if (aux1->getPrice() < aux2->getPrice()) 
        return true;
    if (aux1->getPrice() > aux2->getPrice()) 
        return false;
 
    return false;
}

bool Utility::compareProductsbyNameCountryPrice(Product* p1, Product *p2)
{
    if (p1->getName() != p2->getName())
    {
        if (p1->getName() < p2->getName()) 
            return true;
        else if (p1->getName() > p2->getName()) 
            return false;
    }
    if (p1->getName() == p2->getName())
    {
        FoodProduct *aux1 = dynamic_cast<FoodProduct *>(p1);
        FoodProduct *aux2 = dynamic_cast<FoodProduct *>(p2);
        if (aux1->getCountryOfOrigin() == aux2->getCountryOfOrigin())
        {
            if (aux1->getLeiPerKg() < aux2->getLeiPerKg()) 
                return true;
            else if (aux1->getLeiPerKg() > aux2->getLeiPerKg()) 
                return false;
        } 
        else
        {
            if (aux1->getCountryOfOrigin() < aux2->getCountryOfOrigin()) 
                return true;
            else if (aux1->getCountryOfOrigin() > aux2->getCountryOfOrigin()) 
                return false;
        }
    }
    return false;
}


