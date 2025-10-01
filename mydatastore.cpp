// implement core functionality of program:
// searching -> use setIntersection, setUnion
// adding product
// adding users
// saving database 
// etc
#include <sstream>
#include <iomanip>
#include <cctype>
#include "mydatastore.h"
#include "util.h"
#include "product.h"


using namespace std;

MyDataStore::MyDataStore() : DataStore() 
{
}

MyDataStore::~MyDataStore() {
  for (size_t i = 0; i < products_.size(); i++) {
    delete products_[i];
  }

  for (size_t i = 0; i < users_.size(); i++) {
    delete users_[i];
  }
}

void MyDataStore::addProduct(Product* p) {
  // vector<Product*> products;

  products_.push_back(p); 

  std::set<std::string> fill = p->keywords();


  // for every keyword in the product's keyword set, 
  for (const std::string& k : fill) {
    std::string lower_k = convToLower(k);
    index[lower_k].insert(p);
    // std::cout << "DEBUG: indexed: " << k << " -> " << p->getName() << endl;
  }

  // for (std::map<std::string, std::set<Product*>>::iterator it = index.begin(); it != index.end(); ++it) {
  //   // std::cout << "DEBUG: Keyword: " << it->first << " -> " << it->second.size() << " products" << std::endl;
  // }
}

void MyDataStore::addUser(User* u) {
  // vector<User*> users;

  users_.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
// 0 = AND search -> setIntersection
// 1 = OR search -> setUnion

  set<Product*> result;

  if(terms.size() == 0) {
    return std::vector<Product*>(); // no terms return empty
  }

  std::map<std::string, std::set<Product*>>::iterator it = index.find(terms[0]);

  if (it != index.end()) {
    result = it->second; // copy set 
  }

  // loop thru remaining terms
  for (size_t i = 1; i < terms.size(); i++) {
    std::map<std::string, std::set<Product*>>::iterator next_it = index.find(terms[i]);
    terms[i] = convToLower(trim(terms[i]));

    if (next_it != index.end()) {
      std::set<Product*> next = next_it->second;

      if (type == 0) {
        result = setIntersection(result, next);
      }

      else if (type == 1) {
        result = setUnion(result, next);
      }

    }
  }

  for (size_t i = 0; i < terms.size(); i++) {
    terms[i] = convToLower(trim(terms[i]));
  }

  
  vector<Product*> r(result.begin(), result.end());
  return r;
}

void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>" << std::endl;
  for (Product* p : products_) {
    p->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;

  for (User* u : users_) {
    u->dump(ofile);
  }
  ofile << "</users>" << std::endl;

}

void MyDataStore::add_to_cart(User* u, Product* p) {
  // std::cout << "DEBUG: entered add_to_cart." << std::endl;
  
  carts[u->getName()].push_back(p); // append product to user's cart
  
  // std::cout << "DEBUG: ADDED " << p->getName() << " TO USER: " << u->getName() << " CART." << std::endl; 
  std::cout << "Added to cart!" << std::endl;
}

void MyDataStore::buy_cart(User* u) {
  std::string uname = u->getName(); // find users name 
  std::vector<Product*>& cart = carts[uname]; // find their cart


  for (std::vector<Product*>::iterator it = cart.begin(); it != cart.end();) {

    // std::cout << "DEBUG: entered for loop inside buy_cart" << std::endl;
    Product* p = *it;

    
    double prod_price = p->getPrice();
    int prod_qty = p->getQty();

    if (u->getBalance() >= prod_price && prod_qty > 0) {
      // std::cout << "DEBUG: entered if statement inside loop inside buy_cart" << std::endl;
      u->deductAmount(prod_price);
      p->subtractQty(1);
      it = cart.erase(it);
    }
    else {
    ++it;
    }
  }  
}

void MyDataStore::view_cart(User* u) {
  std::string uname = u->getName(); // find users name 
  std::vector<Product*>& cart = carts[uname]; // find their cart

  // std::cout << "DEBUG: found " << u->getName() << "'s cart." << std::endl;
  int cnt = 1;
  for (std::vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
    // std::cout << "DEBUG: entered for loop in view_cart" << std::endl;
    Product* p = *it;

    std::cout << "Item " << cnt << std::endl;
    std::cout << p->displayString() << std::endl;
    std::cout << std::endl;
    cnt++;
  }

}

const std::vector<User*>& MyDataStore::getUsers() const { 
  return users_;
}