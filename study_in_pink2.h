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
protected:
    ElementType type;
public:
    MapElement(ElementType in_type) : type(in_type) {};
    virtual ~MapElement() {};   
    virtual ElementType getType() const {   return type;   };
};

class Path : public MapElement {
public:
    Path() : MapElement(PATH) {};
    ~Path() {};
};

class Wall : public MapElement {
public:
    Wall() : MapElement(WALL) {};
    ~Wall() {};
};

class FakeWall : public MapElement {
private:
    int reg_exp;
public:
    FakeWall() : MapElement(FAKE_WALL), reg_exp(0) {};
    FakeWall(int in_reg_exp) : MapElement(FAKE_WALL), reg_exp(in_reg_exp) {};
    ~FakeWall() {};
    // additional methods
    int getRegExp() const {    return reg_exp;   }
};

class Map {
private:
    int num_rows, num_cols;
    MapElement *** elements;
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls);
    ~Map();
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
};

class Position {
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
    virtual int getExp() const {return -1;}
};

class Sherlock : public MovingObject {
private:
    // TODO
    string moving_rule;
    int hp;
    int exp;

public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    string str() const;
    int getExp() const {    return exp;   }
};

class Watson : public MovingObject {
private:
    // TODO
    string moving_rule;
    int hp;
    int exp;

public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    string str() const;
    int getExp() const {    return exp;   }
};

class Criminal : public MovingObject {
private:
    // TODO
    Sherlock * sherlock;
    Watson  * watson;
public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    Position getCurrentPosition() const {   return pos; }
    Position getNextPosition();
    void move();
    string str() const;

};

class ArrayMovingObject {
private:
    // TODO
private:
    MovingObject ** arr_mv_objs;
    int count;
    int capacity;
public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject() ;
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
    int map_num_rows, map_num_cols;
    int map_num_moving_objects;
    int num_walls;  // Number of Wall objects
    Position * arr_walls; 
    // int num_fake_walls;  // Number of FakeWall objects
    // Position * arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    string watson_moving_rule;
    Position watson_init_pos;
    Position criminal_init_pos;
    int num_steps;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
};

// Robot, BaseItem, BaseBag,...

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

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

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
