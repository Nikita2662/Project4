#include "HashMap.h"
#include <iostream>
#include <cassert>

void hashtester()
{
	// Define a hashmap that maps strings to doubles and has a maximum
	// load factor of 0.2. It will initially have 10 buckets when empty.
	HashMap<double> nameToGPA(0.2);
	assert(nameToGPA.size() == 0);
	// Add new items to the hashmap
	nameToGPA.insert("Carey", 3.5); // Carey has a 3.5 GPA
	assert(nameToGPA.size() == 1);
	nameToGPA.insert("David", 2.99); // David needs to up his game
	assert(nameToGPA.size() == 2);

	// You can also use brackets like C++'s unordered_map!
	nameToGPA["Annie"] = 3.85; // Adds Annie, who has the highest GPA of all.
	// Since adding Annie would push the load factor from 0.2 to 0.3, exceeding the
	// maximum load factpr of 0.2, adding Annie caused the hashmap to increase the
	// number of buckets, forcing a rehash of all items.
	assert(nameToGPA.size() == 3);
	double* davidsGPA = nameToGPA.find("David");
	if (davidsGPA != nullptr)
		*davidsGPA = 3.1; // after a re-grade of David's exam, update 2.99 -> 3.1
	nameToGPA.insert("Carey", 4.0); // Carey deserves a 4.0
	cout << *(nameToGPA.find("Carey")) << endl;
	// sees if linda is in the map; if not, creates a new entry for linda in map
	cout << nameToGPA["Linda"]; // prints zero
	assert(nameToGPA.size() == 4);
	cout << endl << "All tests passed";
}

int main()
{
	hashtester();
}