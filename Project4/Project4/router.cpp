/*#include "router.h"
#include "HashMap.h"
#include "router.h"
#include "geotools.h"
#include "algorithm"
#include "queue"
using namespace std;

Router::Router(const GeoDatabaseBase& geo_db)
{
	// FILL IF NEEDED
}
Router::~Router()
{
	// FILL IF NEEDED
}

double Router::heuristic(const GeoPoint& pt1, const GeoPoint& pt2) const {
	return distance_earth_km(pt1, pt2);
}



std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	priority_queue<pair<GeoPoint, double>> range;

	range.push(pair<pt1, heuristic(pt1, pt2)>);
	// return vector of GeoPoints that lead from pt1 to pt2, inclusive
	// can contain midpoints + POIs as well as actual endpoints too (essentially, connectedPoints -- all the keys)
	

}
*/