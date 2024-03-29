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
    the FakeWall’s required EXP. 
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
        : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule) 
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
        : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule)
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
        : Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson)
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
    int maxDistance = INT_MIN;
    Position next_pos = Position::npos;

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
        // Check if the new position is valid
        Position temp = Position(xdir, ydir);
        if (!map->isValid(temp, this))
        {
            continue;   // Skip the invalid position
        }
        // Update maxDistance and next position
        if (totalDistance > maxDistance)
        {
            maxDistance = totalDistance;
            next_pos = temp;
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
{   // for now left empty
    // for (int i = 0; i < count; i++)
    // {
    //     delete arr_mv_objs[i];
    // }
    // delete[] arr_mv_objs;
    if (this->arr_mv_objs != nullptr) // Only delete the array if it has not been deleted
    {
        delete[] this->arr_mv_objs;
        this->arr_mv_objs = nullptr; // Set the array pointer to null after deleting
    }
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
            string positions = line.substr(line.find('=') + 1); // Get the part of the string after the equals sign
            istringstream ss(positions);
            string token;
            while (getline(ss, token, ';'))
            {
                size_t start = token.find('(') + 1;
                size_t end = token.find(',');
                string r_str = token.substr(start, end - start); // Extract the string for r

                start = end + 1;
                end = token.find(')');
                string c_str = token.substr(start, end - start); // Extract the string for c

                int r = stoi(r_str); // Convert r_str to an int
                int c = stoi(c_str); // Convert c_str to an int

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
            string positions = line.substr(line.find('=') + 1); // Get the part of the string after the equals sign
            istringstream ss(positions);
            string token;
            while (getline(ss, token, ';'))
            {
                size_t start = token.find('(') + 1;
                size_t end = token.find(',');
                string r_str = token.substr(start, end - start); // Extract the string for r

                start = end + 1;
                end = token.find(')');
                string c_str = token.substr(start, end - start); // Extract the string for c

                int r = stoi(r_str); // Convert r_str to an int
                int c = stoi(c_str); // Convert c_str to an int

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
    delete[] arr_fake_walls;
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
{
	/*
	These items are contained within the robots. The conditions created are as follows:
 	Call the location where the robot is created with coordinates (i,j) where i is the row index,
 	j is the column index.
	With p = i∗j. Call s the cardinal number of p . We define the cardinal number of a number
 	as the sum value of the digits, until the sum value is a 1-digit number.
	*/
    int p = init_pos.getRow() * init_pos.getCol();
    int s = cardinalNum(p);
    if (s >= 0 && s <= 1)
    {
        // create MagicBook
        item = new MagicBook();
    }
    else if  (s >= 2 && s <= 3)
    {
        // create EnergyDrink
        item = new EnergyDrink();
    }
    else if (s >= 4 && s <= 5)
    {
        // create FirstAid
        item = new FirstAid();
    }
    else if (s >= 6 && s <= 7)
    {
        // create ExcemptionCard
        item = new ExcemptionCard();
    }
    else if (s >= 8 && s <= 9)
    {
        // create PassingCard
        int t = (init_pos.getRow() * 11 + init_pos.getCol()) % 4;
        string challenge = "";
        if (t == 0)
        {
            challenge = "RobotS";
        }
        else if (t == 1)
        {
            challenge = "RobotC";
        }
        else if (t == 2)
        {
            challenge = "RobotSW";
        }
        else if (t == 3)
        {
            challenge = "all";
        }
        item = new PassingCard(challenge);
    }
}

int Robot::cardinalNum(int num)
{
    while (num > 9) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        num = sum;
    }
    return num;
}

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
int RobotC::getDistance(Sherlock * sherlock) const
{
    return abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
}
int RobotC::getDistance(Watson * watson) const 
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
/*================ Implement of RobotS class ========================*/
RobotS::RobotS(int index, const Position & init_pos, Map * map, Criminal * Criminal, Sherlock * sherlock, RobotType robot_type)
        : Robot(index, init_pos, map, Criminal, robot_type), sherlock(sherlock)
{}

/*
    Move to the next location 1 unit away from the original and closest to Sherlock’s next location.
    the distance referred to is the Manhattan distance
    If there are multiple nearest locations, the order of selection clockwise rotation
    starting from the upwards direction, and selecting the first location
*/
Position RobotS::getNextPosition()
{
    /*
        Move to the next location 1 unit away from the original and closest to
        Sherlock’s next location (Mathantann dstance)
    */
    // U R D : 
    Position directions[] = {Position(-1, 0), Position(0, 1), Position(1, 0), Position(0, -1)};
    int nearestDistance = INT_MAX;
    Position next_pos = Position::npos;
    // Loop through all 4 directions
    for (int i = 0; i < 4; i++)
    {
        // Calculate new RobotS position
        int xdir = pos.getRow() + directions[i].getRow();
        int ydir = pos.getCol() + directions[i].getCol();
        // Calculate distance between RobotS - sherlock
        int distance = abs(xdir - sherlock->getCurrentPosition().getRow()) + abs(ydir - sherlock->getCurrentPosition().getCol());
        Position temp = Position(xdir, ydir);
        // Check if the new position is valid
        if (!map->isValid(temp, this))
        {
            continue;   // Skip the invalid position
        }
        // Update nearestDistance and next position
        if (distance < nearestDistance)
        {
            nearestDistance = distance;
            next_pos = temp;
        }
    }
    
    return next_pos;
}
void RobotS::move()
{
    Position next_pos = getNextPosition();
    if (next_pos != Position::npos)
    {
        pos = next_pos;
    }
}
int RobotS::getDistance(Sherlock * sherlock) const
{
    return abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
}
string RobotS::str() const
{
    stringstream ss;
    ss << "RobotS[pos=" << pos.str() << ";type=S;dist=" << getDistance(sherlock) << "]";
    return ss.str();
}
/*================ Implement of RobotW class ========================*/
RobotW::RobotW(int index, const Position & init_pos, Map * map, Criminal * Criminal, Watson * watson, RobotType robot_type)
        : Robot(index, init_pos, map, Criminal, robot_type), watson(watson)
{}
/*
    Move to the next location 1 unit away from the original and closest to Watson’s next location.
    the distance referred to is the Manhattan distance
    If there are multiple nearest locations, the order of selection clockwise rotation
    starting from the upwards direction, and selecting the first location
*/
Position RobotW::getNextPosition()
{
    // U R D L 
    Position directions[] = {Position(-1, 0), Position(0, 1), Position(1, 0), Position(0, -1)};
    int nearestDistance = INT_MAX;
    Position next_pos = Position::npos;
    // Loop through all 4 directions
    for (int i = 0; i < 4; i++)
    {
        // Calculate new RobotW position
        int xdir = pos.getRow() + directions[i].getRow();
        int ydir = pos.getCol() + directions[i].getCol();
        // Calculate distance between RobotW - watson
        int distance = abs(xdir - watson->getCurrentPosition().getRow()) + abs(ydir - watson->getCurrentPosition().getCol());
        Position temp = Position(xdir, ydir);
        // Check if the new position is valid
        if (!map->isValid(temp, this))
        {
            continue;   // Skip the invalid position
        }
        // Update nearestDistance and next position
        if (distance < nearestDistance)
        {
            nearestDistance = distance;
            next_pos = temp;
        }
    }
    
    return next_pos;
}
void RobotW::move()
{
    Position next_pos = getNextPosition();
    if (next_pos != Position::npos)
    {
        pos = next_pos;
    }
}
int RobotW::getDistance(Watson * watson) const
{
    return abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
}
string RobotW::str() const
{
    stringstream ss;
    ss << "RobotW[pos=" << pos.str() << ";type=W;dist=" << getDistance(watson) << "]";
    return ss.str();
}
/*================ Implement of RobotSW class ========================*/
RobotSW::RobotSW(int index, const Position & init_pos, Map * map, Criminal * Criminal, Sherlock * sherlock, Watson * watson, RobotType robot_type)
        : Robot(index, init_pos, map, Criminal, robot_type), sherlock(sherlock), watson(watson)
{}
/*
    Move to the next location that is 2 units away from the original and has
    the closest total distance to both Sherlock and Watson. If there are multiple suitable
    positions, the order of selection is as if in RobotS.
*/
Position RobotSW::getNextPosition()
{
    /*
     Move to the next location that is 2 units away from the original and has
    the closest total distance to both Sherlock and Watson. (manhattan distance)
    */
    // U2 RU1 R2 RD1 D2 LD1 L2 LU1
    Position directions[] = {Position(-2, 0), Position(-1, 1), Position(0, 2), Position(1, 1),
                             Position(2, 0), Position(1, -1), Position(0, -2), Position(-1, -1)};
    int nearestDistance = INT_MAX;
    Position next_pos = Position::npos;
    // Loop through all 8 directions
    for (int i = 0; i < 8; i++)
    {
        // Calculate new RobotSW position
        int xdir = pos.getRow() + directions[i].getRow();
        int ydir = pos.getCol() + directions[i].getCol();
        // Calculate distance between RobotSW - sherlock and RobotSW - watson
        int distance_sherlock = abs(xdir - sherlock->getCurrentPosition().getRow()) + abs(ydir - sherlock->getCurrentPosition().getCol());
        int distance_watson   = abs(xdir - watson->getCurrentPosition().getRow()) + abs(ydir - watson->getCurrentPosition().getCol());
        int totalDistance = distance_sherlock + distance_watson;
        Position temp = Position(xdir, ydir);
        // Check if the new position is valid
        if (!map->isValid(temp, this))
        {
            continue;   // Skip the invalid position
        }
        // Update nearestDistance and next position
        if (totalDistance < nearestDistance)
        {
            nearestDistance = totalDistance;
            next_pos = temp;
        }
    }
    
    return next_pos;
}
void RobotSW::move()
{
    Position next_pos = getNextPosition();
    if (next_pos != Position::npos)
    {
        pos = next_pos;
    }
}
int RobotSW::getDistance(Sherlock * sherlock, Watson * watson) const
{
    int distance_sherlock = abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) + abs(pos.getCol() - sherlock->getCurrentPosition().getCol());
    int distance_watson   = abs(pos.getRow() - watson->getCurrentPosition().getRow()) + abs(pos.getCol() - watson->getCurrentPosition().getCol());
    return distance_sherlock + distance_watson;
}
string RobotSW::str() const
{
    stringstream ss;
    ss << "RobotSW[pos=" << pos.str() << ";type=SW;dist=" << getDistance(sherlock, watson) << "]";
    return ss.str();
}

/*================ Implement of MagicBook class ========================*/
bool MagicBook::canUse(Character * obj, Robot * robot)
{
    return obj->getExp() <= 350;
}
void MagicBook::use(Character * obj, Robot * robot)
{
    if (canUse(obj, robot))
    {
        obj->setExp(ceil(obj->getExp() * 1.25));
    }
}
/*================ Implement of EnergyDrink class ========================*/
bool EnergyDrink::canUse(Character * obj, Robot * robot)
{
    return obj->getHp() <= 100;
}
void EnergyDrink::use(Character * obj, Robot * robot)
{
    if (canUse(obj, robot))
    {
        obj->setHp(ceil(obj->getHp() * 1.20));
    }
}
/*================ Implement of FirstAid class ========================*/
bool FirstAid::canUse(Character * obj, Robot * robot)
{
    return (obj->getHp() <= 100) || (obj->getExp() <= 350);
}
void FirstAid::use(Character * obj, Robot * robot)
{
    if (canUse(obj, robot))
    {
        obj->setHp(ceil(obj->getHp() * 1.50));
    }
}
/*================ Implement of ExcemptionCard class ========================*/
bool ExcemptionCard::canUse(Character * obj, Robot * robot)
{
    return ((obj->getName() == "Sherlock") && (obj->getHp() % 2 != 0));
}
void ExcemptionCard::use(Character * obj, Robot * robot)
{
    /*
    Immunity Card helps the character to be immune to hp, exp when not overcoming challenges at a destination.
    will implement later
    */
   return;
}
/*================ Implement of PassingCard class ========================*/
bool PassingCard::canUse(Character * obj, Robot * robot)
{
    return ((obj->getName() == "Watson") && (obj->getHp() % 2 == 0));
}
void PassingCard::use(Character * obj, Robot * robot)
{
    /* 
    When using the PassingCard to perform a challenge, the character does not need to perform the challenge at a destination location
    The tag has an attribute challenge (type string) which is the name of a challenge (for example type RobotS is a
    tag to pass the challenge posed by RobotS without doing it
    If the tag’s type is all the tag can be used for any type regardless of the challenge encountered.
    Otherwise, it is necessary to check whether the card type  matches the type of challenging action the character encounters
    if the card type does not match:
        *the character’s exp will be reduced by 50 EXP even though the effect still be performed 
    */
   if (challenge == "all" || challenge == robot->getName())
   {
		return;
   }
   else
   {
		obj->setExp(obj->getExp() - 50);
		return;
   }
}
/*================ Implement of sherlockBag class ========================*/
SherlockBag::SherlockBag(Sherlock * sherlock) : BaseBag(sherlock)
{
    head = nullptr;
    maxSize = 13;
    currentSize = 0;
}
SherlockBag::~SherlockBag()
{
    BaseItem * temp = head;
    while (temp != nullptr)
    {
        BaseItem * next = temp->next;
        delete temp;
        temp = next;
    }
}
/*
    Add the item to the beginning of the list
*/
bool SherlockBag::insert(BaseItem * item)
{
    if (head == nullptr)
    {
        head = item;
        currentSize++;
        return true;
    }
    else if (currentSize < maxSize)
    {
        item->next = head;
        head = item;
        currentSize++;
        return true;
    }
    return false;
}
/*
    Find the item in the bag that can be used and is closest
    to the top of the bag. This item will be swapped
    with the first item in the list and then
    removed from the list.
*/
BaseItem * SherlockBag::get()
{
    BaseItem * temp = head;
    BaseItem * prev = nullptr;
    while (temp != nullptr)
    {
        if (temp->canUse(obj, nullptr))
        {
            // if the item is not the first item in the list
            if (prev != nullptr)
            {
                // swap temp with head
                prev->next = head;
                head->next = temp->next;
                temp->next = prev;
                head = temp;
            }
            // Remove the head of the list
            head = head->next;
            currentSize--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }

    return nullptr;
}
/*
    If in the inventory there is an item of the
    type to be used, the character can use this item by reversing its position with first item
    (if it is not the first item) and remove it from the list. If there are multiple items, the
    item closest to the top of the bag will be done as above.
*/
BaseItem * SherlockBag::get(ItemType itemType)
{
    BaseItem * temp = head;
    BaseItem * prev = nullptr;
    while (temp != nullptr)
    {
        if ((temp->itemType == itemType) && (temp->canUse(obj, nullptr)))
        {
            // if the item is not the first item in the list
            if (prev != nullptr)
            {
                // swap temp with head
                prev->next = head;
                head->next = temp->next;
                temp->next = prev;
                head = temp;
            }
            // Remove the head of the list
            head = head->next;
            currentSize--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }

    return nullptr;
}
/*
    Bag[count=<c>;<list_items>]
    <c>: is the current number of items that the inventory has.
    <list_items>: is a string representing the items from beginning to end of a linked list
    each item is represented by the item’s type name, the items are separated by a comma
    The type names of the items are the same as the class names described above
*/
string SherlockBag::str() const 
{
    stringstream ss;
    ss << "Bag[count=" << currentSize << ";";
    BaseItem * temp = head;
    while (temp != nullptr)
    {
        if (temp->itemType == MAGIC_BOOK)
        {
            ss << "MagicBook";
        }
        else if (temp->itemType == ENERGY_DRINK)
        {
            ss << "EnergyDrink";
        }
        else if (temp->itemType == FIRST_AID)
        {
            ss << "FirstAid";
        }
        else if (temp->itemType == EXCEMPTION_CARD)
        {
            ss << "ExcemptionCard";
        }
        else if (temp->itemType == PASSING_CARD)
        {
            ss << "PassingCard";
        }

        if (temp->next != nullptr)
        {
            ss << ",";
        }
        temp = temp->next;
    }
    ss << "]";
    return ss.str();
}

BaseItem * SherlockBag::peak(ItemType itemType)
{
    BaseItem * temp = head;
    while (temp != nullptr)
    {
        if (temp->itemType == itemType)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
/*================ Implement of watsonBag class ========================*/
WatsonBag::WatsonBag(Watson * watson) : BaseBag(watson)
{
    head = nullptr;
    maxSize = 15;
    currentSize = 0;
}
WatsonBag::~WatsonBag()
{
    BaseItem * temp = head;
    while (temp != nullptr)
    {
        BaseItem * next = temp->next;
        delete temp;
        temp = next;
    }
}
/*
    Add the item to the beginning of the list
*/
bool WatsonBag::insert(BaseItem * item)
{
    if (head == nullptr)
    {
        head = item;
        currentSize++;
        return true;
    }
    else if (currentSize < maxSize)
    {
        item->next = head;
        head = item;
        currentSize++;
        return true;
    }
    return false;
}
/*
    Find the item in the bag that can be used and is closest
    to the top of the bag. This item will be swapped
    with the first item in the list and then
    removed from the list.
*/
BaseItem * WatsonBag::get()
{
    BaseItem * temp = head;
    BaseItem * prev = nullptr;
    while (temp != nullptr)
    {
        if (temp->canUse(obj, nullptr))
        {
            // if the item is not the first item in the list
            if (prev != nullptr)
            {
                // swap temp with head
                prev->next = head;
                head->next = temp->next;
                temp->next = prev;
                head = temp;
            }
            // Remove the head of the list
            head = head->next;
            currentSize--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }

    return nullptr;
}
/*
    If in the inventory there is an item of the
    type to be used, the character can use this item by reversing its position with first item
    (if it is not the first item) and remove it from the list. If there are multiple items, the
    item closest to the top of the bag will be done as above.
*/
BaseItem * WatsonBag::get(ItemType itemType)
{
    BaseItem * temp = head;
    BaseItem * prev = nullptr;
    while (temp != nullptr)
    {
        if ((temp->itemType == itemType) && (temp->canUse(obj, nullptr)))
        {
            // if the item is not the first item in the list
            if (prev != nullptr)
            {
                // swap temp with head
                prev->next = head;
                head->next = temp->next;
                temp->next = prev;
                head = temp;
            }
            // Remove the head of the list
            head = head->next;
            currentSize--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }

    return nullptr;
}
/*
    Bag[count=<c>;<list_items>]
    <c>: is the current number of items that the inventory has.
    <list_items>: is a string representing the items from beginning to end of a linked list
    each item is represented by the item’s type name, the items are separated by a comma
    The type names of the items are the same as the class names described above
*/
string WatsonBag::str() const 
{
    stringstream ss;
    ss << "Bag[count=" << currentSize << ";";
    BaseItem * temp = head;
    while (temp != nullptr)
    {
        if (temp->itemType == MAGIC_BOOK)
        {
            ss << "MagicBook";
        }
        else if (temp->itemType == ENERGY_DRINK)
        {
            ss << "EnergyDrink";
        }
        else if (temp->itemType == FIRST_AID)
        {
            ss << "FirstAid";
        }
        else if (temp->itemType == EXCEMPTION_CARD)
        {
            ss << "ExcemptionCard";
        }
        else if (temp->itemType == PASSING_CARD)
        {
            ss << "PassingCard";
        }

        if (temp->next != nullptr)
        {
            ss << ",";
        }
        temp = temp->next;
    }
    ss << "]";
    return ss.str();
}
BaseItem * WatsonBag::peak(ItemType itemType)
{
    BaseItem * temp = head;
    while (temp != nullptr)
    {
        if (temp->itemType == itemType)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
/*================ Implement of StudyPinkProgram class ========================*/
/*
    Constructor receives 1 parameter which is the path to the configuration file for
    the program. The constructor needs to initialize the necessary information for the
    class. As for arr_mv_objs, after initialization, criminal, sherlock, watson are added
    sequentially using the add method
*/
StudyPinkProgram::StudyPinkProgram(const string & config_file_path)
{
    config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    arr_mv_objs = new ArrayMovingObject(config->map_num_moving_objects);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
}
/*
    Destructor needs to delete the map, arr_mv_objs, criminal, sherlock, watson
*/
StudyPinkProgram::~StudyPinkProgram()
{
    delete map;
    delete arr_mv_objs;
    delete criminal;
    delete sherlock;
    delete watson;
}
/*
    The isStop method returns true if the program stops, otherwise returns false.
    The program stops when one of the following conditions occurs: Sherlock’s hp is 0;
    Watson’s hp is 0; Sherlock catches the criminal; Watson caught the criminal.
*/
bool StudyPinkProgram::isStop() const
{
    return (sherlock->getHp() == 0) || (watson->getHp() == 0) 
            || (sherlock->getCurrentPosition() == criminal->getCurrentPosition())
            || (watson->getCurrentPosition() == criminal->getCurrentPosition());
}
void StudyPinkProgram::run(bool verbose)
{
    // Note: This is a sample code. You can change the implementation as you like.
    // TODO
    int criminalMoves = 0;
    for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                if (verbose) 
                {
                    sherlockEvents(i);
                    watsonEvents(i);
                    arr_mv_objs->get(i)->move();
                    // update here
                    criminalEvents(i, criminalMoves);
                    sherlockEvents(i);
                    watsonEvents(i);
                    printStep(istep);

                    if (isStop()) {
                        printStep(istep);
                        break;
                    }
                }
                else
                {
                    arr_mv_objs->get(i)->move();
                }

            if (i == arr_mv_objs->size() - 1)
            {
                for (int j = 0; j < arr_mv_objs->size(); j++)
                {
                    if (isStop()) {
                        printStep(istep);
                        break;
                    }
                    criminalEvents(j, criminalMoves);
                    sherlockEvents(j);
                    watsonEvents(j);       
                }

            }
        }
    }
    printResult();
}

void StudyPinkProgram::sherlockEvents(int index)
{
        // If Sherlock meets:
        /*
            RobotS: Sherlock needs to solve a problem to win against RobotS. If Sherlock’s EXP
            is now greater than 400, Sherlock will solve the problem and receive the item this
            robot holds. Otherwise, Sherlock’s EXP will be lost by 10%.
            RobotW: Sherlock will pass and receive the item without having to fight.
            RobotSW: Sherlock can only win against RobotSW when EXP of Sherlock is
            greater than 300 and HP of Sherlock greater than 335. If he wins, Sherlock
            receives the item this robot holds. Otherwise, Sherlock will lose 15% HP and 15%
            EXP.
            RobotC: Sherlock meeting RobotC means meeting the location next to the criminal.
            At this time, if Sherlock’s EXP is greater than 500, Sherlock will defeat the robot
            and capture the criminal (no items this robot holds). On the contrary, Sherlock will
            let criminals escape. However, you will still be able to destroy the robot and receive
            the items this robot holds
        */
        if (arr_mv_objs->get(index)->getName() == "RobotS" && sherlock->getCurrentPosition() == arr_mv_objs->get(index)->getCurrentPosition())
        {
            Robot* robot = dynamic_cast<Robot*>(arr_mv_objs->get(index));
            if (sherlock->getExp() > 400)
            {
                if (robot) 
                {
                    sherlock_bag->insert(robot->item);
                }
            }
            else
            {
                if (sherlock_bag->get(EXCEMPTION_CARD)->canUse(sherlock, robot) == false)
                {
                    sherlock->setExp(ceil(sherlock->getExp() * 0.90));
                }
            }

            if (sherlock_bag->peak(MAGIC_BOOK)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(MAGIC_BOOK)->use(sherlock, nullptr);
            }
            if (sherlock_bag->peak(ENERGY_DRINK)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(ENERGY_DRINK)->use(sherlock, nullptr);
            }
            if (sherlock_bag->peak(FIRST_AID)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(FIRST_AID)->use(sherlock, nullptr);
            }
        }
        else if (arr_mv_objs->get(index)->getName() == "RobotW" && sherlock->getCurrentPosition() == arr_mv_objs->get(index)->getCurrentPosition())
        {
            Robot* robot = dynamic_cast<Robot*>(arr_mv_objs->get(index));
            if (robot) 
            {
                sherlock_bag->insert(robot->item);
            }
            if (sherlock_bag->peak(MAGIC_BOOK)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(MAGIC_BOOK)->use(sherlock, nullptr);
            }
            if (sherlock_bag->peak(ENERGY_DRINK)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(ENERGY_DRINK)->use(sherlock, nullptr);
            }
            if (sherlock_bag->peak(FIRST_AID)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(FIRST_AID)->use(sherlock, nullptr);
            }
        }
        else if (arr_mv_objs->get(index)->getName() == "RobotSW" && sherlock->getCurrentPosition() == arr_mv_objs->get(index)->getCurrentPosition())
        {
            Robot* robot = dynamic_cast<Robot*>(arr_mv_objs->get(index));
            if (sherlock->getExp() > 300 && sherlock->getHp() > 335)
            {
                if (robot) 
                {
                    sherlock_bag->insert(robot->item);
                }
            }
            else
            {
                if (sherlock_bag->peak(EXCEMPTION_CARD)->canUse(sherlock, robot) == false)
                {
                    sherlock->setExp(ceil(sherlock->getExp() * 0.85));
                    sherlock->setHp(ceil(sherlock->getHp() * 0.85));
                }
                else 
                {
                    sherlock_bag->get(EXCEMPTION_CARD)->use(sherlock, robot);
                }
            }
            if (sherlock_bag->peak(MAGIC_BOOK)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(MAGIC_BOOK)->use(sherlock, nullptr);
            }
            if (sherlock_bag->peak(ENERGY_DRINK)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(ENERGY_DRINK)->use(sherlock, nullptr);
            }
            if (sherlock_bag->peak(FIRST_AID)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(FIRST_AID)->use(sherlock, nullptr);
            }
        }
        else if (arr_mv_objs->get(index)->getName() == "RobotC" && sherlock->getCurrentPosition() == arr_mv_objs->get(index)->getCurrentPosition())
        {
            if (sherlock->getExp() > 500)
            {
                /*
                    Sherlock will defeat the robot
                    and capture the criminal (no items this robot holds
                */
                sherlock->setPos(criminal->getCurrentPosition());
            }
            else
            {
                Robot* robot = dynamic_cast<Robot*>(arr_mv_objs->get(index));
                if (robot) 
                {
                    sherlock_bag->insert(robot->item);
                }
            }
            if (sherlock_bag->peak(MAGIC_BOOK)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(MAGIC_BOOK)->use(sherlock, nullptr);
            }
            if (sherlock_bag->peak(ENERGY_DRINK)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(ENERGY_DRINK)->use(sherlock, nullptr);
            }
            if (sherlock_bag->peak(FIRST_AID)->canUse(sherlock, nullptr) == true)
            {
                sherlock_bag->get(FIRST_AID)->use(sherlock, nullptr);
            }
        }
        else if (arr_mv_objs->get(index)->getName() == "Watson" && sherlock->getCurrentPosition() == arr_mv_objs->get(index)->getCurrentPosition())
        {
            while(sherlock_bag->get(PASSING_CARD) != nullptr)
            {
                watson_bag->insert(sherlock_bag->get(PASSING_CARD));
            }
            while(watson_bag->get(EXCEMPTION_CARD) != nullptr)
            {
                sherlock_bag->insert(watson_bag->get(EXCEMPTION_CARD));
            }
        }
}

void StudyPinkProgram::watsonEvents(int index)
{
    /*
    RobotS: Watson will not perform any actions with the robot and will not receive
    items held by this robot.
    RobotW:Watsonneedstoconfront this Robot and only win when it has HP greater
    than 350. If Watson wins, Watson will receive the item held by the robot. If he
    loses, Watson’s HP will be reduced by 5%.
    RobotSW: Watson can only win against RobotSW when Watson’s EXP is greater
    than 600 and Watson’s HP is greater than 165. If he wins, Watson receives the
    item that this robot holds. Otherwise, Watson will lose 15% HP and 15% EXP.
    Watson meets RobotC, which means he has met the location adjacent to the
    criminal. Watson could not catch the criminal because he was held back by RobotC.
    However, Watson will still destroy the robot and receive the item this robot holds.
    */
    if (arr_mv_objs->get(index)->getName() == "RobotS" && arr_mv_objs->get(index)->getCurrentPosition() == watson->getCurrentPosition())
    {
        if (watson_bag->peak(MAGIC_BOOK)->canUse(watson, nullptr) == true)
        {
            watson_bag->get(MAGIC_BOOK)->use(watson, nullptr);
        }
        if (watson_bag->peak(ENERGY_DRINK)->canUse(watson, nullptr) == true)
        {
            watson_bag->get(ENERGY_DRINK)->use(watson, nullptr);
        }
        if (watson_bag->peak(FIRST_AID)->canUse(watson, nullptr) == true)
        {
            watson_bag->get(FIRST_AID)->use(watson, nullptr);
        }
    }
    else if (arr_mv_objs->get(index)->getName() == "RobotW" && arr_mv_objs->get(index)->getCurrentPosition() == watson->getCurrentPosition())
    {
        Robot * robot = dynamic_cast<Robot*>(arr_mv_objs->get(index));
        if (watson->getHp() > 350)
        {
            if (robot) 
            {
                watson_bag->insert(robot->item);
            }
        }
        else
        {
            if (watson_bag->peak(PASSING_CARD)->canUse(watson, robot) == false)
            {
                watson->setHp(ceil(watson->getHp() * 0.95));
            }
            else 
            {
                watson_bag->get(PASSING_CARD)->use(watson, robot);
            }
            if (watson_bag->peak(MAGIC_BOOK)->canUse(watson, nullptr) == true)
            {
                watson_bag->get(MAGIC_BOOK)->use(watson, nullptr);
            }
            if (watson_bag->peak(ENERGY_DRINK)->canUse(watson, nullptr) == true)
            {
                watson_bag->get(ENERGY_DRINK)->use(watson, nullptr);
            }
            if (watson_bag->peak(FIRST_AID)->canUse(watson, nullptr) == true)
            {
                watson_bag->get(FIRST_AID)->use(watson, nullptr);
            }  
        }
    }
    else if (arr_mv_objs->get(index)->getName() == "RobotSW" && arr_mv_objs->get(index)->getCurrentPosition() == watson->getCurrentPosition())
    {
        Robot * robot = dynamic_cast<Robot*>(arr_mv_objs->get(index));
        if (watson->getExp() > 600 && watson->getHp() > 165)
        {
            if (robot) 
            {
                watson_bag->insert(robot->item);
            }
        }
        else
        {
            if (watson_bag->peak(PASSING_CARD)->canUse(watson, robot) == false)
            {
                watson->setExp(ceil(watson->getExp() * 0.85));
                watson->setHp(ceil(watson->getHp() * 0.85));
            }
            else 
            {
                watson_bag->get(PASSING_CARD)->use(watson, robot);
            }
            if (watson_bag->peak(MAGIC_BOOK)->canUse(watson, nullptr) == true)
            {
                watson_bag->get(MAGIC_BOOK)->use(watson, nullptr);
            }
            if (watson_bag->peak(ENERGY_DRINK)->canUse(watson, nullptr) == true)
            {
                watson_bag->get(ENERGY_DRINK)->use(watson, nullptr);
            }
            if (watson_bag->peak(FIRST_AID)->canUse(watson, nullptr) == true)
            {
                watson_bag->get(FIRST_AID)->use(watson, nullptr);
            }
        }
    }  
    else if (arr_mv_objs->get(index)->getName() == "RobotC" && arr_mv_objs->get(index)->getCurrentPosition() == watson->getCurrentPosition())
    {
        Robot * robot = dynamic_cast<Robot*>(arr_mv_objs->get(index));
        if (robot) 
        {
            watson_bag->insert(robot->item);
        }
        if (watson_bag->peak(MAGIC_BOOK)->canUse(watson, nullptr) == true)
        {
            watson_bag->get(MAGIC_BOOK)->use(watson, nullptr);
        }
        if (watson_bag->peak(ENERGY_DRINK)->canUse(watson, nullptr) == true)
        {
            watson_bag->get(ENERGY_DRINK)->use(watson, nullptr);
        }
        if (watson_bag->peak(FIRST_AID)->canUse(watson, nullptr) == true)
        {
            watson_bag->get(FIRST_AID)->use(watson, nullptr);
        }
    }   
}


void StudyPinkProgram::criminalEvents(int index, int & criminalMoves)
{
               /*
        During the criminal’s movement, for every 3 steps that the criminal moves, a robot will be
        created. Note that when the getNextPosition method of Criminal does not return a valid
        move position, the move method does not perform the move, which is not counted as a move.
        */
        if (arr_mv_objs->get(index)->getName() == "Criminal" && criminal->getNextPosition() != Position::npos)
        {
            criminalMoves++;
            if (criminalMoves == 3)
            {
                /*
                After every 3 steps of the criminal, a robot will be created at that location
                If it is the first robot created on the map, it will be the robot type RobotC.
                Closer distance to Sherlock’s location: Create a robot RobotS
                Closer distance to Watson’s location: Creating a robot RobotW
                The distance to Sherlock and Watson’s location is equal: Create a robot RobotSW
                */
                if (arr_mv_objs->size() == 3)
                {
                    newRobot = new RobotC(4, criminal->getPreviousPosition(), map, criminal, C);
                }
                else
                {
                    int distance_sherlock = abs(criminal->getPreviousPosition().getRow() - sherlock->getCurrentPosition().getRow()) 
                                            + abs(criminal->getPreviousPosition().getCol() - sherlock->getCurrentPosition().getCol());
                    int distance_watson = abs(criminal->getPreviousPosition().getRow() - watson->getCurrentPosition().getRow()) 
                                            + abs(criminal->getPreviousPosition().getCol() - watson->getCurrentPosition().getCol());
                    if (distance_sherlock < distance_watson)
                    {
                        newRobot = new RobotS(arr_mv_objs->size(), criminal->getPreviousPosition(), map, criminal, sherlock, S);
                    }
                    else if (distance_sherlock > distance_watson)
                    {
                        newRobot = new RobotW(arr_mv_objs->size(), criminal->getPreviousPosition(), map, criminal, watson, W);
                    }
                    else
                    {
                        newRobot = new RobotSW(arr_mv_objs->size(), criminal->getPreviousPosition(), map, criminal, sherlock, watson, SW);
                    }
                }
                // added robot to the array of moving objects suppose the array is no full
                if (!arr_mv_objs->isFull())
                {
                    arr_mv_objs->add(newRobot);
                }
                criminalMoves = 0;
            }
        }
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////

