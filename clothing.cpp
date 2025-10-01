#include <sstream>
#include <iomanip>
#include <cctype>
#include "clothing.h" 
#include "util.h"

using namespace std;

Clothing::Clothing (const std::string& name, double price, int qty, const std::string& size, const std::string& brand)
  : Product("clothing", name, price, qty), size_(size), brand_(brand)
  {
  }

Clothing::~Clothing() { }

void Clothing::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_<< "\n" << size_ << "\n" << brand_ << endl;  
}

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> words;

  // ADD KEYWORDS FROM CLOTHING NAME
  std::set<std::string> name_word = parseStringToWords(name_);
  words.insert(name_word.begin(), name_word.end());

  // ADD KEYWORDS FROM BRAND
  std::set<std::string> brand_word = parseStringToWords(brand_);
  words.insert(brand_word.begin(), brand_word.end());

  return words;
}

std::string Clothing::displayString() const {
  std::stringstream ss; 

  ss << name_ << std::endl << "Size: " << size_ << " Brand: " << brand_ << std::endl << price_ << "  " << qty_ << " left."; 
  return ss.str();
}