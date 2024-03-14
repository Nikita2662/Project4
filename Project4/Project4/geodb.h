#ifndef GEODB_H
#define GEODB_H

#include "base_classes.h"
#include "HashMap.h"

class GeoDatabase : public GeoDatabaseBase
{
public:
	GeoDatabase();
	virtual ~GeoDatabase();
	virtual bool load(const std::string& map_data_file);
	virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
	virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
	virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const; 
private:
	// so far, these data members will have THEIR DESTRUCTORS CALLED - all good
	HashMap<vector<GeoPoint>> connectedPoints; // for each GeoPoint(toString), maps to vector of all Geopoints directly connected via segments
	HashMap<GeoPoint> pointsOfInterest; // for each point of interest (string), maps to GeoPoint location of that poi
	HashMap<string> streetNamesOfSegments; // for each segment (GeoPoint.tostring + GeoPoint.tostring), maps to its street name

	void createOneWayConnection(GeoPoint& source, GeoPoint& connected);
};

#endif // GEODB_H