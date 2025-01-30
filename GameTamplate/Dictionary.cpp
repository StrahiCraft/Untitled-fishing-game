#include "Dictionary.h"

template<typename K, typename V>
Dictionary<K, V>::Dictionary() {
	_dictionary = vector<DictionaryItem<K, V>>();
}

template<typename K, typename V>
void Dictionary<K, V>::addItem(K key, V value) {
	if (containsKey(key)) {
		setValue(key, value);
		return;
	}

	_dictionary.push_back(DictionaryItem<K, V>(key, value));
}

template<typename K, typename V>
void Dictionary<K, V>::removeItem(K key) {
	DictionaryItem<K, V> *item = getItemIndex(key);

	_dictionary.erase(remove(_dictionary.begin(), _dictionary.end(), item), _dictionary.end());
}

template<typename K, typename V>
void Dictionary<K, V>::setValue(K key, V newValue) {
	int itemIndex = getItemIndex(key);

	if (itemIndex == -1) {
		return;
	}

	_dictionary[itemIndex].setValue(newValue);
}

template<typename K, typename V>
V Dictionary<K, V>::getValue(K key) {
	int itemIndex = getItemIndex(key);

	if (itemIndex == -1) {
		return V();
	}

	return _dictionary[itemIndex].getValue();
}

template<typename K, typename V>
int Dictionary<K, V>::getItemIndex(K key)
{
	for (int i = 0; i < _dictionary.size(); i++) {
		if (_dictionary[i].getKey() == key) {
			return i;
		}
	}
	return -1;
}

template<typename K, typename V>
bool Dictionary<K, V>::containsKey(K key)
{
	for (DictionaryItem<K, V> item : _dictionary) {
		if (item.getKey() == key) {
			return true;
		}
	}
	return false;
}
