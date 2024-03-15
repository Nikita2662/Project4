#ifndef TOURGENERATOR_H
#define TOURGENERATOR_H

#include "base_classes.h"
class TourGenerator : public TourGeneratorBase
{
public:
	TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
	virtual ~TourGenerator();
	virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
	const GeoDatabaseBase& myDB;
	const RouterBase& rout;
};

#endif // TOURGENERATOR_H