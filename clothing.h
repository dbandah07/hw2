#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

// keywords() returns the appropriate keywords to indez the product
// displayString() creates a string that contains the product info 
// dump() outputs the database format of the product info

class Clothing : public Product {
  public: 
  Clothing(const std::string& name, double price, int qty, const std::string& size, const std::string& brand);
  ~Clothing();
  void dump(std::ostream& os) const;
  std::set<std::string> keywords() const;
  std::string displayString() const;

  private:
  std::string size_;
  std::string brand_;
};

#endif

