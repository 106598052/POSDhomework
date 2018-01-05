#include "parser.h"
#include "scanner.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string& check(string &s);

int main( int argc , char **argv ) {
	while(true){
		cout << "?- ";
		string input;
		getline(cin, input);
		if(check(input) == "halt."){
      break;
    }
		Scanner s(input);
		Parser p(s);
		try{
			p.buildExpression();
			string result = p.getExpressionTree()->getResult() + '.';
			cout << result << endl;
		}catch (std::string & msg) {
      cout << msg << endl;
		}
	}
}

string& check(string &input) {
  if (input.empty()) {
       return input;
  }
  int index = 0;
  string str="";
  for(int i=0 ; i<input.size() ; i++){
      if(input[i] != ' '){
          index = i;
          str = str + input[i];
      }
  }
  input = str;
  return input;
}
