#include <sstream>
#include <iomanip>
#include <cctype>
#include "book.h" 
#include "util.h"

using namespace std;

Book::Book(const std::string& name, double price, int qty, const std::string& ibsn, const std::string& author) 
  : Product("book", name, price, qty), ibsn_(ibsn), author_(author)
  {
  }

Book::~Book() { }

void Book::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ibsn_  << "\n" << author_ << endl;  
}

std::set<std::string> Book::keywords() const {

  std::set<std::string> words;
  // std::string b_word;
  // std::string s;


  // ADD KEYWORDS FROM BOOKS NAME
  std::set<std::string> name_word = parseStringToWords(name_);
  words.insert(name_word.begin(), name_word.end());


  // add ibsn num as a keyword
  words.insert(ibsn_);

  std::set<std::string> author_word = parseStringToWords(author_);
  words.insert(author_word.begin(), author_word.end());

  return words;
}

std::string Book::displayString() const {
  std::stringstream ss; 

  ss << name_ << std::endl << "Author: " << author_ << " ISBN: " << ibsn_ << std::endl << price_ << "  " << qty_ << " left.";
  return ss.str();
}