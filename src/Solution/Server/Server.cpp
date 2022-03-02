#include "Server.h"

using namespace std;

/* NU MODIFICATI */
Server::Server(){}

/* NU MODIFICATI */
Server *Server::GetInstance()
{
	if (!instance)
	{
		instance = new Server;
	}

	return instance;
}

/* NU MODIFICATI */
Server::~Server()
{
	if (instance != NULL)
		instance = NULL;

	if (!__UserID__ProductsCart__.empty())
		__UserID__ProductsCart__.clear();
}

void Server::set__UserID__ProductsCart__()
{
	list <User*> :: iterator it;
	ShoppingCart *sc;
    for (it = usr.begin(); it != usr.end(); ++it)
	{
		sc = new ShoppingCart;
		__UserID__ProductsCart__.insert(pair<int, ShoppingCart *> ( (*it)->getUserID(), sc));
	}
}

list<Product *> &Server::getProductsList()
{
	return prod;
}

list<User *> &Server::getUsersList()
{
	return usr;
}

map<int, ShoppingCart *> Server::get__UserID__ProductsCart__()
{
	return __UserID__ProductsCart__;
}

bool Server::requestAddProduct(int userID, int productID, int quantity)
{
	int nr = 0;

	User* user;
	Product* product;

	if (quantity <= 0)
		return false;

	for (list<Product*>::iterator it = getProductsList().begin(); it != getProductsList().end(); it++)
		if (productID == (*it)->getId())
			if ((*it)->getQuantity() >= quantity)
			{
				nr = 1;
				product = *it;
			}

	if (nr == 0)
		return false;

	nr = 0;

	for (list<User*>::iterator it = getUsersList().begin(); it != getUsersList().end(); it++)
		if (userID == (*it)->getUserID())
		{
			nr = 1;
			user = *it;
		}

	if (nr == 0)
		return false;
	

	ShoppingCart *cart = (__UserID__ProductsCart__.find(user->getUserID()))->second;
	map <int, int>::iterator it = (cart->getShoppingCart()).find(productID);

	if (it != (cart->getShoppingCart()).end())
		cart->raiseQuantity(productID, quantity);
	else
	{
		pair<int, int> aux(productID, quantity);
		cart->addProduct(productID, quantity);
	}

	product->decreaseQuantity(quantity);

	return true;
}

bool Server::requestDeleteProduct(int userID, int productID, int quantity)
{
	int nr = 0;

	User* user;
	Product* product;

	for (list<Product*>::iterator it = getProductsList().begin(); it != getProductsList().end(); it++)
		if (productID == (*it)->getId())
		{
			nr = 1;
			product = *it;
		}

	if(nr == 0) 
		return false;

	nr = 0;

	for (list<User*>::iterator it = getUsersList().begin(); it != getUsersList().end(); it++)
		if (userID == (*it)->getUserID())
		{
			nr = 1;
			user = *it;
		}

	if(nr == 0)
		return false;

	if (quantity <= 0)
		return false;

	ShoppingCart *cart = (__UserID__ProductsCart__.find(user->getUserID()))->second;
	map<int, int>::iterator it = (cart->getShoppingCart()).find(productID);

	if(it != (cart->getShoppingCart()).end())
	{
		if (it->second > quantity)
		{
			product->increaseQuantity(quantity);
			cart->lowerQuantity(productID, quantity);
		}
		else
		{
			product->increaseQuantity(it->second);
			cart->deleteProduct(productID);
		}
	}
	else
		return false;

	return true;
}

/* NU MODIFICATI */
void Server::populateProducts(const json &input)
{
	prod = ObjectFactory::getProductList(input["shoppingCart"]);
}

/* NU MODIFICATI */
void Server::populateUsers(const json &input)
{
	usr = ObjectFactory::getUserList(input["useri"]);
}