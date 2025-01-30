#pragma once
#include <string>

using namespace std;

template <typename K, typename V>
class DictionaryItem
{
private:
	K _key;
	V _value;
public:
	DictionaryItem();
	DictionaryItem(K key, V value);

	K getKey();
	V getValue();
	V *getValueAdress();

	void setValue(V value);
};

