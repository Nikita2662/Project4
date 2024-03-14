#include "HashMap.h"
#include "geodb.h"
#include "geopoint.h"
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

void loadtester()
{
	GeoDatabase g;
	g.load("C:/Nikita/College/CS32/PROJ 4/Project4/Project4/tiny1.txt");
}

void getpoitester()
{
	GeoDatabase g;
	g.load("mapdata.txt"); // assume this works to avoid error checking
	GeoPoint p;
	if (g.get_poi_location("Diddy Riese", p))
		cout << "The PoI is at " << p.sLatitude << ", "
		<< p.sLongitude << endl;
	else
		cout << "PoI not found!\n";
}

void getstreetnametester()
{
	GeoDatabase g;
	g.load("mapdata.txt"); // assume this works to avoid error checking

	/* WORKS
	GeoPoint p1("34.0732851", "-118.4931016");
	GeoPoint p2("34.0736122", "-118.4927669");
	cout << g.get_street_name(p1, p2) << endl; // writes "Glenmere Way"
	cout << g.get_street_name(p2, p1); // writes "Glenmere Way"
	*/

	/* WORKS
	GeoPoint p1("34.0601422", "-118.4468929");
	GeoPoint p2("34.0600768", "-118.4467216");
	cout << g.get_street_name(p1, p2) << endl; // writes "a path"
	cout << g.get_street_name(p2, p1); // writes "a path"
	*/

	/* WORKS
	GeoPoint p1("34.0602175", "-118.4464952");
	GeoPoint p2("34.0600768", "-118.4467216");
	cout << g.get_street_name(p1, p2) << endl; // writes "Kinross Avenue"
	cout << g.get_street_name(p2, p1); // writes "Kinross Avenue"
	*/
}

void getconnectedpointstester()
{
	GeoDatabase g;
	g.load("C:/Nikita/College/CS32/PROJ 4/Project4/Project4/mapdata.txt"); // assume this works to avoid error checking
	
	/*std::vector<GeoPoint> pts = g.get_connected_points(GeoPoint("34.0731003", "-118.4931016"));
	if (pts.empty())
		cout << "There are no points connected to your specified point\n" << endl;
	else {
		for (const auto p : pts)
			cout << p.sLatitude << ", " << p.sLongitude << endl;
	}*/
	
	std::vector<GeoPoint> pts = g.get_connected_points(GeoPoint("34.0736122", "-118.4927669"));
	if (pts.empty())
		cout << "There are no points connected to your specified point\n" << endl;
	else {
		for (const auto p : pts)
			cout << p.sLatitude << ", " << p.sLongitude << endl;
	}

	pts = g.get_connected_points(GeoPoint("34.0601422", "-118.4468929"));
	if (pts.empty())
		cout << "There are no points connected to your specified point\n" << endl;
	else {
		for (const auto p : pts)
			cout << p.sLatitude << ", " << p.sLongitude << endl;
	}

	pts = g.get_connected_points(GeoPoint("34.0600768", "-118.4467216"));
	if (pts.empty())
		cout << "There are no points connected to your specified point\n" << endl;
	else {
		for (const auto p : pts)
			cout << p.sLatitude << ", " << p.sLongitude << endl;
	}
}

int main()
{
	hashtester();   // WORKS
	//loadtester();   // ??????
	//getpoitester(); // WORKS
	getconnectedpointstester();
	//getstreetnametester(); // WORKS
}