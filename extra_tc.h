void tc_1001() {
    cout << "----- Testcase 01 -----" << endl;
    Path path = Path();
    cout << path.getType();
}
void tc_1004() {
    cout << "----- Testcase 04 -----" << endl;
    Wall wall = Wall();
    cout << wall.getType();
}
void tc_1009() {
    cout << "----- Testcase 09 -----" << endl;
    FakeWall *fakewall = new FakeWall(100);
    cout << fakewall->getType();
    delete fakewall;
}
void tc_1014() {
    cout << "----- Testcase 14 -----" << endl;
    int num_walls = 2;
    Position arr_walls[] = {Position(2, 3), Position(3, 0)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(2, 4)};
    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
}
void tc_1015() {
    cout << "----- Testcase 15 -----" << endl;
    int num_walls = 3;
    Position arr_walls[] = {Position(2, 4), Position(2, 3), Position(3, 1)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(1, 1)};
    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
}
void tc_1016() {
    cout << "----- Testcase 16 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4, 3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(3, 3)};
    Map * map = new Map(7, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
}
void tc_1017() {
    cout << "----- Testcase 17 -----" << endl;
    int num_walls = 1;
    Position arr_walls[] = {Position(4, 0)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(0, 0)};
    Map * map = new Map(6, 2, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
}
void tc_1057() {
    cout << "----- Testcase 57 -----" << endl;
    Position pos = Position("(0, 0)");
    cout << pos.str();
}
void tc_1062() {
    cout << "----- Testcase 62 -----" << endl;
    Position pos = Position("(3, 5)");
    cout << pos.getRow();
}
void tc_1063() {
    cout << "----- Testcase 63 -----" << endl;
    Position pos = Position(2, 4);
    cout << pos.getRow();
}
void tc_1066() {
    cout << "----- Testcase 66 -----" << endl;
    Position pos = Position("(3, 5)");
    pos.setRow(5);
    cout << pos.str();
}
void tc_1067() {
    cout << "----- Testcase 67 -----" << endl;
    Position pos = Position(2, 4);
    pos.setRow(3);
    cout << pos.str();
}
void tc_1070() {
    cout << "----- Testcase 70 -----" << endl;
    Position pos = Position(2, 4);
    cout << pos.isEqual(2, 4);
}
void tc_1094() {
    cout << "----- Testcase 94 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 1), Position(1, 3), Position(3, 1), Position(3, 3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(1, 2), map, 100, 250);
    cout << sherlock->getNextPosition().str() << endl;

    delete map;
    delete sherlock;
}
// moving rule có bước đi đầu tiên đến ô Wall
void tc_1095() {
    cout << "----- Testcase 95 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 1), Position(1, 3), Position(3, 1), Position(3, 3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(2, 1), map, 100, 250);
    cout << sherlock->getNextPosition().str() << endl;

    delete map;
    delete sherlock;
}
// moving rule có bước đi đầu tiên đến ô FakeWall
void tc_1096() {
    cout << "----- Testcase 96 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 1), Position(1, 3), Position(3, 1), Position(3, 3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(3, 2), map, 100, 250);
    cout << sherlock->getNextPosition().str() << endl;

    delete map;
    delete sherlock;
}
// moving rule có bước đi đầu tiên qua Wall và bị đứng yên, bước đi tiếp theo không qua Wall nên thực hiện di chuyển
void tc_1097() {
    cout << "----- Testcase 97 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 1), Position(1, 3), Position(3, 1), Position(3, 3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(4, 1), map, 100, 250);
    cout << sherlock->getNextPosition().str() << endl;

    delete map;
    delete sherlock;
}
// moving rule có bước đi làm nhân vật di chuyển ra ngoài bản đồ => nhân vật cần dừng lại ở rìa bản đồ
void tc_1098() {
    cout << "----- Testcase 98 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 1), Position(1, 3), Position(3, 1), Position(3, 3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(1, 4), map, 100, 250);
    cout << sherlock->getNextPosition().str() << endl;

    delete map;
    delete sherlock;
}
void tc_1099() {
    cout << "----- Testcase 99 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 1), Position(1, 3), Position(3, 1), Position(3, 3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(1, 2), map, 100, 250);
    sherlock->move();
    cout << sherlock->str();

    delete map;
    delete sherlock;
}
void tc_1109() {
    cout << "----- Testcase 109 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 1), Position(1, 3), Position(3, 1), Position(3, 3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(1, 2), map, 100, 250);
    cout << sherlock->str() << endl;

    delete map;
    delete sherlock;
}
void tc_1114() {
    cout << "----- Testcase 114 -----" << endl;
    int num_walls = 8;
    Position arr_walls[] = {Position(1, 1), Position(2, 1), Position(3, 1), Position(4, 1), Position(1, 3), Position(2, 3), Position(3, 3), Position(4, 3)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(1, 2), Position(4, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Watson *watson = new Watson(1, "LUR", Position(0, 1), map, 100, 250);
    cout << watson->getNextPosition().str() << endl;

    delete map;
    delete watson;
}
// moving rule có bước đi đầu tiên đến ô FakeWall và có thể đến được
void tc_1116() {
    cout << "----- Testcase 116 -----" << endl;
    int num_walls = 8;
    Position arr_walls[] = {Position(1, 1), Position(2, 1), Position(3, 1), Position(4, 1), Position(1, 3), Position(2, 3), Position(3, 3), Position(4, 3)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(1, 2), Position(4, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Watson *watson = new Watson(1, "DR", Position(3, 2), map, 100, 500);
    cout << watson->getNextPosition().str() << endl;

    delete map;
    delete watson;
}
// moving rule có bước đi đầu tiên đến ô FakeWall và không thể đến được
void tc_1117() {
    cout << "----- Testcase 117 -----" << endl;
    int num_walls = 8;
    Position arr_walls[] = {Position(1, 1), Position(2, 1), Position(3, 1), Position(4, 1), Position(1, 3), Position(2, 3), Position(3, 3), Position(4, 3)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(1, 2), Position(4, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Watson *watson = new Watson(1, "DR", Position(0, 2), map, 100, 500);
    cout << watson->getNextPosition().str() << endl;

    delete map;
    delete watson;
}
void tc_1120() {
    cout << "----- Testcase 120 -----" << endl;
    int num_walls = 8;
    Position arr_walls[] = {Position(1, 1), Position(2, 1), Position(3, 1), Position(4, 1), Position(1, 3), Position(2, 3), Position(3, 3), Position(4, 3)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(1, 2), Position(4, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Watson *watson = new Watson(1, "LUR", Position(0, 1), map, 100, 250);
    watson->move();
    cout << watson->str();

    delete map;
    delete watson;
}
void tc_1132() {
    cout << "----- Testcase 132 -----" << endl;
    int num_walls = 8;
    Position arr_walls[] = {Position(1, 1), Position(2, 1), Position(3, 1), Position(4, 1), Position(1, 3), Position(2, 3), Position(3, 3), Position(4, 3)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(1, 2), Position(4, 2)};

    Map * map = new Map(5, 5, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Watson *watson = new Watson(1, "LUR", Position(0, 1), map, 100, 250);
    cout << watson->str() << endl;

    delete map;
    delete watson;
}
void tc_1138() {
    cout << "----- Testcase 138 -----" << endl;
    int num_walls = 14;
    Position arr_walls[] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 4), Position(1, 5), Position(1, 6), Position(3, 2), Position(3, 4), Position(5, 0), Position(5, 1), Position(5, 2), Position(5, 4), Position(5, 5), Position(5, 6)};
    int num_fake_walls = 3;
    Position arr_fake_walls[] = {Position(1, 3), Position(2, 3), Position(5, 3)};

    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(0, 0), map, 100, 250);
    Watson * watson = new Watson(2, "URL", Position(0, 6), map, 100, 250);
    Criminal * criminal = new Criminal(0, Position(3, 3), map, sherlock, watson);
    cout << criminal->getNextPosition().str() << endl;

    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
}
void tc_1143() {
    cout << "----- Testcase 143 -----" << endl;
    int num_walls = 14;
    Position arr_walls[] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 4), Position(1, 5), Position(1, 6), Position(3, 2), Position(3, 4), Position(5, 0), Position(5, 1), Position(5, 2), Position(5, 4), Position(5, 5), Position(5, 6)};
    int num_fake_walls = 3;
    Position arr_fake_walls[] = {Position(1, 3), Position(2, 3), Position(5, 3)};

    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(0, 0), map, 100, 250);
    Watson * watson = new Watson(2, "URL", Position(0, 6), map, 100, 250);
    Criminal * criminal = new Criminal(0, Position(3, 3), map, sherlock, watson);
    criminal->move();
    cout << criminal->str();

    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
}
void tc_1153() {
    cout << "----- Testcase 153 -----" << endl;
    int num_walls = 14;
    Position arr_walls[] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 4), Position(1, 5), Position(1, 6), Position(3, 2), Position(3, 4), Position(5, 0), Position(5, 1), Position(5, 2), Position(5, 4), Position(5, 5), Position(5, 6)};
    int num_fake_walls = 3;
    Position arr_fake_walls[] = {Position(1, 3), Position(2, 3), Position(5, 3)};

    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "URL", Position(0, 0), map, 100, 250);
    Watson * watson = new Watson(2, "URL", Position(0, 6), map, 100, 250);
    Criminal * criminal = new Criminal(0, Position(3, 3), map, sherlock, watson);
    cout << criminal->str() << endl;

    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
}
void tc_1159() {
    cout << "----- Testcase 159 -----" << endl;
    int num_walls = 14;
    Position arr_walls[] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 4), Position(1, 5), Position(1, 6), Position(3, 2), Position(3, 4), Position(5, 0), Position(5, 1), Position(5, 2), Position(5, 4), Position(5, 5), Position(5, 6)};
    int num_fake_walls = 3;
    Position arr_fake_walls[] = {Position(1, 3), Position(2, 3), Position(5, 3)};

    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "LU", Position(0, 0), map, 100, 250);
    Watson * watson = new Watson(2, "LU", Position(0, 6), map, 100, 250);
    Criminal * criminal = new Criminal(0, Position(3, 3), map, sherlock, watson);
    cout << criminal->str() << endl;

    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
}
// "có 1 vị trí mà k/c từ Criminal đến Sherlock + Watson là dài nhất + vị trí đó không đi đến được"
void tc_1160() {
    cout << "----- Testcase 160 -----" << endl;
    int num_walls = 14;
    Position arr_walls[] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 4), Position(1, 5), Position(1, 6), Position(3, 2), Position(3, 4), Position(5, 0), Position(5, 1), Position(5, 2), Position(5, 4), Position(5, 5), Position(5, 6)};
    int num_fake_walls = 3;
    Position arr_fake_walls[] = {Position(1, 3), Position(2, 3), Position(5, 3)};

    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "LU", Position(0, 0), map, 100, 250);
    Watson * watson = new Watson(2, "LU", Position(6, 0), map, 100, 250);
    Criminal * criminal = new Criminal(0, Position(3, 6), map, sherlock, watson);
    cout << criminal->str() << endl;

    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
}
// "có 2 vị trí mà k/c từ Criminal đến Sherlock + Watson là dài nhất + vị trí đó có thể đi đến được"
void tc_1161() {
    cout << "----- Testcase 161 -----" << endl;
    int num_walls = 14;
    Position arr_walls[] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 4), Position(1, 5), Position(1, 6), Position(3, 2), Position(3, 4), Position(5, 0), Position(5, 1), Position(5, 2), Position(5, 4), Position(5, 5), Position(5, 6)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(1, 3), Position(5, 3)};

    Map * map = new Map(7, 7, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "LU", Position(3, 0), map, 100, 250);
    Watson * watson = new Watson(2, "LU", Position(3, 6), map, 100, 250);
    Criminal * criminal = new Criminal(0, Position(3, 3), map, sherlock, watson);
    cout << criminal->str() << endl;

    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
}
void tc_1167() {
    cout << "----- Testcase 167 -----" << endl;

    ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(5);
    cout << arr_mv_objs->str() << endl;
    delete arr_mv_objs;
}
void tc_1168() {
    cout << "----- Testcase 168 -----" << endl;

    int num_walls = 3;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
    
    ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(5);
    arr_mv_objs->add(sherlock);

    cout << arr_mv_objs->str() << endl;
    delete arr_mv_objs;
    delete sherlock;
    delete map;
}
bool tc_1171() {
    cout << "----- Testcase 171 -----" << endl;

    int num_walls = 3;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
    

    ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(3);
    bool result = arr_mv_objs->add(sherlock);
    delete arr_mv_objs;
    delete sherlock;
    delete map;

    return result;
}
void tc_1181() {
    cout << "----- Testcase 181 -----" << endl;

    Configuration * config = new Configuration("181.txt"); // 168
    cout << config->str() << endl;
    delete config;
}
void tc_1185() {
    cout << "----- Testcase 185 -----" << endl;

    Configuration * config = new Configuration("185.txt");
    cout << config->str() << endl;
    delete config;
}
void tc_1199() {
    cout << "----- Testcase 199 -----" << endl;
    int num_walls = 5;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(3,2), Position(4,3)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
    Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
    Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
    RobotS * robotS = new RobotS(3, Position(3,3), map, criminal, sherlock);
    int distance_old = robotS->getDistance();

    Position new_position = robotS->getNextPosition();
    RobotS * robotS_new = new RobotS(4, new_position, map, criminal, sherlock);
    int distance_new = robotS->getDistance();

    if(distance_old - distance_new >= 0) cout << "Can get close";
    else cout << "Can not get close";

    delete robotS;
    delete robotS_new;
    delete sherlock;
    delete watson;
    delete criminal;
    delete map;
}
void tc_1211() {
    cout << "----- Testcase 211 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(7, 0), Position(6, 1), Position(8, 1), Position(7,2)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
    Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);

    Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
    RobotW * robotW = new RobotW(3, Position(7,1), map, criminal, watson);
    int distance_old = robotW->getDistance();

    Position new_position = robotW->getNextPosition();
    RobotW * robotW_new = new RobotW(4, new_position, map, criminal, watson);
    int distance_new = robotW->getDistance();

    if(distance_old - distance_new >= 0) cout << "Can get close";
    else cout << "Can not get close";

    delete robotW;
    delete robotW_new;
    delete sherlock;
    delete watson;
    delete criminal;
    delete map;
}
void tc_1223() {
    cout << "----- Testcase 223 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(7, 0), Position(6, 1), Position(8, 1), Position(7,2)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
    Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);

    Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
    RobotSW * robotSW = new RobotSW(3, Position(7,1), map, criminal, sherlock, watson);
    int distance_old = robotSW->getDistance();

    Position new_position = robotSW->getNextPosition();
    RobotSW * robotSW_new = new RobotSW(4, new_position, map, criminal, sherlock, watson);
    int distance_new = robotSW->getDistance();

    if(distance_old - distance_new >= 0) cout << "Can get close";
    else cout << "Can not get close";

    delete robotSW;
    delete robotSW_new;
    delete sherlock;
    delete watson;
    delete criminal;
    delete map;
}
void tc_1235() {
    cout << "----- Testcase 235 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(7, 0), Position(6, 1), Position(8, 1), Position(7,2)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
    Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);

    Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
    RobotC * robotC = new RobotC(3, Position(7,1), map, criminal);

    cout << "First position: " << robotC->getCurrentPosition().str() << endl;
    Position new_position = robotC->getNextPosition();
    RobotC * robotC_new = new RobotC(4, new_position, map, criminal);

    cout << "Next position: " << robotC_new->getCurrentPosition().str() << endl;

    delete robotC;
    delete robotC_new;
    delete sherlock;
    delete watson;
    delete criminal;
    delete map;
}
void tc_1247() {
    cout << "----- Testcase 247 -----" << endl;
    int num_walls = 3;
    Position arr_walls[] = {Position(1, 2), Position(2, 2), Position(3, 2)};
    int num_fake_walls = 1;
    Position arr_fake_walls[] = {Position(2, 0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(2, 4), map, 250, 450);
    Watson * watson = new Watson(2, "LU", Position(2, 5), map, 300, 350);

    Criminal * criminal = new Criminal(0, Position(5, 6), map, sherlock, watson);

    ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(10);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
    arr_mv_objs->add(criminal);

    for(int i = 0; i < 2; i++) {
        criminal->move();
    }

    cout << arr_mv_objs->str() << endl;

    delete sherlock;
    delete watson;
    delete criminal;
    delete arr_mv_objs;
    delete map;
}
void tc_1297() {
    cout << "----- Testcase 297 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    cout << sherlockBag->str() << endl;

    delete map;
    delete sherlock;
    delete sherlockBag;
}

void tc_1298() {
    cout << "----- Testcase 298 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

    BaseItem * firstAid1 = new FirstAid();
    BaseItem * firstAid2 = new FirstAid();

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    sherlockBag->insert(firstAid1);
    sherlockBag->insert(firstAid2);

    cout << sherlockBag->str() << endl;

    delete map;
    delete sherlock;
    delete firstAid1;
    delete firstAid2;
    delete sherlockBag;
}
void tc_1299() {
    cout << "----- Testcase 299 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 80, 450);

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    for (int i=0; i<12; i++) {
        BaseItem * firstAid = new FirstAid();
        sherlockBag->insert(firstAid);
    }

    cout << sherlockBag->str() << endl;

    delete map;
    delete sherlock;
    delete sherlockBag;
}
void tc_1300() {
    cout << "----- Testcase 300 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 80, 450);

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    for (int i=0; i<14; i++) {
        BaseItem * firstAid = new FirstAid();
        sherlockBag->insert(firstAid);
    }

    cout << sherlockBag->str() << endl;

    delete map;
    delete sherlock;
    delete sherlockBag;
}
void tc_1302() {
    cout << "----- Testcase 302 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    sherlockBag->get();

    cout << sherlockBag->str() << endl;

    delete map;
    delete sherlock;
    delete sherlockBag;
}
void tc_1303() {
    cout << "----- Testcase 303 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

    BaseItem * passingCard1 = new PassingCard("RobotSW");
    BaseItem * passingCard2 = new PassingCard("all");

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    sherlockBag->insert(passingCard1);
    sherlockBag->insert(passingCard2);

    sherlockBag->get();

    cout << sherlockBag->str() << endl; // str

    delete map;
    delete sherlock;
    delete passingCard1;
    delete passingCard2;
    delete sherlockBag;
}
void tc_1304() {
    cout << "----- Testcase 304 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 120, 300);

    BaseItem * passingCard = new PassingCard("all"); 
    BaseItem * firstAid = new FirstAid();

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    sherlockBag->insert(passingCard);
    sherlockBag->insert(firstAid);

    sherlockBag->get();

    cout << sherlockBag->str() << endl;

    delete map;
    delete sherlock;
    delete passingCard;
    delete firstAid;
    delete sherlockBag;
}
void tc_1307() {
    cout << "----- Testcase 303 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 150, 450);

    BaseItem * passingCard1 = new PassingCard("RobotS");
    BaseItem * passingCard2 = new PassingCard("RobotC");

    BaseBag * sherlockBag = new SherlockBag(sherlock);

    sherlockBag->insert(passingCard1);
    sherlockBag->insert(passingCard2);

    sherlockBag->get(PASSING_CARD);

    cout << sherlockBag->str() << endl;

    delete map;
    delete sherlock;
    delete passingCard1;
    delete passingCard2;
    delete sherlockBag;
}
void tc_1323() {
    cout << "----- Testcase 323 -----" << endl;
    int num_walls = 4;
    Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
    int num_fake_walls = 2;
    Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};

    Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

    Watson * watson = new Watson(1, "RUU", Position(1, 3), map, 150, 450);

    BaseBag * watsonBag = new WatsonBag(watson);

    cout << watsonBag->str() << endl;

    delete map;
    delete watson;
}


class TestStudyInPink {
public:
    TestStudyInPink() = default;
    
    static void tc_1001() {
        ::tc_1001();
    }
    static void tc_1004() {
        ::tc_1004();
    }
    static void tc_1009() {
        ::tc_1009();
    }
    static void tc_1014() {
        ::tc_1014();
    }
    static void tc_1015() {
        ::tc_1015();
    }
    static void tc_1016() {
        ::tc_1016();
    }
    static void tc_1017() {
        ::tc_1017();
    }
    static void tc_1043() {
        cout << "----- Testcase 43 -----" << endl;
        int num_walls = 0;
        // Position arr_walls[] = {};
        Position * arr_walls = NULL;
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(5, 5)};
        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        for (int i = 0; i < map->num_rows; i++) {
            for (int j = 0; j < map->num_cols; j++) {
                cout << map->map[i][j]->getType();
                if (map->map[i][j]->getType() == FAKE_WALL) {
                    FakeWall *fakewall = dynamic_cast<FakeWall*>(map->map[i][j]);
                    cout << fakewall->getReqExp();
                }
                cout << "-";
            }
            cout << endl;    
        }
        delete map;
    }
    static void tc_1057() {
        ::tc_1057();
    }
    static void tc_1062() {
        ::tc_1062();
    }
    static void tc_1063() {
        ::tc_1063();
    }
    static void tc_1066() {
        ::tc_1066();
    }
    static void tc_1067() {
        ::tc_1067();
    }
    static void tc_1070() {
        ::tc_1070();
    }
    static void tc_1094() {
        ::tc_1094();
    }
    static void tc_1095() {
        ::tc_1095();
    }
    static void tc_1096() {
        ::tc_1096();
    }
    static void tc_1097() {
        ::tc_1097();
    }
    static void tc_1098() {
        ::tc_1098();
    }
    static void tc_1099() {
        ::tc_1099();
    }
    static void tc_1109() {
        ::tc_1109();
    }
    static void tc_1114() {
        ::tc_1114();
    }
    static void tc_1116() {
        ::tc_1116();
    }
    static void tc_1117() {
        ::tc_1117();
    }
    static void tc_1120() {
        ::tc_1120();
    }
    static void tc_1132() {
        ::tc_1132();
    }
    static void tc_1138() {
        ::tc_1138();
    }
    static void tc_1143() {
        ::tc_1143();
    }
    static void tc_1153() {
        ::tc_1153();
    }
    static void tc_1159() {
        ::tc_1159();
    }
    static void tc_1160() {
        ::tc_1160();
    }
    static void tc_1161() {
        ::tc_1161();
    }
    static void tc_1167() {
        ::tc_1167();
    }
    static void tc_1168() {
        ::tc_1168();
    }
    static void tc_1171() {
        ::tc_1171();
    }
    static void tc_1181() {
        ::tc_1181();
    }
    static void tc_1185() {
        ::tc_1185();
    }
    static void tc_1199() {
        ::tc_1199();
    }
    static void tc_1211() {
        ::tc_1211();
    }
    static void tc_1223() {
        ::tc_1223();
    }
    static void tc_1235() {
        ::tc_1235();
    }
    static void tc_1247() {
        ::tc_1247();
    }
    static void tc_1278() {
        cout << "----- Testcase 278 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};
    
        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
            
        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
    
        Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
    
        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
    
        BaseItem * excemptionCard = new ExcemptionCard();
    
        cout << excemptionCard->canUse(criminal, NULL);
    
        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete excemptionCard;
    }
    
    static void tc_1297() {
        ::tc_1297();
    }
    static void tc_1298() {
        ::tc_1298();
    }
    static void tc_1299() {
        ::tc_1299();
    }
    static void tc_1300() {
        ::tc_1300();
    }
    static void tc_1302() {
        ::tc_1302();
    }
    static void tc_1303() {
        ::tc_1303();
    }
    static void tc_1304() {
        ::tc_1304();
    }
    static void tc_1307() {
        ::tc_1307();
    }
    static void tc_1323() {
        ::tc_1323();
    }
    static void tc_1286() {
        cout << "----- Testcase 286 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5)};
        int num_fake_walls = 2;
        Position arr_fake_walls[] = {Position(2, 0), Position(4,0)};
    
        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
            
        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
    
        Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
    
        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
    
        BaseItem * passingCard = new PassingCard("all");
    
        cout << passingCard->canUse(criminal, NULL);
    
        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete passingCard;
    }
    static void tc_1194() {
        cout << "----- Testcase 194 -----" << endl;

        Configuration * config = new Configuration("185.txt");
        cout << "Map Num Rows: " << config->map_num_rows << endl;
        cout << "Map Num Cols: " << config->map_num_cols << endl;
        cout << "Max Num Moving Objects: " << config->max_num_moving_objects << endl;
        cout << "Num Wall: " << config->num_walls << endl;
        if (config->num_walls != 0) {
            cout << "Array Wall: " << config->arr_walls->str() << endl;
        }
        cout << "Num Fake Wall: " << config->num_fake_walls << endl;
        if (config->num_fake_walls != 0) {
            cout << "Array Fake Wall: " << config->arr_fake_walls->str() << endl;
        }
        cout << "Shelock Moving Rule: " << config->sherlock_moving_rule << endl;
        cout << "Sherlock init position: " << config->sherlock_init_pos.str() << endl;
        cout << "Sherlock init hp: " << config->sherlock_init_hp << endl;
        cout << "Sherlock init exp: " << config->sherlock_init_exp << endl;
        cout << "Watson Moving Rule: " << config->watson_moving_rule << endl;
        cout << "Watson init position: " << config->watson_init_pos.str() << endl;
        cout << "Watson init hp: " << config->watson_init_hp << endl;
        cout << "Watson init exp: " << config->watson_init_exp << endl;
        cout << "Criminal init position: " << config->criminal_init_pos.str() << endl;
        cout << "Number step: " << config->num_steps << endl;
        delete config;
    }
    static void tc_1253() {
        cout << "----- Testcase 253 -----" << endl;
        BaseItem * magicBook = new MagicBook();
        
        delete magicBook;
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