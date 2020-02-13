#include "iostream"
#include "fstream"
#include "string"
#include <map>
#include <vector>
#include <stdlib.h>
using namespace std;

enum state{START,COMMENT,ID,NUM,ASSIGN,SPECIAL_CHARACTER,FINISH,ERROR};


class Scanner{
	private :
		state current_state,next_state;
		map<string,string> res;
		map<char,string> sp_characters;
		string path;
	public :
		Scanner(string p);
		void start();
		string traverse_command();
};