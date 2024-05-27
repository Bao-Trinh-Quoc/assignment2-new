/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 01.03.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink2.h"
#include "extra_tc.h"

using namespace std;

// void g_satc_02() { // global
//     cout << "----- Sample Testcase 02 -----" << endl;
//     Configuration * config = new Configuration("sa_tc_02_config");
//     /* my testcase */
//     // Configuration * config = new Configuration("my_sa_tc_02_config");
//     cout << config->str() << endl;
//     delete config;
// }

// class TestStudyInPink {
// public:
//     TestStudyInPink() = default;

//     static void satc_01() {
//         cout << "----- Sample Testcase 01 -----" << endl;
//         int num_walls = 3;
//         Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
//         int num_fake_walls = 1;
//         Position arr_fake_walls[] = {Position(2, 0)};

//         Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        
//         Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
//         cout << sherlock->str() << endl;

//         Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
//         cout << watson->str() << endl;

//         Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
//         cout << criminal->str() << endl;

//         cout << "* Sherlock makes a move" << endl;
//         sherlock->move();
//         cout << sherlock->str() << endl;

//         cout << "* Watson makes a move" << endl;
//         watson->move();
//         cout << watson->str() << endl;

//         cout << "* Criminal makes a move" << endl;
//         criminal->move();
//         cout << criminal->str() << endl;

//         ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(10);
//         arr_mv_objs->add(criminal);
//         arr_mv_objs->add(sherlock);
//         arr_mv_objs->add(watson);
//         cout << arr_mv_objs->str() << endl;

//         delete arr_mv_objs;
//         delete sherlock;
//         delete watson;
//         delete criminal;
//         delete map;
//     }

//     static void satc_02() {
//         g_satc_02();
//     }

//     static void satc_03() {
//         // Sample test for RobotC
//         cout << "----- Sample Testcase 03 -----" << endl;
//         int num_walls = 3;
//         Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
//         int num_fake_walls = 1;
//         Position arr_fake_walls[] = {Position(2, 0)};

//         Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

//         Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
//         Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
//         Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
//         criminal->move();

//         RobotC * robotC = new RobotC(3, Position(7,9), map, criminal);
//         cout << "Current position of Criminal: " << criminal->str() << endl;
//         cout << "Criminal makes a move" << endl;
//         criminal->move();
//         cout << "New position of Criminal: " << criminal->str() << endl;

//         cout << "Current position of robotC: " << robotC->str() << endl;
//         cout << "RobotC makes a move" << endl;
//         robotC->move();
//         cout << "New position of robotC: " << robotC->str() << endl;

//         delete sherlock;
//         delete watson;
//         delete criminal;
//         delete map;
//         delete robotC;
//     }
// };

// // add more testcases here
// void tc_1001() {
//     cout << "----- Testcase 01 -----" << endl;
//     Path path = Path();
//     cout << path.getType();
// }

int main(int argc, const char * argv[]) {
    // TestStudyInPink::satc_01();
    // TestStudyInPink::satc_02();
    // TestStudyInPink::satc_03();
    
    // TestStudyInPink::tc_1001();
    // cout << endl;
    // TestStudyInPink::tc_1004();
    // cout << endl;
    // TestStudyInPink::tc_1009();
    // cout << endl;
    // TestStudyInPink::tc_1014();
    // cout << endl;
    // TestStudyInPink::tc_1015();
    // cout << endl;
    // TestStudyInPink::tc_1016();
    // cout << endl;
    // TestStudyInPink::tc_1017();
    // cout << endl;
    // TestStudyInPink::tc_1043();
    // cout << endl;
    // TestStudyInPink::tc_1057();
    // cout << endl;
    // TestStudyInPink::tc_1062();
    // cout << endl;
    // TestStudyInPink::tc_1063();
    // cout << endl;
    // TestStudyInPink::tc_1066();
    // cout << endl;
    // TestStudyInPink::tc_1067();
    // cout << endl;
    // TestStudyInPink::tc_1070();
    // cout << endl;
    // TestStudyInPink::tc_1094();
    // cout << endl;
    // TestStudyInPink::tc_1099();
    // cout << endl;
    // TestStudyInPink::tc_1109();
    // cout << endl;
    // TestStudyInPink::tc_1114();
    // cout << endl;
    // TestStudyInPink::tc_1120();
    // cout << endl;
    // TestStudyInPink::tc_1132();
    // TestStudyInPink::tc_1138();
    // TestStudyInPink::tc_1143();
    // TestStudyInPink::tc_1153();
    // TestStudyInPink::tc_1159();
    // TestStudyInPink::tc_1167();
    // TestStudyInPink::tc_1171();
    // TestStudyInPink::tc_1181();
    // TestStudyInPink::tc_1185();
    // TestStudyInPink::tc_1199();
    // TestStudyInPink::tc_1211();
    // TestStudyInPink::tc_1223();
    // TestStudyInPink::tc_1235();
    // TestStudyInPink::tc_1247();
    // TestStudyInPink::tc_1253();
    // TestStudyInPink::tc_1286();
    // TestStudyInPink::tc_1278();
    // TestStudyInPink::tc_1354();
    TestStudyInPink::tc_1194();

    return 0;
}   