#include "router.h"
#include "HashMap.h"
#include "base_classes.h"
#include "router.h"
#include "geotools.h"
#include "algorithm"
#include "queue"
#include <unordered_map>
using namespace std;

Router::Router(const GeoDatabaseBase& geo_db)
	: myDB(geo_db)
{}

Router::~Router() {}

double Router::h(const GeoPoint& pt1, const GeoPoint& pt2) const {
	return distance_earth_km(pt1, pt2);
}


std::vector<GeoPoint> Router::reconstructPath(const unordered_map<string, GeoPoint>& previousNodes, GeoPoint curr) const
{
	std::vector<GeoPoint> totalPath; // vectors of GeoPoints, from start point to end point
	totalPath.push_back(curr);

	// O(n)
	while (previousNodes.find(curr.to_string()) != previousNodes.end()) // while curr is in the cameFrom map
	{
		curr = previousNodes.find(curr.to_string())->second; // the GeoPoint this one came from
		totalPath.push_back(curr);
	}

	// O(n)
	std::reverse(totalPath.begin(), totalPath.end());
	return totalPath;
}


vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	priority_queue<pair<GeoPoint, double>, std::vector<std::pair<GeoPoint, double>>, ComparePriority> frontier;
	unordered_map<string, GeoPoint> cameFrom; // each GeoPoint (as string) maps to its previous GeoPoint (ON CHEAPEST PATH)
	unordered_map<string, double> costSoFar; 

	frontier.push(make_pair(pt1, h(pt1, pt2)));
	cameFrom[pt1.to_string()] = pt1;
	costSoFar[pt1.to_string()] = 0.0;

	while (!frontier.empty())
	{
		GeoPoint curr = frontier.top().first;
		frontier.pop();

		if (curr.to_string() == pt2.to_string())
			return reconstructPath(cameFrom, curr);

		vector<GeoPoint> pts = myDB.get_connected_points(curr);
		for (vector<GeoPoint>::iterator next = pts.begin(); next != pts.end(); next++) {
			double newCost = costSoFar[curr.to_string()] + h(curr, *next);
			if ((costSoFar.find(curr.to_string()) == costSoFar.end()) || (newCost < costSoFar[(*next).to_string()])) {
				costSoFar[(*next).to_string()] = newCost;
				double priority = newCost + h(*next, pt2);
				frontier.push(make_pair(*next, priority));
				cameFrom[(*next).to_string()] = curr;
			}
		}
	}
	return {};
}
