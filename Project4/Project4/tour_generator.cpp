#include "tour_generator.h"
#include "HashMap.h"
#include "tourcmd.h"
#include "base_classes.h"
#include "geotools.h"
using namespace std;

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router)
	: myDB(geodb), rout(router)
{}

TourGenerator::~TourGenerator()
{}

std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const
{
	vector<TourCommand> result;
	for (int i = 0; i < stops.size(); i++) {
		string poi, talkPoints;
		stops.get_poi_data(i, poi, talkPoints);

		TourCommand cmd1;
		cmd1.init_commentary(poi, talkPoints);
		result.push_back(cmd1);

		if (i == stops.size() - 1) break; // last stop

		// if at least 1 more POI:
		GeoPoint currPOI = GeoPoint();
		myDB.get_poi_location(poi, currPOI);

		GeoPoint nextPOI = GeoPoint();
		string poi2, talkPoints2;
		stops.get_poi_data(i + 1, poi2, talkPoints2);
		myDB.get_poi_location(poi2, nextPOI);

		// generate point by point route
		vector<GeoPoint> myRoute = rout.route(currPOI, nextPOI);

		// generate TourCommands for this path
		for (int i = 1; i < myRoute.size(); i++) {
			// proceed command
			TourCommand pcmd;

			double angle = angle_of_line(myRoute[i - 1], myRoute[i]);
			string dirTravel;
			if (angle < 22.5) dirTravel = "east";
			else if (angle < 67.5) dirTravel = "northeast";
			else if (angle < 112.5) dirTravel = "north";
			else if (angle < 157.5) dirTravel = "northwest";
			else if (angle < 202.5) dirTravel = "west";
			else if (angle < 247.5) dirTravel = "southwest";
			else if (angle < 292.5) dirTravel = "south";
			else if (angle < 337.5) dirTravel = "southeast";
			else dirTravel = "east";

			pcmd.init_proceed(dirTravel, myDB.get_street_name(myRoute[i - 1], myRoute[i]),
				distance_earth_miles(myRoute[i - 1], myRoute[i]), myRoute[i - 1], myRoute[i]);
			result.push_back(pcmd);

			// turn command?
			double turnAngle = angle_of_turn(myRoute[i - 1], myRoute[i], myRoute[i + 1]);
			if (i != myRoute.size() - 1
				&& (myDB.get_street_name(myRoute[i - 1], myRoute[i]) != myDB.get_street_name(myRoute[i], myRoute[i + 1]))
				&& turnAngle != 0)
			{
				TourCommand tcmd;

				string dirTurn = "invalid angle";
				if (turnAngle >= 1 && turnAngle < 180) dirTurn = "left";
				else if (turnAngle >= 180 && turnAngle <= 359) dirTurn = "right";

				tcmd.init_turn(dirTurn, myDB.get_street_name(myRoute[i], myRoute[i+1])); // turn "onto" blah
				result.push_back(tcmd);
			}
		}
	}
	return result;
}