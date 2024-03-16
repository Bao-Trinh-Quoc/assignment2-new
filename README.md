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
