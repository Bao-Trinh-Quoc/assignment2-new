#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Implement the MapElement class
MapElement::MapElement(ElementType in_type) : type(in_type) {}
MapElement::~MapElement()
{
    // Intentionally left empty
}
ElementType MapElement::getType() const
{
    return this->type;
}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////