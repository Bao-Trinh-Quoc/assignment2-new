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
        int fakeWallExp = (row * 257 + col * 139 + 89) % 900 + 1;
        elements[row][col] = new FakeWall(fakeWallExp);
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
            }   // Check if the object is a Criminal
            else if (mv_obj->getName() == "Criminal")
            {
                return true;
            }
            else if (mv_obj->getName() == "RobotC" || mv_obj->getName() == "RobotS" || mv_obj->getName() == "RobotW"
                    || mv_obj->getName() == "RobotSW")
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
bool Position::isEqual(const Position & pos) const
{
    return (r == pos.r && c == pos.c);
}
const Position Position::npos = Position(-1, -1);

/*================ Implement of Sherlock class ========================*/
Sherlock::Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
        : MovingObject(index, init_pos, map, "Sherlock"), moving_rule(moving_rule) 
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
The first time the method is called, the first character will be used. 
When the last character is used, it will return to starting the process from the first character.
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
        : MovingObject(index, init_pos, map, "Watson"), moving_rule(moving_rule)
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
        : MovingObject(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson)
{}
/*  The criminal has cameras monitoring both Sherlock and Watson in this maze.
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
            else 
                return Position::npos;
        }
    }
    return next_pos;
}
void Criminal::move()
{
    Position next_pos = getNextPosition();
    if (next_pos != Position::npos)
    {
        prev_pos = pos;     // Save the previous position
        pos = next_pos;
    }
}
Position Criminal::getPreviousPosition() const
{
    return prev_pos;
}
// Criminal[index=<index>;pos=<pos>]
string Criminal::str() const
{
    stringstream ss;
    ss << "Criminal[index=" << index << ";pos=" << pos.str() << "]";
    return ss.str();
}

/*================ Implement of ArrayMovingObject class ========================*/
ArrayMovingObject::ArrayMovingObject(int capcity)
{
    this->capacity = capcity;
    count = 0;
    arr_mv_objs = new MovingObject * [capcity];
}
ArrayMovingObject::~ArrayMovingObject()
{
    for (int i = 0; i < capacity; i++)
    {
        delete arr_mv_objs[i];
    }
    delete[] arr_mv_objs;
}
bool ArrayMovingObject::add(MovingObject * mv_obj)
{
    if (!isFull())
    {
        arr_mv_objs[count++] = mv_obj;
        return true;
    }

    return false;
}
/*  The str method returns a string representing information for ArrayMovingObject.
    The format of the returned string is:
    Array[count=<count>;capacity=<capacity>;<MovingObject1>;...]
    MovingObject1,...: These are the MovingObjects in the array, respectively. Each
    MovingObject is printed in the corresponding format of that object type.
    Example:
    ArrayMovingObject[count=3;capacity=10;Criminal[index=0;pos=(8,9)];
    Sherlock[index=1;pos=(1,4);moving_rule=RUU]; Watson[index=2;pos=(2,1);moving_rule=LU]]
*/
string ArrayMovingObject::str() const
{
    stringstream ss;
    ss << "ArrayMovingObject[count=" << count << ";capacity=" << capacity << ";";
    for (int i = 0; i < count; i++)
    {
        ss << arr_mv_objs[i]->str();
        if (i < count - 1)
        {
            ss << ";";
        }
    }
    ss << "]";
    return ss.str();

}

/*================ Implement of Configuration class ========================*/
/* 
    The file consists of lines, each line can be one of the following formats. Note that the order of lines may vary.
    ...
*/
Configuration::Configuration(const string & filepath)
{
    ifstream file(filepath);
    if (!file)
    {
        cout << "Cannot open file " << filepath << endl;
        return;
    }
    string line;
    // why need buffer ? Readme !! vdry interesting bugs about sscanf that i don't know --- 16/03/2024
    char buffer[256];   // temp buffer
    while(getline(file, line))
    {
        if (line.find("MAP_NUM_ROWS=") != string::npos)
        {
            sscanf(line.c_str(), "MAP_NUM_ROWS=%d", &map_num_rows);
        }
        else if (line.find("MAP_NUM_COLS=") != string::npos)
        {
            sscanf(line.c_str(), "MAP_NUM_COLS=%d", &map_num_cols);
        }
        else if (line.find("MAX_NUM_MOVING_OBJECTS=") != string::npos)
        {
            sscanf(line.c_str(), "MAX_NUM_MOVING_OBJECTS=%d", &map_num_moving_objects);
        }
        else if (line.find("NUM_WALLS=") != string::npos)
        {
            sscanf(line.c_str(), "NUM_WALLS=%d", &num_walls);
            arr_walls = new Position[num_walls];
        }
        else if (line.find("ARRAY_WALLS=") != string::npos)
        {
            int r, c;
            int i = 0;
            istringstream ss(line);
            string token;
            while (getline(ss, token, ';'))
            {
                if (token.find("ARRAY_WALLS=") != string::npos)
                {
                    continue;
                }
                sscanf(token.c_str(), "(%d,%d)", &r, &c);
                arr_walls[i++] = Position(r, c);
            }
        }
        else if (line.find("NUM_FAKE_WALLS=") != string::npos)
        {
            sscanf(line.c_str(), "NUM_FAKE_WALLS=%d", &num_fake_walls);
            arr_fake_walls = new Position[num_fake_walls];
        }
        else if (line.find("ARRAY_FAKE_WALLS=") != string::npos)
        {
            int r, c;
            int i = 0;
            istringstream ss(line);
            string token;
            while (getline(ss, token, ';'))
            {
                if (token.find("ARRAY_FAKE_WALLS=") != string::npos)
                {
                    continue;
                }
                sscanf(token.c_str(), "(%d,%d)", &r, &c);
                arr_fake_walls[i++] = Position(r, c);
            }
        }
        else if (line.find("SHERLOCK_MOVING_RULE=") != string::npos)
        {
            // sscanf(line.c_str(), "SHERLOCK_MOVING_RULE=%s", sherlock_moving_rule);
            sscanf(line.c_str(), "SHERLOCK_MOVING_RULE=%s", buffer);
            sherlock_moving_rule = buffer; // Assign to std::string 
        }
        else if (line.find("SHERLOCK_INIT_POS=") != string::npos)
        {
            int r, c;
            sscanf(line.c_str(), "SHERLOCK_INIT_POS=(%d,%d)", &r, &c);
            sherlock_init_pos = Position(r, c);
        }
        else if (line.find("SHERLOCK_INIT_HP=") != string::npos)
        {
            sscanf(line.c_str(), "SHERLOCK_INIT_HP=%d", &sherlock_init_hp);
        }
        else if (line.find("SHERLOCK_INIT_EXP=") != string::npos)
        {
            sscanf(line.c_str(), "SHERLOCK_INIT_EXP=%d", &sherlock_init_exp);
        }
        else if (line.find("WATSON_MOVING_RULE=") != string::npos)
        {
            sscanf(line.c_str(), "WATSON_MOVING_RULE=%s", buffer);
            watson_moving_rule = buffer; // Assign to std::string
        }
        else if (line.find("WATSON_INIT_POS=") != string::npos)
        {
            int r, c;
            sscanf(line.c_str(), "WATSON_INIT_POS=(%d,%d)", &r, &c);
            watson_init_pos = Position(r, c);
        }
        else if (line.find("WATSON_INIT_HP=") != string::npos)
        {
            sscanf(line.c_str(), "WATSON_INIT_HP=%d", &watson_init_hp);
        }
        else if (line.find("WATSON_INIT_EXP=") != string::npos)
        {
            sscanf(line.c_str(), "WATSON_INIT_EXP=%d", &watson_init_exp);
        }
        else if (line.find("CRIMINAL_INIT_POS=") != string::npos)
        {
            int r, c;
            sscanf(line.c_str(), "CRIMINAL_INIT_POS=(%d,%d)", &r, &c);
            criminal_init_pos = Position(r, c);
        }
        else if (line.find("NUM_STEPS=") != string::npos)
        {
            sscanf(line.c_str(), "NUM_STEPS=%d", &num_steps);
        }
    }
    file.close();
}
Configuration::~Configuration()
{
    delete[] arr_walls;
}
/*
    Format of this string:
    Configuration[<attribute_name1>=<attribute_value1>;...] --- needed to be updated
     Configuration[
    MAP_NUM_ROWS=10
    MAP_NUM_COLS=10
    MAX_NUM_MOVING_OBJECTS=10
    NUM_WALLS=3
    ARRAY_WALLS=[(1,2);(2,3);(3,4)]
    NUM_FAKE_WALLS=1
    ARRAY_FAKE_WALLS=[(4,5)]
    SHERLOCK_MOVING_RULE=RUU
    SHERLOCK_INIT_POS=(1,3)
    SHERLOCK_INIT_HP=250
    SHERLOCK_INIT_EXP=500
    WATSON_MOVING_RULE=LU
    WATSON_INIT_POS=(2,1)
    WATSON_INIT_HP=300
    WATSON_INIT_EXP=350
    CRIMINAL_INIT_POS=(7,9)
    NUM_STEPS=100
    ]
*/
string Configuration::str() const
{
    stringstream ss;
    ss << "Configuration[MAP_NUM_ROWS=" << map_num_rows << " MAP_NUM_COLS=" << map_num_cols << " MAX_NUM_MOVING_OBJECTS=" << map_num_moving_objects
       << " NUM_WALLS=" << num_walls << " ARRAY_WALLS=[";
    for (int i = 0; i < num_walls; i++)
    {
        ss << arr_walls[i].str();
        if (i < num_walls - 1)
        {
            ss << ";";
        }
    }
    ss << "] NUM_FAKE_WALLS=" << num_fake_walls << " ARRAY_FAKE_WALLS=[";
    for (int i = 0; i < num_fake_walls; i++)
    {
        ss << arr_fake_walls[i].str();
        if (i < num_fake_walls - 1)
        {
            ss << ";";
        }
    }

    ss << "] SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << " SHERLOCK_INIT_POS=" << sherlock_init_pos.str() << " SHERLOCK_INIT_HP=" << sherlock_init_hp
       << " SHERLOCK_INIT_EXP=" << sherlock_init_exp << " WATSON_MOVING_RULE=" << watson_moving_rule << " WATSON_INIT_POS=" << watson_init_pos.str()
       << " WATSON_INIT_HP=" << watson_init_hp << " WATSON_INIT_EXP=" << watson_init_exp << " CRIMINAL_INIT_POS=" << criminal_init_pos.str()
       << " NUM_STEPS=" << num_steps << "]";
    return ss.str();
}

/*================ Implement of Robot class ========================*/
Robot::Robot(int index, const Position & init_pos, Map * map, Criminal * Criminal, RobotType robot_type)
        : MovingObject(index, init_pos, map, "Robot"), robot_type(robot_type), criminal(Criminal)
{}

/*================ Implement of RobotC class ========================*/
RobotC::RobotC(int index, const Position & init_pos, Map * map, Criminal * Criminal,  RobotType robot_type)
        : Robot(index, init_pos, map, Criminal, robot_type)
{}
/*
    Moves to the next location in the same location as the criminal
*/
Position RobotC::getNextPosition()
{
    if (map->isValid(criminal->getPreviousPosition(), this))
    {
        return criminal->getPreviousPosition();
    }
    return Position::npos;
}
void RobotC::move()
{
    Position next_pos = getNextPosition();
    if (next_pos != Position::npos)
    {
        pos = next_pos;
    }
}
int RobotC::getDistance(Sherlock * sherlock)
{
    return abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
}
int RobotC::getDistance(Watson * watson)
{
    return abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
}
/*  Robot[pos=<pos>;type=<robot_type>;dist=<dist>]
    <pos> prints the current position of the Robot
    robot_type prints a value that can be C, S, W or SW
    dist prints the distance to Sherlock, Watson or the sum of both depending on whether
    the robot is S, W or SW. If the robot type is RobotC, print an empty string.
*/
string RobotC::str() const
{
    stringstream ss;
    ss << "RobotC[pos=" << pos.str() << ";type=C;dist=]";
    return ss.str();
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////