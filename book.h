#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

// keywords() returns the appropriate keywords to indez the product
// displayString() creates a string that contains the product info 
// dump() outputs the database format of the product info

class Book : public Product {
  public: 
  Book(const std::string& name, double price, int qty, const std::string& ibsn, const std::string& author);
  ~Book();
  void dump(std::ostream& os) const override;
  std::set<std::string> keywords() const override;
  std::string displayString() const override;

  private:
  std::string ibsn_;
  std::string author_;
};

#endif 