#include "stdafx.h"

std::vector<double> ReadVectorFromStream(std::istream & inStream);

void WriteVectorToStream(std::vector<double> const & vectorToOut, std::ostream & outStream);

void TransformVector(std::vector<double> & vector);
