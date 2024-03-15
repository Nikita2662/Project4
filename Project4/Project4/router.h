#ifndef ROUTER_H
#define ROUTER_H

#include "base_classes.h"
#include "geopoint.h"
#include <unordered_map>
#include <string>
using namespace std;

class Router : public RouterBase
{
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	double h(const GeoPoint& pt1, const GeoPoint& pt2) const;
	std::vector<GeoPoint> reconstructPath(const unordered_map<std::string, GeoPoint>& previousNodes, GeoPoint curr) const;
	// comparison struct  based on second elem of pair (priority)
	struct ComparePriority {
		bool operator()(const std::pair<GeoPoint, double>& lhs, const std::pair<GeoPoint, double>& rhs) const { return lhs.second > rhs.second; } // greater than, priority_queue is max heap
	};

	const GeoDatabaseBase& myDB;
};

#endif // ROUTER_H
