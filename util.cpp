#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
// #include <string>
#include <set>

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  // string of many words, split them into individual keywords (at punctuation, 2 char words)

  std::set<std::string> words; 
  std::string word; 

  // for (size_t i = 0; i < rawWords.length(); i++) {
  //   if (rawWords[i] == '.' || rawWords[i] == '\'') {
  //       words.insert(word); // apend keyword 
  //   }
  //   word += rawWords[i];
  // }

  for (size_t i = 0; i < rawWords.length(); ++i) {
    char c = rawWords[i];

    if (c == ' ' || c == '.' || c == '\'') {
      if (!word.empty()) {
        words.insert(word);
        word.clear();
      }
    }
    else {
      word += c;
    }
  }

  if (!word.empty()) {
    words.insert(word);
  }

  return words;
} 

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
