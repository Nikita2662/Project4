#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <functional>
#include <string>
using namespace std;

template<typename T>
class HashMap
{
public:
	HashMap(double max_load = 0.75); // constructor
	~HashMap(); // destructor; deletes all of the items in the hashmap
	int size() const; // return the number of associations in the hashmap
	// The insert method associates one item (key) with another (value).
		// If no association currently exists with that key, this method inserts
		// a new association into the hashmap with that key/value pair. If there is
		// already an association with that key in the hashmap, then the item
		// associated with that key is replaced by the second parameter (value).
		// Thus, the hashmap must contain no duplicate keys.
	void insert(const std::string& key, const T& value);
	// Defines the bracket operator for HashMap, so you can use your map like this:
		// your_map["david"] = 2.99;
		// If the key does not exist in the hashmap, this will create a new entry in
		// the hashmap and map it to the default value of type T (0 for builtin types).
		// It returns a reference to the newly created value in the map.
	T& operator[](const std::string& key);
	// If no association exists with the given key, return nullptr; otherwise,
		// return a pointer to the value associated with that key. This pointer can be
		// used to examine that value within the map.
	const T* find(const std::string& key) const;
	// If no association exists with the given key, return nullptr; otherwise,
		// return a pointer to the value associated with that key. This pointer can be
		// used to examine that value or modify it directly within the map.
	T* find(const std::string& key) {
		const auto& hm = *this;
		return const_cast<T*>(hm.find(key));
	}
private:
	struct Node
	{
		Node(const string k, const T& v, Node* ptr = nullptr)
			: key(k), value(v), next(ptr)
		{}

		string key;
		T value;
		Node* next;
	};

	// returns subscript of bucket that inputted key (string) will be stored in w/ its value
	int hashFunc(const string s) const; // hashes a string to int, using STL's hash function

	HashMap(const HashMap&) = delete; HashMap& operator=(const HashMap&) = delete;
	double maxLoad;
	int numAssociations;
	int numBuckets;
	vector<Node*> buckets;
};

// TEMPLATE METHOD IMPLEMENTATIONS
template<typename T> 
HashMap<typename T>::HashMap(double max_load) // constructor
	: maxLoad(max_load), numAssociations(0)
{
	for (int i = 0; i < 10; i++)
	{
		buckets.push_back(nullptr); // adds 10 elems to buckets, each set to nullptr
		numBuckets++;
	}
}

template<typename T> 
HashMap<typename T>::~HashMap() // destructor; deletes all of the items in the hashmap
{
	for (size_t k = 0; k < numBuckets; k++) // iterate through each bucket
		while (buckets[k] != nullptr) // iterate through the linked list by pointer
		{
			Node* temp = buckets[k];
			buckets[k] = buckets[k]->next;
			delete temp;
		}
	numAssociations = 0;
}

template<typename T>
int HashMap<typename T>::size() const // return the number of associations in the hashmap
{ return numAssociations; }

// returns subscript of bucket that inputted key (string) will be stored in w/ its value
template<typename T>
int HashMap<typename T>::hashFunc(const string s) const
{
	unsigned int hashedToInt = hash<string>()(s);
	return (hashedToInt % numBuckets); 
}

// The insert method associates one item (key) with another (value).
	// If no association currently exists with that key, this method inserts
	// a new association into the hashmap with that key/value pair. If there is
	// already an association with that key in the hashmap, then the item
	// associated with that key is replaced by the second parameter (value).
	// Thus, the hashmap must contain no duplicate keys.
template<typename T>
void HashMap<typename T>::insert(const std::string& key, const T& value)
{
	int subscript = hashFunc(key);

	for (Node* p = buckets[subscript]; p != nullptr; p = p->next) // iterate through all Nodes
	{
		if (p->key == key) {
			p->value = value; // update if key already exists
			return;
		}
	}
	// otherwise, no association currently exists w this key:
	numAssociations++; // new key-value pair to be added

	// IF REHASH REQUIRED:
	if (numAssociations / numBuckets > maxLoad) { // if load factor too big
		int oldNumBuckets = numBuckets;
		numBuckets *= 2;
		vector<Node*> bigger(numBuckets, nullptr);

		for (int i = 0; i < oldNumBuckets; i++) { // iterate through old buckets
			if (buckets[i] == nullptr) continue;

			// all the Nodes belong where this Node's key belongs
			int biggerSS = hashFunc(buckets[i]->key);
			bigger[biggerSS] = buckets[i];
		}

		buckets.swap(bigger); // bigger, which now contains old Buckets, will be deleted out of scope

		subscript = hashFunc(key);
	}
	// end "IF REHASH REQUIRED" case

	// insert to front of LL
	Node* temp = buckets[subscript];
	buckets[subscript] = new Node(key, value, temp);
}

// Defines the bracket operator for HashMap, so you can use your map like this:
	// your_map["david"] = 2.99;
	// If the key does not exist in the hashmap, this will create a new entry in
	// the hashmap and map it to the default value of type T (0 for builtin types).
	// It returns a reference to the newly created value in the map.
template<typename T>
T& HashMap<typename T>::operator[](const std::string& key)
{
	T* val = find(key);
	if (val == nullptr) { // no assoc w this key, not in hashmap
		insert(key, T());
		val = find(key);
	}
	return *val; // return value assoc. w key BY REFERENCE
}

// If no association exists with the given key, return nullptr; otherwise,
	// return a pointer to the value associated with that key. This pointer can be
	// used to examine that value within the map.
template<typename T>
const T* HashMap<typename T>::find(const std::string& key) const
{
	int subscript = hashFunc(key); // subscript of bucket key should be in

	for (Node* p = buckets[subscript]; p != nullptr; p = p->next) { // traverses every Node starting w the first
		if (p->key == key) return &(p->value);
	}
	return nullptr;
}

#endif // HASNMAP_H