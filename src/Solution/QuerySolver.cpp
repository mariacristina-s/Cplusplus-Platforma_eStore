#include "QuerySolver.h"

using namespace std;

/* NU MODIFICATI */
QuerySolver::QuerySolver() 
{
  server = Server::GetInstance();
}

/* NU MODIFICATI */
QuerySolver::~QuerySolver()
{
  if (server != nullptr) 
  {
    server = nullptr;
  }
}

list<Product*> QuerySolver::Query_3a() {
  list<Product*> esp;
  for (list<Product*>::iterator it = server->getProductsList().begin(); it != server->getProductsList().end() ; ++it)
  {
      if ( ((*it)->getCategory() == "espressor") && ((*it)->getProductType() == "redus") ) {
        esp.push_back(*it);
      }
  }
  return esp;
}

list<User*> QuerySolver::Query_3b(){
  list<User*> bu;
  for (list<User*>::iterator it = server->getUsersList().begin(); it != server->getUsersList().end(); ++it)
  {
    if ( ( (*it)->getUserType() == "User nonpremium" ) && ( (*it)->getTransportCost() <= 11.5 ) ) {
      bu.push_back(*it);
    }
  }
  return bu;
}

list<Product*> QuerySolver::Query_3c()
{
  
  list<Product*>::iterator it;
  list<Product*> resig;
  for (it = server->getProductsList().begin(); it != server->getProductsList().end() ; ++it)
  {
    if ((*it)->getProductType() == "resigilat") 
    {
      ResealedProduct *it2 = dynamic_cast<ResealedProduct*>(*it);
      if (it2 != NULL) {
        if (it2->getReason() == "lipsa_accesorii") 
        {
          resig.push_back(*it);
        }
      }
    }
  }
  resig.sort(Utility::compareProductsbyPrice);
  return resig;
}

list<Product*> QuerySolver::Query_3d()
{
  list<Product*>::iterator it;
  list<Product*> alimentare;
  for (it = server->getProductsList().begin(); it != server->getProductsList().end() ; ++it) 
    if ((*it)->getProductType() == "alimentar") 
      alimentare.push_back(*it);

  alimentare.sort(Utility::compareProductsbyNameCountryPrice);
  return alimentare;
}

list<User*> QuerySolver::Query_3e() {

  multimap<int, string> judete;
  list<User*> user_aux, rez;
  vector<int> IDs;

  string max, judet;
  int nr, var = 0;

  vector<int>::iterator itID;
  multimap<int, string>::iterator itj;
  list<User*>::iterator it;

  for(it = server->getUsersList().begin(); it != server->getUsersList().end(); ++it)
  {
    if (judete.size() != 0)
      {
        var = 0;
        for(itj = judete.begin(); itj != judete.end(); ++itj) 
        {
          if(itj->second == (*it)->getBillingData().getCounty())
          {
            var = 1;
            nr = itj->first;
            nr++;
            judet = itj->second;
            judete.erase(itj);
            judete.insert(pair <int, string>(nr, judet) );
            break;
          }
        }
        if(var == 0)
          judete.insert(pair<int, string>(1, (*it)->getBillingData().getCounty()));
        
      }
    else
      judete.insert(pair<int, string>(1, (*it)->getBillingData().getCounty()));
  }

  max = judete.rbegin()->second;

  for(it = server->getUsersList().begin(); it != server->getUsersList().end(); ++it)
    if((*it)->getBillingData().getBlock() == "-" && (*it)->getDeliveryData().getBlock() == "-" && (*it)->getBillingData().getApartment() == 0 && (*it)->getDeliveryData().getApartment() == 0 && (*it)->getBillingData().getCounty() == max)
    {
      user_aux.push_back(*it);
      IDs.push_back((*it)->getUserID());
    }

  sort(IDs.begin(), IDs.end());

  for(itID = IDs.begin(); itID != IDs.end(); ++itID)
    for(it = user_aux.begin(); it != user_aux.end(); ++it)
      if(*itID == (*it)->getUserID())
        rez.push_back(*it);

  return rez;
}

list<User*> QuerySolver::Query_3f()
{
  list<User*> users, rez;
  list<User*>::iterator itu;
  list<Product*> prod;
  list<Product*>::iterator itp;
  vector<int> aux;
  vector<int>::iterator it;

  for (itp = server->getProductsList().begin(); itp != server->getProductsList().end(); itp++)
  {
    if ((*itp)->getCategory() == "imprimanta" || (*itp)->getCategory() == "telefon")
      aux.push_back((*itp)->getId());
  }

  for (itu = server->getUsersList().begin(); itu != server->getUsersList().end(); itu++)
  {
    if ((*itu)->getUserType() == "User premium")
    {
      PremiumUser *i = dynamic_cast<PremiumUser*>(*itu);
      for (it = aux.begin(); it != aux.end(); it++)
        if ((*i).getDiscounts().find(*it) != (*i).getDiscounts().end())
        {
          rez.push_back(*itu);
          break;
        }
    }
  }
  return rez;
}
