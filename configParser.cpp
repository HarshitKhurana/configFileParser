#include<iostream>
#include<stdlib.h>
#include<fstream>

using namespace std;

class KeyValue  {
	public:
	string key;
	string value;
		
		KeyValue(string a , string b)  {
			this->key = a;
			this->value = b;
		}

		KeyValue(char *a, char *b)  {
			this->key = string(a);
			this->value = string(b);
		}
};

KeyValue * Parse(string singleLine) {
	string nullValue("Null");
	if (singleLine[0] == '#' || singleLine[0] == '\n' || singleLine[0] == '\0' )
		return  new KeyValue(nullValue, nullValue);

	int length=singleLine.length();
	char key[length] , value[length];
	int delimiterEncountered=0 , index1=0,index2=0;
	
	for ( int i = 0 ; i < length ; i ++){
		if (singleLine[i] == '=') {
			delimiterEncountered =1;
			i++;			
		}
		if (!delimiterEncountered)  {
			key[index1] = singleLine[i];
			index1++;
		}
		else  {
			value[index2]=singleLine[i];
			index2++;
		}
	}
	
	key[index1]='\0';
	value[index2]='\0';
	if (!delimiterEncountered)	{
		// cerr << "[#] No delimiter found - error"<<endl;
		return  new KeyValue(string("corrupt"), nullValue);
	}
	// cout << "[*] Returning "<<key<<":"<<value<<endl;

	return new KeyValue(key,value);
}

int main( int argc,  char *argv[]){
/*
	comile as : g++ configParser.cpp -o configParser
	run as : ./configParser <configFile>
*/ 
	cout <<"[*] The delimiter used in config file must be '=' and comments should start with'#'"<<endl;
	if (argc != 2){
		cerr << "[#] Usage : \n\t"<<argv[0]<<"<configfile>"<<endl;
		exit(1);
	}
	string filename (argv[1]);
    Reader file_rdr;
	
	for (std:: string line; getline(infile , line);) {
		// cout << "[*] Line is :^^^"<<line<<"%%%"<<endl;
		KeyValue *obj = Parse(line);
		if (obj->key == string("Null"))
			continue;
		if (obj->key == string("corrupt")){
		cerr << "\t[#] Error in parsing file: "<< filename<<" , file format not correct" << endl;
    cerr <<"\t[#] "<<"Error here : "<<line<<endl;
			exit(1);	// Non-zero exit code to indicate error in config file
		}
		cout <<"[*] "<<obj->key << ":"<<obj->value<<endl;
	}
  // return success
  exit (0); 
}
