# 10/03/2024
init code <br>
Implement MapElement<br>
Implement Path, Wall, FakeWall <br>
# 11/03/2024
implement constructor and destructor of Map. <br>
Implement constructors and some methods of Position. <br>
Move implementation of MapElement from cpp to .h    <br>
# 12/03/2024
implement MovingObject <br>
added more additional methods, defined npos in Position and isValid in Map <br>
implement some of Sherlock class <br>
# 13/03/2024
changed constructor of MovingObject <br>
added overloaded operator == != in Position <br>
implemented Sherlock <br>
implemented Watson <br>
# 14/03/2024
changed getExp in movingObject to non pure virtual function <br>
updated isValid in map to accept Criminal as another case in FakeWall <br>
implemented Criminal class <br>
# 16/03/2024
implemented ArrayMovingObjects <br>
added overloaded method for class Position <br>
started implement Configuration <br>
there is some errors in sa_tc_02_config <br>
Configuration will need to be updated this version is just testing <br>
Implemented Configuration --- testing <br>
==Nice BUGS==
Got some bugs in reading file at Sherlock_INIT_POS --- fixed <br>
REASON: <br>
**The sscanf expects a char* to write to, but sherlock_moving_rule and watson_moving_rule are string object**<br>
**so this will cause undefined behavior (my program stopped at SHERLOCK_INIT_POS)**<br>
**To fix this, i used a temp char buffer to read the string then assign it to string variable**<br>
Probably will changed this Configuration later but now it worked and iam so happy! <br>
Maybe needed to changed the size of buffer if needed <br>
# 17/03/2024
Improved COnfiugration to cover more options <br>
Added my own sa_tc_02 for Configuration and changed how str in Configuration will output(from ";" to " ") <br>
TestStudyInPink is friend of everyone! <br>
corrected typos in constructor of Sherlock, Watson and Criminal pos -> init_pos <br>
Changed exp of fake wall in Map constructor when created (r ∗ 257 + c ∗ 139 + 89) % 900 + 1 <br>
Tested sa_tc_01 yayy <br>
# 19/03/2024
if the position that Criminal will go to is not valid, getNextPosition of Criminal should return Position::npos <br>
**The process of creating Robot will put in class Criminal or elsewhere ?** <br>
added new method for Criminal getPrevPosition and added prevPos attributes <br>
implemented RobotC <br>
testing git and github <br>
# 20/03/2024
Changed the order of constructor in RobotC <br>
then changed it back (because main.cpp got error at tc_03) <br>
Created Robot class <br>
Changed logic in getNextPosition of Criminal. if the position that Criminal will go to is invalid, shoudl assign to npos not return <br>
Changed the implementation of getNextPosition in Criminal to handle logic problem <br>
**Very strange behavior can't run sa_tc03 after sa_tc01 but reverse worked ---> problem in sa_tc01** <br>
Implemented 4 different types of Robot <br>
# 21/03/2024
Simplified Robot class <br>
Implemented Character class receiced MovingObject as an ancestor class <br>