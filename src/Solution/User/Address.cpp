#include "Address.h"

using namespace std;

Address::Address()
{
	county = "";
	locality = "";
	street = "";
	number = 0;
	block = "";
	apartment = 0;
}

Address::Address(const Address &address)
{
	county = address.county;
	locality = address.locality;
	street = address.street;
	number = address.number;
	block = address.block;
	apartment = address.apartment;
}

Address::Address(const string &jud, const string &loc, const string &str, int nr, const string &bl, int ap)
{
	county = jud;
	locality = loc;
	street = str;
	number = nr;
	block = bl;
	apartment = ap;
}

const Address &Address::operator=(const Address &adr)
{
	
		county = adr.county;
		locality = adr.locality;
		street = adr.street;
		number = adr.number;
		block = adr.block;
		apartment = adr.apartment;
	
	return *this;
}

void Address::setStrada(const string &str)
{
	street = str;
}

void Address::setNumber(int nr)
{
	number = nr;
}

void Address::setBlock(const string &bl)
{
	block = bl;
}

void Address::setApartment(int ap)
{
	apartment = ap;
}

void Address::setCounty(const string &jud)
{
	county = jud;
}

void Address::setLocality(const string &loc)
{
	locality = loc;
}

string &Address::getStreet()
{
	return street;
}

int Address::getNumber()
{
	return number;
}
string &Address::getBlock()
{
	return block;
}

int Address::getApartment()
{
	return apartment;
}

string &Address::getCounty()
{
	return county;
}

string &Address::getLocality()
{
	return locality;
}

bool Address::operator==(const Address &address)
{
	if (county == address.county && locality == address.locality && street == address.street && number == address.number && block == address.block && apartment == address.apartment) 
		return true;
	else return false; 
}

bool Address::operator!=(const Address &address)
{
	if (*this == address)
		return false;
	else return true;
}

ostream &operator<<(ostream &os, const Address &a)
{
	throw("undefined");
}

json Address::toJSON()
{
	return json(*this);
}