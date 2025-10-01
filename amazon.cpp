#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;

    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if ( cmd == "ADD" ) {
              string u;
              int cnt;

              if (ss >> u >> cnt) {
                // cout << "DEBUG: entered ADD if" << endl; 
                if (cnt < 1 || cnt > (int)hits.size()) { // valid
                  // cout << "DEBUG: entered second if" << endl;
                  cout << "Invalid request" << endl;
                }
                else {
                  User* found_u = nullptr;
                  for (User* user : ds.getUsers()) {
                    // cout << "DEBUG: entered for loop" << endl;
                    if (convToLower(user->getName()) == convToLower(u)) {
                      // cout << "DEBUG: entered if inside for loop" << endl;
                      found_u = user;
                      break;
                    }
                  }
                    
                  if (found_u == nullptr) {
                    cout << "Invalid request" << endl;
                  }
                  else {
                    // cout << "DEBUG: entered last if before exit" << endl;
                    Product* p = hits[cnt-1];
                    ds.add_to_cart(found_u, p);
                  }
                }
              }
            }
            

            else if ( cmd == "VIEWCART" ) {
              string u;
              User* found_u = nullptr;

              if (ss >> u) {
                for (User* user : ds.getUsers()) {
                  // cout << "DEBUG: entered for loop, found user: " << user->getName() << endl;
                  if (convToLower(user->getName()) == convToLower(u)) {
                    // cout << "DEBUG: entered if statement inside if" << endl;
                    found_u = user;
                    break;
                  }
                }
              }

              if (found_u == nullptr) {
                cout << "Invalid username" << endl;
              }
              else if (found_u != nullptr) {
                // cout << "DEBUG: entered if before exit" << endl; 
                ds.view_cart(found_u);
              }
            }
            
            else if ( cmd == "BUYCART" ) {
              string u;
              User* found_u = nullptr;
              
              if (ss >> u) {
                for (User* user : ds.getUsers()) {
                  // cout << "DEBUG: entered for loop" << endl;
                  if (convToLower(user->getName()) == convToLower(u)) {
                    // cout << "DEBUG: entered if inside for" << endl;
                    found_u = user;
                    break;
                  }
                }
              }

              if (found_u == nullptr) {
                cout << "Invalid username" << endl;
              }

              else {
                // cout << "DEBUG: entered last if before exit" << endl;
                ds.buy_cart(found_u);
                // cout << "Bought " << found_u->getName() << " cart." << endl;
              }
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
