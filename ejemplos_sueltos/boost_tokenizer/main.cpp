#include<iostream>
#include<boost/tokenizer.hpp>
#include<boost/foreach.hpp>
#include<string>
#include <vector>
int main(){
   using namespace std;
   using namespace boost;
   string s = "This is,  a test";
   tokenizer<> tok(s);
   vector <string> myTokens (tok.begin(), tok.end());
   BOOST_FOREACH(string & s, myTokens){
     cout << s << endl;
   }
}
