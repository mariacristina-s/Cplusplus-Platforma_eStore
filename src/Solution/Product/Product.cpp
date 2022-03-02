#include "Product.h"
using namespace std;

// Constructori
Product::~Product() {
	
}

Product::Product() {
	name = "";
	quantity = 0;
    category = "";
    id = 0;
}

Product::Product(const string &n, int q, const string &c, int i) {
	name = n;
	quantity = q;
	category = c;
	id = i;
}

Product::Product(const Product &p) {
	name = p.name;
	quantity = p.quantity;
	category = p.category;
	id = p.id;
}
 
// Operator =
const Product &Product::operator=(const Product &p) {
	name = p.name;
	quantity = p.quantity;
	category = p.category;
	id = p.id;
	return *this;
} 
 
// Set
void Product::setCategory(const string &category) {
	this->category = category;
}

void Product::setId(int id) {
	this->id = id;
}

void Product::setQuantity(int quantity) {
	this->quantity = quantity;
}

void Product::setName(const string &name) {
	this->name = name;
}
 
// Get
string &Product::getCategory() {
	return category;
}

int Product::getQuantity() {
	return quantity;
}

int Product::getId() {
	return id;
}

string &Product::getName() {
	return name;
}

bool Product::checkQuantity(int requestedQuantity)
{
	if (requestedQuantity == quantity)
		return true;
	else return false;
}

void Product::decreaseQuantity(int requestedQuantity)
{
	quantity = quantity - requestedQuantity;
}

void Product::increaseQuantity(int requestedQuantity)
{
	quantity = quantity + requestedQuantity;
}

json Product::toJSON()
{
	return json(*this);
}
