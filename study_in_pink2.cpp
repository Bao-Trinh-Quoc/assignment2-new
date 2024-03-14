#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////


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

/*  checks whether the location pos is a valid location for the object mv_obj to move to
    depended on type of mv_obj and the type of the element at pos
    Path: represents a path, objects can move on this element.  
    Wall: represents a wall, objects cannot move on this element.
    FakeWall: Because the criminal created the maze, he can recognize 
    the fake wall, and Sherlock, with his observation ability, can detect this fake wall.
    For Watson, FakeWall will be detected (and moved through) if Watson has EXP greater than
    the FakeWall’s required EXP. All other movable objects cannot be moved on this element.
*/
bool Map::isValid(const Position & pos, MovingObject * mv_obj) const
{
    int row = pos.getRow();
    int col = pos.getCol();
    // Check if the position is out of the map
    if (row < 0 || row >= num_rows || col < 0 || col >= num_cols)
    {
        return false;
    }
    // Check if the object is a Path
    if (elements[row][col]->getType() == PATH)
    {
        return true;
    }
    // Check if the object is a Wall
    if (elements[row][col]->getType() == WALL)
    {
        return false;
    }
    // Check if the object is a FakeWall
    if (elements[row][col]->getType() == FAKE_WALL)
    {
        // Check if the object is a MovingObject
        if (mv_obj != nullptr)
        {
            // Check if the object is a Watson
            if (mv_obj->getName() == "Watson")
            {
                // Check if the Watson's EXP is greater than the FakeWall's required EXP
                if (mv_obj->getExp() > dynamic_cast<FakeWall *>(elements[row][col])->getRegExp())
                {
                    return true;
                }
            }
            // Check if the object is a Sherlock
            else if (mv_obj->getName() == "Sherlock")
            {
                return true;
            }
            else if (mv_obj->getName() == "Criminal")
            {
                return true;
            }
        }
    }
    return false; 
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
const Position Position::npos = Position(-1, -1);

/*================ Implement of Sherlock class ========================*/
Sherlock::Sherlock(int index, const string & moving_rule, const Position & pos, Map * map, int init_hp, int init_exp)
        : MovingObject(index, pos, map, "Sherlock"), moving_rule(moving_rule) 
{
    // init_hp must in within range [0, 500]
    if (init_hp < 0)
        init_hp = 0;
    else if (init_hp > 500)
        init_hp = 500;
    // init_exp must in within range [0, 900]
    if (init_exp < 0)
        init_exp = 0;
    else if (init_exp > 900)
        init_exp = 900;
    
    hp = init_hp;
    exp = init_exp;
}       


/*
If the returned Position is not a valid position for this object to move then return npos of class Position.
Sherlock moves according to moving_rule. Each time the method is called, the next character is used as the direction of movement.
The first time the method is called, the first character will be used. When the last character is used, it will return to starting
the process from the first character.
Example: moving_rule = "LR", the order of characters used is: ’L’, ’R’, ’L’, ’R’, ’L’, ’R’,. .. 
*/
Position Sherlock::getNextPosition() 
{
    static int i = 0;
    int r = pos.getRow();
    int c = pos.getCol();
    char direction = moving_rule[i];
    i = (i + 1) % moving_rule.length(); // Update the index for the next call
    switch (direction)
    {
        case 'U':
            r--;
            break;
        case 'D':
            r++;
            break;
        case 'L':
            c--;
            break;
        case 'R':
            c++;
            break;
    }
    Position next_pos(r, c);
    if (map->isValid(next_pos, this))
    {
        return next_pos;
    }
    return Position::npos;
}
void Sherlock::move()
{
    Position next_pos = getNextPosition();
    if (next_pos != Position::npos)
    {
        pos = next_pos;
    }
}
//  Sherlock[index=<index>;pos=<pos>;moving_rule=<moving_rule>]
string Sherlock::str() const
{
    stringstream ss;
    ss << "Sherlock[index=" << index << ";pos=" << pos.str() << ";moving_rule=" << moving_rule << "]";
    return ss.str();
}

/*================ Implement of Watson class ========================*/
Watson::Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
        : MovingObject(index, pos, map, "Watson"), moving_rule(moving_rule)
{
    // init_hp must in within range [0, 500]
    if (init_hp < 0)
        init_hp = 0;
    else if (init_hp > 500)
        init_hp = 500;
    // init_exp must in within range [0, 900]
    if (init_exp < 0)
        init_exp = 0;
    else if (init_exp > 900)
        init_exp = 900;
    
    hp = init_hp;
    exp = init_exp;
}
Position Watson::getNextPosition()
{
    static int i = 0;
    int r = pos.getRow();
    int c = pos.getCol();
    char direction = moving_rule[i];
    i = (i + 1) % moving_rule.length(); // Update the index for the next call
    switch (direction)
    {
        case 'U':
            r--;
            break;
        case 'D':
            r++;
            break;
        case 'L':
            c--;
            break;
        case 'R':
            c++;
            break;
    }
    Position next_pos(r, c);
    if (map->isValid(next_pos, this))
    {
        return next_pos;
    }
    return Position::npos;
}
void Watson::move()
{
    Position next_pos = getNextPosition();
    if (next_pos != Position::npos)
    {
        pos = next_pos;
    }
}
//  Watson[index=<index>;pos=<pos>;moving_rule=<moving_rule>]
string Watson::str() const
{
    stringstream ss;
    ss << "Watson[index=" << index << ";pos=" << pos.str() << ";moving_rule=" << moving_rule << "]";
    return ss.str();
}

/*================ Implement of Criminal class ========================*/
Criminal::Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson)
        : MovingObject(index, pos, map, "Criminal"), sherlock(sherlock), watson(watson)
{}
/* The criminal has cameras monitoring both Sherlock and Watson in this maze.
   Therefore, unlike the detective couple’s way of moving, the criminal will
   choose the next moving location as the valid location with the greatest total distance to Sherlock
    and Watson. (Using Manhattan distance)

    In case there is more than 1 location with the greatest total distance to Sherlock and
    Waton, priority is given to choosing the location in the order of directions ’U’, ’L’, ’D’, ’R’.
*/
Position Criminal::getNextPosition()
{
    // U, L, D, R
    Position directions[] = {Position(-1, 0), Position(0, -1), Position(1, 0), Position(0, 1)};
    int maxDistance = -1;
    Position next_pos = pos;

    for (int i = 0; i < 4; i++)
    {
        // Calculate new Criminal position
        int xdir = pos.getRow() + directions[i].getRow();
        int ydir = pos.getCol() + directions[i].getCol();
        // Calculate distance between criminal - sherlock and criminal - watson
        int criminal_sherlock = abs(xdir - sherlock->getCurrentPosition().getRow()) 
                                + abs(ydir - sherlock->getCurrentPosition().getCol());
        int criminal_watson   = abs(xdir - watson->getCurrentPosition().getRow()) 
                                + abs(ydir - watson->getCurrentPosition().getCol());
        // Calculate total distance
        int totalDistance = criminal_sherlock + criminal_watson;
        // Update maxDistance and next position
        if (totalDistance > maxDistance)
        {
            Position temp = Position(xdir, ydir);
            if (map->isValid(temp, this))
            {
                maxDistance = totalDistance;
                next_pos = temp;
            }
        }
    }
    return next_pos;
}
void Criminal::move()
{}
string Criminal::str() const
{
    stringstream ss;
    ss << "Criminal[index=" << index << ";pos=" << pos.str() << "]";
    return ss.str();
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////