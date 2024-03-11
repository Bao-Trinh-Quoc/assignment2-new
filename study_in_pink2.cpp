#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

/*===================== =Implement the MapElement class ============== */ 
MapElement::MapElement(ElementType in_type) : type(in_type) {}
MapElement::~MapElement()
{
    // Intentionally left empty
}
ElementType MapElement::getType() const
{
    return this->type;
}
/*======================= Implement the Map class ===================== */ 
// Constructor needs to create a 2D array which each element is an appropriate object.
// If this element is in the array_walls, this element is Wall object.
//  it is FakeWall object if it exists in array_fake_walls. The other elements are Path objects.
Map::Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls)
        : num_rows(num_rows), num_cols(num_cols)
{
    // Create a 2D array of MapElement pointers
    elements = new MapElement ** [num_rows];
    for (int i = 0; i < num_rows; i++)
    {
        elements[i] = new MapElement * [num_cols];
    }
    // Initialize the array with Path objects
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            elements[i][j] = new Path();
        }
    }
    // Replace appropriate elements with Wall objects
    for (int i = 0; i < num_walls; i++)
    {
        int row = array_walls[i].getRow();
        int col = array_walls[i].getCol();
        delete elements[row][col];
        elements[row][col] = new Wall();
    }
    // Replace appropriate elements with FakeWall objects
    for (int i = 0; i < num_fake_walls; i++)
    {
        int row = array_fake_walls[i].getRow();
        int col = array_fake_walls[i].getCol();
        delete elements[row][col];
        elements[row][col] = new FakeWall();
    }
}
Map::~Map()
{
    // Deallocate the 2D array
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            delete elements[i][j];
        }
        delete[] elements[i];
    }
    delete[] elements;
}

/*================ Implement of Position class ========================*/
/*
Public constructor with one parameter str_pos demonstrates a string of location
Format of str_pos is "(<r>,<c>)" with <r> and <c> are the values for row and column respectively.
Example: str_pos = "(1,15)"
*/
Position::Position(const string & str_pos)
{
    // Extract the row and column from the string
    int r, c;
    sscanf(str_pos.c_str(), "(%d,%d)", &r, &c);
    this->r = r;
    this->c = c;
}
string Position::str() const
{
    string str_pos = "(";
    str_pos += to_string(r);
    str_pos += ",";
    str_pos += to_string(c);
    str_pos += ")";

    return str_pos;
}
bool Position::isEqual(int in_r, int in_c) const
{
    return (r == in_r && c == in_c);
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////