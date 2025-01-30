#include "DictionaryItem.h"

template<typename K, typename V>
DictionaryItem<K, V>::DictionaryItem()
{

}

template<typename K, typename V>
DictionaryItem<K, V>::DictionaryItem(K key, V value) : _key(key), _value(value)
{
	
}

template<typename K, typename V>
K DictionaryItem<K, V>::getKey()
{
	return _key;
}

template<typename K, typename V>
V DictionaryItem<K, V>::getValue()
{
	return _value;
}

template<typename K, typename V>
V* DictionaryItem<K, V>::getValueAdress()
{
	return &_value;
}

template<typename K, typename V>
void DictionaryItem<K, V>::setValue(V value)
{
	_value = value;
}
