#include <iostream>

using namespace std;

class String {
private:
	char* data;
	int len;
	int sapacity{ 15 };

public:
	void newCap(int newCapacity) {
		if (newCapacity > sapacity) {
			sapacity = newCapacity + 15;
			char* newData = new char[sapacity + 1];
			if (data) {
				strcpy_s(newData, sapacity + 1, data);
				delete[] data;
			}
			data = newData;
		}
	}

	String() : len(0), sapacity(15), data(nullptr) {};

	String(const string str) {
		char i = str[0];
		len = 0;

		while (i != '\0') {
			i = str[len];
			len++;
		}

		data = new char[len + 1];
		for (int i = 0; i < len; i++) {
			data[i] = str[i];
		}
	}


	String(const char* str) : len(0), sapacity(15), data(nullptr) {
		int length = strlen(str);

		if (length > 15) {
			sapacity = length + 15;
		}

		data = new char[sapacity + 1];
		strcpy_s(data, sapacity + 1, str);
		len = length;
	}


	String(int size, char symbol) : len(size), sapacity(15), data(nullptr) {
		if (size > sapacity) {
			sapacity = size + 15;
		}

		data = new char[sapacity + 1];

		for (int i = 0; i < len; i++) {
			data[i] = symbol;
		}

		data[len] = '\0';
	}


	~String() {
		delete[] data;
	}

	int size() const {
		return len;
	}

	int capacity() const {
		return sapacity;
	}

	void clear() {
		delete[] data;
		len = 0;
		data = nullptr;
	}

	char at(int index) const {
		if (index < 0 || index >= len) 	cout << "Error :: Index out of range" << endl;

		else return data[index];
	}

	void insert(char symb) {
		newCap(len + 1);
		data[len] = symb;
		len++;
		data[len] = '\0';
	}

	void insert(int index, char symb) {
		if (index < 0 || index > len) {
			cout << "Error :: Index out of range" << endl;
		}

		newCap(len + 1);
		for (int i = 0; i <= index; i++)
		{
			if (i == index) data[i] = symb;
			else data[i + 1] = data[i];
		}

		for (int i = index + 1; i < strlen(data); i++)
		{
			data[i] = data[i];

		}

		data[index] = symb;
		len++;
		data[len] = '\0';
	}

	void insert(int index, char symb, int count) {
		if (index < 0 || index > len) {
			cout << "Error :: Index out of range" << endl;
		}

		newCap(len + count);

		for (int i = 0; i <= index; i++)
		{
			if (i == index) break;
			else data[i] = data[i];
		}

		for (int i = index; i < index + count; i++)
		{
			data[i] = symb;
		}

		for (int i = index + count; i < strlen(data); i++)
		{
			data[i] = data[i];
		}
		len += count;
		data[len] = '\0';
	}

	void insert(int index, const char* substr) {
		if (index < 0 || index > len) {
			cout << "Error :: Index out of range" << endl;
			return;
		}

		int sublen = strlen(substr);
		newCap(len + sublen);

		for (int i = len; i >= index; i--)
		{
			data[i + sublen] = data[i];
		}

		for (int i = index, j = 0; j < sublen; i++, j++)
		{
			data[i] = substr[j];
		}

		len += sublen;
		data[len] = '\0';
	}

	void insert(int index, const string substr) {
		int sublen = substr.length();
		newCap(len + sublen);

		for (int i = len; i >= index; i--)
		{
			data[i + sublen] = data[i];
		}

		for (int i = index, j = 0; j < sublen; i++, j++)
		{
			data[i] = substr[j];
		}

		len += sublen;
		data[len] = '\0';
	}

	void insert(int index, const String& substr) {
		insert(index, substr.data);
	}

	int find(const string substr) const {
		char i = substr[0];
		int leng = 0;

		while (i != '\0') {
			i = substr[len];
			leng++;
		}

		int searchlen = len - leng + 1;
		for (int i = 0; i < searchlen; i++) {
			int k;
			for (int j = 0; j < leng; j++, k++) {
				if (data[i + j] != substr[i]) {
					break;
				}
			}
			if (k == leng) {
				return i;
			}
		}
		cout << "Error :: No such substr is find" << endl;
		return 0;
	}

	int rfind(const string substr) const {
		char i = substr[0];
		int leng = 0;

		while (i != '\0') {
			i = substr[len];
			leng++;
		}

		int searchlen = len - leng + 1;

		for (int i = searchlen - 1; i >= 0; i--) {
			int j;
			for (j = 0; j < leng; j++) {
				if (data[i + j] != substr[j]) {
					break;
				}
			}
			if (j == leng) {
				return i;
			}
		}
		cout << "Error :: No such substr is find" << endl;
		return 0;

	}


	String operator=(const string str) {
		delete[] data;
		len = str.length();
		sapacity = str.capacity();
		data = new char[sapacity + 1];

		for (int i = 0; i < len; i++)
		{
			data[i] = str[i];
		}

		return *this;
	}

	String& operator=(const char* str) {
		delete[] data;
		len = strlen(str);
		int cp = 15;
		if (len > cp) cp = len + 15;

		sapacity = cp;

		data = new char[sapacity + 1];
		strcpy_s(data, sapacity + 1, str);

		return *this;
	}


	friend bool operator>(const String& right, const String& left) {
		return strcmp(right.data, left.data) > 0;
	}

	friend bool operator<(const String& right, const String& left) {
		return strcmp(right.data, left.data) < 0;
	}

	friend bool operator>=(const String& right, const String& left) {
		return strcmp(right.data, left.data) >= 0;
	}

	friend bool operator<=(const String& right, const String& left) {
		return strcmp(right.data, left.data) <= 0;
	}

	friend bool operator==(const String& right, const String& left) {
		return strcmp(right.data, left.data) == 0;
	}

	friend bool operator!=(const String& right, const String& left) {
		return strcmp(right.data, left.data) != 0;
	}


	String operator+(const String& other) const {
		String result;
		result.newCap(len + other.len);
		strcpy_s(result.data, len + other.len, data);
		strcat_s(result.data, len + other.len, other.data);
		result.len = len + other.len;
		return result;
	}

	String& operator+=(const String& other) {
		newCap(len + other.len);
		strcat_s(data, (len + other.len + 1), other.data);
		len += other.len;
		return *this;
	}


	String(const String& str) :data{ new char[str.len] }, len{ str.len }, sapacity{ str.sapacity } {
		for (size_t i = 0; i < len; i++)
		{
			data[i] = str.data[i];
		}
	}

	String(String&& str) : len(str.len + 1), sapacity(str.sapacity), data(str.data) {
		str.len = 0;
		str.sapacity = 0;
		str.data = nullptr;
	}


	char& operator[](int index) {
		if (index < 0 || index >= len) {
			cout << "Error :: Index out of range" << endl;
		}
		return data[index];
	}

	friend ostream& operator<<(ostream& output, const String& str) {
		output << "Your text: ";
		for (int i = 0; i < str.len; i++)
		{
			output << str.data[i];
		}

		output << endl << "Lenght: " << str.len << endl;
		output << "Capacity: " << str.sapacity << endl;

		return output;
	}

	friend istream& operator>>(istream& input, String& str) {
		delete[] str.data;

		while (strlen(str.data) > str.sapacity) {
			str.sapacity += 15;
		}

		str.data = new char[str.sapacity];

		input.getline(str.data, str.sapacity);

		return input;
	}

};

int main() {
	String str(3, 'a');
	cout << str;
	const string s = "tresh";
	string str1("ogo vot eto ti snaiper");
	//str.insert(1, "lala");

	str.insert(0,str1);
	cout << str;
}
