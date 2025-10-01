#include <sstream>
#include <iomanip>
#include <cctype>
#include "movie.h" 
#include "util.h"

using namespace std;

Movie::Movie (const std::string& name, double price, int qty, const std::string& genre, const std::string& rating)
  : Product("movie", name, price, qty), genre_(genre), rating_(rating)
  {
  }

Movie::~Movie() { }

void Movie::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_<< "\n" << genre_ << "\n" << rating_ << endl;  
}

std::set<std::string> Movie::keywords() const {
  std::set<std::string> words;

  // ADD KEYWORDS FROM MOVIE NAME
  std::set<std::string> name_word = parseStringToWords(name_);
  words.insert(name_word.begin(), name_word.end());
  words.insert(genre_);

  return words;
}

std::string Movie::displayString() const {
  std::stringstream ss; 

  ss << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << std::endl << price_ << "  " << qty_ << " left.";
  return ss.str();
}