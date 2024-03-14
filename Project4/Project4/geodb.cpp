#include "geodb.h"
#include "HashMap.h"
#include "geopoint.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

GeoDatabase::GeoDatabase()
{

}
GeoDatabase::~GeoDatabase()
{

}

bool GeoDatabase::load(const std::string& map_data_file)
{
	ifstream infile(map_data_file);
	if (!infile) {
		cerr << "Error opening this map data file" << endl;
		return false;
	}

	std::string streetName;
	while (getline(infile, streetName)) // read and process each line of file until end
	{
		// GeoPoint endpoints of segment
		std::string line, lat1, long1, lat2, long2;
		getline(infile, line);
		istringstream iss(line); 
		if (!(iss >> lat1 >> long1 >> lat2 >> long2)) {
			cerr << "Error with reading GeoPoint coordinates" << endl;
			continue;
		}	

		// number of points of interest on this segment
		int numPOIs;
		infile >> numPOIs;
		infile.ignore(10000, '\n'); // consume the rest of line, ignore
		
		// points of interest
		std::string locationName;
		for (int i = 0; i < numPOIs; i++) { // for each POI
			getline(infile, locationName, '|'); // use '|' as delimiter, next input operation begins after it & it is not stored
			
			std::string line2, plat, plong;
			getline(infile, line2);
			istringstream iss2(line2);
			if (!(iss2 >> plat >> plong)) {
				cerr << "Error with reading point of interest coordinates" << endl;
				continue;
			}
			
			// STORE IN MAP 
		}
	}
	return true; // file was found, presumably "loaded" since formatted correctly
}


bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const;
std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const;
std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;