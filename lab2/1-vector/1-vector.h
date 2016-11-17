#include "stdafx.h"

std::vector<double> readVectorFromStream(std::istream & inStream);

void writeVectorToStream(std::vector<double> const & vectorToOut, std::ostream & outStream);

void transformVector(std::vector<double> & vector);
