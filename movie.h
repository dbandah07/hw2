#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

// keywords() returns the appropriate keywords to indez the product
// displayString() creates a string that contains the product info 
// dump() outputs the database format of the product info

class Movie : public Product {
  public: 
  Movie(const std::string& name, double price, int qty, const std::string& genre, const std::string& rating);
  ~Movie();
  void dump(std::ostream& os) const;
  std::set<std::string> keywords() const;
  std::string displayString() const;

  private:
  std::string genre_;
  std::string rating_;
};

#endif

