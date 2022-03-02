#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "../Solution/Product/NonFoodProduct.h"
#include "../Solution/Product/FoodProduct.h"

class Utility{

public:
    static bool compareProductsbyPrice(Product *, Product *);
    static bool compareProductsbyNameCountryPrice(Product *, Product *);
};