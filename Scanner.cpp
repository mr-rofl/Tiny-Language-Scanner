#include "Scanner.h"

Scanner::Scanner(string p){
	next_state=START;
	current_state=START;
	path=p;
	res.insert(pair<string , string>("if","if token"));
	res.insert(pair<string , string>("else","else token"));
	res.insert(pair<string , string>("end","end token"));
	res.insert(pair<string , string>("then","then token"));
	res.insert(pair<string , string>("read","read token"));
	res.insert(pair<string , string>("write","write token"));
	res.insert(pair<string , string>("repeat","repeat token"));
	res.insert(pair<string , string>("until","until token"));
	sp_characters.insert(pair<char,string>('=',"equal token"));
	sp_characters.insert(pair<char,string>('+',"plus token"));
	sp_characters.insert(pair<char,string>('-',"minus token"));
	sp_characters.insert(pair<char,string>('*',"multiply token"));
	sp_characters.insert(pair<char,string>('/',"divide token"));
	sp_characters.insert(pair<char,string>(';',"semi-colon token"));
	sp_characters.insert(pair<char,string>('(',"open bracket token"));
	sp_characters.insert(pair<char,string>(')',"close bracket token"));
	sp_characters.insert(pair<char,string>('<',"less than token"));
}


string Scanner::traverse_command(){
	string output;
	ifstream code(path);
	vector<string> commands;
	string temp;
	char c,temp_char;
	if(code.is_open()){
		while(code.get(c))
		{
			switch (current_state)
			{
			case START:
				if(c=='{'){
					next_state=COMMENT;
				}
				else if (isdigit(c)){
					next_state=NUM;
					temp+=c;
				}
				else if(c==':')
				{
					next_state=ASSIGN;
				}
				else if(isalpha(c))
				{
					next_state=ID;
					temp+=c;
				}
				else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='='||c=='('||c==')'||c=='<'||c==';'){
					next_state=SPECIAL_CHARACTER;
					temp+=c;
					
				}
				else if (c==' '||c=='\n'||c=='\t')
				{
					next_state=current_state;
				}

				else
				{
					next_state=ERROR;
				}
				break;
			case COMMENT:
				if (c=='}')
				{
					next_state=START;
				}
				else
				{
					next_state=current_state;
				}
				break;
			case ID:
				temp_char = code.peek() ;
				if (isalpha(c))
				{
					next_state=current_state;
					temp.push_back(c);
				}
				else if(c==' ' || c==';'||c==' '||c=='\n'||c=='\t'){
					output+=(temp+": ");
					if(res[temp]=="")
					{
						output+="identifier\n";
					}
					else
					{
						output+=(res[temp]+"\n");
					}
					temp="";
					next_state=START;
					if (c==';')
					{
						output+="; :  "+sp_characters[';']+"\n";
					}
				}
				else
				{
					next_state=ERROR;
				}
				if (temp_char==EOF)
				{
					output+=temp+": ";
					if(res[temp]=="")
					{
						output+="identifier\n";
					}
					else
					{
						output+=res[temp]+"\n";
					}
				}
				
				break;
			case NUM:
				temp_char = code.peek() ;
				if (isdigit(c))
				{
					next_state=current_state;
					temp.push_back(c);
				}
				
				else if(c==' '||c==';'||c==' '||c=='\n'||c=='\t'|| temp_char == EOF ){
					output+=temp+": number\n";
					temp="";
					next_state=START;
					if (c==';')
					{
						output+="; :  "+sp_characters[';']+"\n";
					}
				}
				else
				{
					next_state=ERROR;
				}
				if (temp_char==EOF){
					output+=temp+": number\n";
				}

				break;
			case ASSIGN:
				if (c=='=')
				{
					next_state=START;
					output+=" := : assignment token\n";
				}
				else
				{
					next_state=ERROR;
				}
				break;
			case SPECIAL_CHARACTER:
				output+=temp+": "+sp_characters[temp[0]]+"\n";
				temp="";
				next_state=START;
				break;
			case FINISH:
				next_state=START;
				break;
			case ERROR:
				output="ERROR\n";
				break;
			default:
				break;
			}
			current_state=next_state;
			if (current_state==ERROR)
			{
				break;
			}

		}
		code.close();
	
	}
	else
	{
		output="error, can't find the file\n";
		
	}
	return output;
}