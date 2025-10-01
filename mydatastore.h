#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include "datastore.h"

// implement core functionality of program:
// searching -> use setIntersection, setUnion
// adding product
// adding users
// saving database 
// etc

class MyDataStore : public DataStore 
{
public:
  MyDataStore();
  ~MyDataStore();
  void addProduct(Product* p) override;
  
  void addUser(User* u) override; 
  std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
  void dump(std::ostream& ofile) override;
  void add_to_cart(User* u, Product* p);
  void buy_cart(User* u);
  void view_cart(User* u);

  const std::vector<User*>& getUsers() const;

  private:
  std::vector<Product*> products_;
  std::vector<User*> users_;

  std::map<std::string, std::set<Product*>> index;
  std::map<std::string, std::vector<Product*>> carts;
};
#endif