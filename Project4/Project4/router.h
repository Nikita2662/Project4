#ifndef ROUTER_H
#define ROUTER_H

#include "base_classes.h"

class Router : public RouterBase
{
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1,
		const GeoPoint& pt2) const;
private:
	double heuristic(const GeoPoint& pt1, const GeoPoint& pt2) const;
};

#endif // ROUTER_H
