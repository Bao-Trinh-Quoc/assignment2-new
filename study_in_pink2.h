/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 2
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
    friend class TestStudyInPink;
protected:
    ElementType type;
public:
    MapElement(ElementType in_type) : type(in_type) {};
    virtual ~MapElement() {};   
    virtual ElementType getType() const {   return type;   };
};

class Path : public MapElement {
    friend class TestStudyInPink;
public:
    Path() : MapElement(PATH) {};
    ~Path() {};
};

class Wall : public MapElement {
    friend class TestStudyInPink;
public:
    Wall() : MapElement(WALL) {};
    ~Wall() {};
};

class FakeWall : public MapElement {
    friend class TestStudyInPink;
private:
    int reg_exp;
public:
    FakeWall() : MapElement(FAKE_WALL), reg_exp(0) {};
    FakeWall(int in_reg_exp) : MapElement(FAKE_WALL), reg_exp(in_reg_exp) {};
    ~FakeWall() {};
    // additional methods
    int getReqExp() const {    return reg_exp;   }
};

class Map {
    friend class TestStudyInPink;
private:
    int num_rows, num_cols;
    MapElement *** map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls);
    ~Map();
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
};

class Position {
    friend class TestStudyInPink;
private:
    int r, c;
public:
    static const Position npos;

    Position(int r=0, int c=0) : r(r), c(c) {};

    Position(const string & str_pos);

    int getRow() const {    return r;       }
    int getCol() const {    return c;       }
    void setRow(int r) {    this->r = r;    }
    void setCol(int c) {    this->c = c;    }
    string str() const;
    bool isEqual(int in_r, int in_c) const;
    bool isEqual(const Position & pos) const;
    // additional methods
    bool operator==(const Position & pos) const { return r == pos.c && c == pos.c;}
    bool operator!=(const Position & pos) const { return !(*this == pos);   }  
};

class MovingObject {
    friend class TestStudyInPink;
protected:
    int index;
    Position pos;
    Map * map;
    string name;

public:
    MovingObject(int index, const Position pos, Map * map, const string & name="")
                : index(index), pos(pos), map(map), name(name) {};
    virtual ~MovingObject() {};
    virtual Position getNextPosition() = 0;
    virtual Position getCurrentPosition() const = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    // additional methods
    string getName() const {    return name;   }
    virtual int getExp() const {    return -1;  }
};

class Character : public MovingObject
{
    friend class TestStudyInPink;
protected:
    int hp;
    int exp;
public:
    Character(int index, const Position & pos, Map * map, const string & name)
        : MovingObject(index, pos, map, name) {};
    // additional methods
    void setExp(int exp) {    this->exp = exp;  }
    void setHp(int hp)  {    this->hp = hp;    }
    int getHp() const {    return hp;   }
};

class Sherlock : public Character {
    friend class TestStudyInPink;
private:
    // TODO
    string moving_rule;

public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    string str() const;
    int getExp() const {    return exp;   }
    // additional methods
    void setPos(const Position & pos) {    this->pos = pos;  }
};

class Watson : public Character {
    friend class TestStudyInPink;
private:
    // TODO
    string moving_rule;

public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    string str() const;
    int getExp() const {    return exp;   }
};

class Criminal : public Character {
    friend class TestStudyInPink;
private:
    // TODO
    Sherlock * sherlock;
    Watson  * watson;
    Position prev_pos = Position::npos;
public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    string str() const;
    // additional methods
    Position getPreviousPosition() const;
};

class ArrayMovingObject {
    friend class TestStudyInPink;
private:
    MovingObject ** arr_mv_objs;
    int count;
    int capacity;
public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const {   return count == capacity;   }
    bool add(MovingObject * mv_obj);
    string str() const;
    MovingObject * get(int index) const {   return arr_mv_objs[index];}
    // return current number of elements in the array
    int size() const {   return count;   }
};

class Configuration {
    friend class StudyPinkProgram;
    friend class TestStudyInPink;
private: 
    // TODO
    int map_num_rows = 0, map_num_cols = 0;
    int max_num_moving_objects = 0;
    int num_walls = 0;  // Number of Wall objects
    Position * arr_walls; 
    int num_fake_walls = 0;  // Number of FakeWall objects
    Position * arr_fake_walls;
    string sherlock_moving_rule = "";
    Position sherlock_init_pos;
    int sherlock_init_hp = 0;
    int sherlock_init_exp = 0;
    string watson_moving_rule = "";
    int watson_init_hp = 0;
    int watson_init_exp = 0;
    Position watson_init_pos;
    Position criminal_init_pos;
    int num_steps = 0;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
};

// Robot
class Robot : public MovingObject
{
    friend class TestStudyInPink;
public:
    RobotType robot_type;
    BaseItem * item;
    Criminal * criminal;
    
public:
    Robot(int index, const Position & init_pos, Map * map, Criminal * Criminal, RobotType robot_type);
private:
    // helper methods
    int cardinalNum(int num);
};

class RobotC : public Robot
{
    friend class TestStudyInPink;
public:
    RobotC(int index, const Position & init_pos, Map * map, Criminal * Criminal,  RobotType robot_type = C);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    int getDistance(Sherlock * sherlock) const;
    int getDistance(Watson * watson) const ;
    string str() const;
};

class RobotS : public Robot
{
    friend class TestStudyInPink;
private:
    Sherlock * sherlock;
public:
    RobotS(int index, const Position & init_pos, Map * map, Criminal * Criminal, Sherlock * sherlock, RobotType robot_type = S);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;
};

class RobotW : public Robot
{
    friend class TestStudyInPink;
private:
    Watson * watson;
public:
    RobotW(int index, const Position & init_pos, Map * map, Criminal * Criminal, Watson * watson, RobotType robot_type = W);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;
};

class RobotSW : public Robot
{
    friend class TestStudyInPink;
private:
    Sherlock * sherlock;
    Watson * watson;
public:
    RobotSW(int index, const Position & init_pos, Map * map, Criminal * Criminal, Sherlock * sherlock, Watson * watson, RobotType robot_type = SW);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;
};


// BaseItem, BaseBag,...
class BaseItem
{
    friend class TestStudyInPink;
public:
    BaseItem * next = nullptr;
    ItemType itemType;
public:
    virtual bool canUse(Character * obj, Robot * robot) = 0;
    virtual void use(Character * obj, Robot * robot) = 0;
};

class MagicBook : public BaseItem
{
    friend class TestStudyInPInk;
public:
    MagicBook() { itemType = MAGIC_BOOK; }
    bool canUse(Character * obj, Robot * robot);
    void use(Character * obj, Robot * robot);
};

class EnergyDrink : public BaseItem
{
    friend class TestStudyInPink;
public:
    EnergyDrink() { itemType = ENERGY_DRINK; }
    bool canUse(Character * obj, Robot * robot);
    void use(Character * obj, Robot * robot);
};

class FirstAid : public BaseItem
{
    friend class TestStudyInPink;
public:
    FirstAid() { itemType = FIRST_AID; }
    bool canUse(Character * obj, Robot * robot);
    void use(Character * obj, Robot * robot);
};

class ExcemptionCard : public BaseItem
{
    friend class TestStudyInPink;
public:
    ExcemptionCard() { itemType = EXCEMPTION_CARD; }
    bool canUse(Character * obj, Robot * robot);
    void use(Character * obj, Robot * robot);
};

class PassingCard : public BaseItem 
{
    friend class TestStudyInPink;
private:
    string challenge;
public:
    PassingCard(const string & challenge) : challenge(challenge) { itemType = PASSING_CARD; };
    bool canUse(Character * obj, Robot * robot);
    void use(Character * obj, Robot * robot);
};

class BaseBag
{
    friend class TestStudyInPink;
protected:
    Character * obj;
    BaseItem * head;    
public:
    BaseBag(Character * obj) : obj(obj) { head = nullptr; }
    virtual ~BaseBag() {}
    // return true if insert successfully
    virtual bool insert(BaseItem * item) { return false; };
    // return the item as described above, if not found, return NULL
    virtual BaseItem * get() { return nullptr; };
    // return the item as described above, if not found, return NULL
    virtual BaseItem * get(ItemType itemType) { return nullptr; };
    // Bag[count=<c>;<list_items>]
    virtual string str() const { return ""; };
};

class SherlockBag : public BaseBag
{
    friend class TestStudyInPink;
private:
    int maxSize, currentSize;
public:
    SherlockBag(Sherlock * sherlock);
    ~SherlockBag();
    bool insert(BaseItem * item);
    BaseItem * get();
    BaseItem * get(ItemType itemType);
    string str() const; 
    // additional methods
    BaseItem * peak(ItemType itemType);
    int getSize() const {   return currentSize;   }
    int getMaxSize() const {    return maxSize;    }
};

class WatsonBag : public BaseBag
{
    friend class TestStudyInPink;
private:
    int maxSize, currentSize;
public:
    WatsonBag(Watson * watson);
    ~WatsonBag();
    bool insert(BaseItem * item);
    BaseItem * get();
    BaseItem * get(ItemType itemType);
    string str() const;  
    // additional methods
    BaseItem * peak(ItemType itemType);
    int getSize() const {   return currentSize;   }
    int getMaxSize() const {    return maxSize;    }
};

class StudyPinkProgram {
    friend class TestStudyInPink;
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    SherlockBag * sherlock_bag = new SherlockBag(sherlock);
    WatsonBag * watson_bag = new WatsonBag(watson);

    Map * map;
    ArrayMovingObject * arr_mv_objs;

    Robot * newRobot = nullptr;

public:
    StudyPinkProgram(const string & config_file_path);
    ~StudyPinkProgram();

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose);
    // additional methods
    void sherlockEvents(int index);
    void watsonEvents(int index);
    void criminalEvents(int index, int & criminalMoves);
    // ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
