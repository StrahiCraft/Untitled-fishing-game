#pragma once
#include "DictionaryItem.h"
#include "DictionaryItem.cpp"
#include <vector>
#include <algorithm>

template <typename K, typename V>
class Dictionary
{
private:
	vector<DictionaryItem<K, V>> _dictionary;
	int getItemIndex(K key);
public:
	Dictionary();
	void addItem(K key, V value);
	void removeItem(K key);
	void setValue(K key, V newValue);
	int getItemCount();
	V getValue(K key);
	V getValue(int index);
	K getKey(int index);
	bool containsKey(K key);
};
