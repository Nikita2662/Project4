#include "geodb.h"
#include "geopoint.h"
#include "geotools.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

GeoDatabase::GeoDatabase() {}

GeoDatabase::~GeoDatabase() {}

void GeoDatabase::createOneWayConnection(GeoPoint& source, GeoPoint& connected)
{
	vector<GeoPoint>* connections = connectedPoints.find(source.to_string()); // vector of connected Geopoints to source
	if (connections == nullptr) { // first reading of "source" point so Node doesn't exist
		vector<GeoPoint> temp;
		connectedPoints.insert(source.to_string(), temp); // inserts the "source" point assoc. w empty vector
		connections = &temp;
	}
	connections->push_back(connected);
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
		/* MAP */ 
		// connected points
		GeoPoint endpt1(lat1, long1);
		GeoPoint endpt2(lat2, long2);

		createOneWayConnection(endpt1, endpt2);
		createOneWayConnection(endpt2, endpt1);

		// map street names of segments: bidirectional segment maps to street name
		streetNamesOfSegments.insert(endpt1.to_string() + ";" + endpt2.to_string(), streetName);
		streetNamesOfSegments.insert(endpt2.to_string() + ";" + endpt1.to_string(), streetName);
		/* END MAP */

		// number of points of interest on this segment
		int numPOIs;
		infile >> numPOIs;
		infile.ignore(10000, '\n'); // consume the rest of line, ignore

		if (numPOIs > 0) {
			/* MAP */
			GeoPoint mid = midpoint(endpt1, endpt2);

			// bidirectional connection: midpoint, endpt1 , then streetName assigned
			createOneWayConnection(endpt1, mid);
			createOneWayConnection(mid, endpt1);
			
			streetNamesOfSegments.insert(endpt1.to_string() + ";" + mid.to_string(), streetName);
			streetNamesOfSegments.insert(mid.to_string() + ";" + endpt1.to_string(), streetName);

			// bidirectional connection: midpoint, endpt2 , then streetName assigned
			createOneWayConnection(endpt2, mid);
			createOneWayConnection(mid, endpt2);

			streetNamesOfSegments.insert(endpt2.to_string() + ";" + mid.to_string(), streetName);
			streetNamesOfSegments.insert(mid.to_string() + ";" + endpt2.to_string(), streetName);
			/* END MAP */

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

				/* MAP */
				GeoPoint poi(plat, plong);
				pointsOfInterest.insert(locationName, poi);

				// bidirectional connection: midpoint, POI , then streetName assigned
				createOneWayConnection(mid, poi);
				createOneWayConnection(poi, mid);

				streetNamesOfSegments.insert(mid.to_string() + ";" + poi.to_string(), "a path");
				streetNamesOfSegments.insert(poi.to_string() + ";" + mid.to_string(), "a path");
				/* END MAP */
			}
		}
	}
	return true; // file was found, presumably "loaded" since formatted correctly
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const
{
	
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const
{
	vector<GeoPoint> n;
	return n;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	return "";
}