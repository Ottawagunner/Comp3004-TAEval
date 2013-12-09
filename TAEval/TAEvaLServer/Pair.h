#ifndef KEY_FILE_PAIR
#define KEY_FILE_PAIR

#include <string>
#include <fstream>

#define EMPTY_STRING "BLANK"

class Pair{

	friend std::ostream& operator<<(std::ostream &, Pair const &);

public:
	Pair(std::string = EMPTY_STRING, std::string = EMPTY_STRING);
	Pair(const Pair &);
	Pair(std::ifstream &);
	~Pair();

	std::string getKey() const;
	std::string getFile() const;

	bool operator<(const Pair &);
	bool operator>(const Pair &);
	bool operator<=(const Pair &);
	bool operator>=(const Pair &);
	bool operator==(const Pair &);

private:
	std::string key;
	std::string filename;
};

#endif
//KEY_FILE_PAIR