
#include "Pair.h"
//#include <string>// do i need this?
//#include <fstream>//do i need this?
#include <iostream>

Pair::Pair(std::string arg1, std::string arg2) : key(arg1), filename(arg2){}

Pair::Pair(const Pair & rhs) {
	key = rhs.getKey();
	filename = rhs.getFile();
}

Pair::Pair(std::ifstream & myFile){
	getline(myFile, key);
	getline(myFile, filename);
}

Pair::~Pair(){}

std::string Pair::getKey() const{
	return key;
}

std::string Pair::getFile() const{
	return filename;
}

std::ostream& operator<<(std::ostream& out, Pair const & rhs){
	out << rhs.getKey() << std::endl << rhs.getFile() << std::endl;
	return out;
}

bool Pair::operator>(const Pair & rhs){
	return key > rhs.getKey();
}

bool Pair::operator<(const Pair & rhs){
	return key < rhs.getKey();
}

bool Pair::operator>=(const Pair & rhs){
	return key >= rhs.getKey();
}

bool Pair::operator<=(const Pair & rhs){
	return key <= rhs.getKey();
}

bool Pair::operator==(const Pair & rhs){
	return key == rhs.getKey();
}