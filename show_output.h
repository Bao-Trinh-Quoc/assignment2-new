#include "study_in_pink2.h"

void tc_1001() {
    cout << "----- Testcase 01 -----" << endl;
    Path path = Path();
    cout << path.getType();
}

class TestStudyInPink {
public:
    TestStudyInPink() = default;
    
    static void tc_1001() {
        ::tc_1001();
    }
    static void tc_1354() {
        cout << "----- Testcase 354 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};
    
        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
    
        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 290, 520);
    
        Watson * watson = new Watson(2, "LU", Position(2, 1), map, 320, 350);
    
        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
    
        RobotC * robotC = new RobotC(3, Position(1, 4), map, criminal);
    
        sherlock->move();
    
        cout << sherlock->str() << endl;
    
        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete robotC;
    }
};

void test() {
    TestStudyInPink::tc_1001();
    TestStudyInPink::tc_1354();
}