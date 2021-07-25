C++ OOP - Course Project
Remake of a "Fireboy & Watergirl" style game

The game we implemented is based on the game Fireboy & Watergirl.
The dog (the orange character) is controlled by the keyboard arrows, the cat (the gray character) is controlled by A- left, W-up D-right.
The game has 4 level.
The goal is for the two players, the dog, and the cat, to come home together in cooperation.
The level ends when they arrive, but in order to gain more victory points, they must collect all the snacks along the way and arrive at the allocated time to the house
(clarification: you do not have to take all the snacks and arrive home in time to complete the level).
The dog can collect bones, the cat can collect fish, and both can collect the common snacks (bone and fish together).
The number of attempts at each level is not limited, the achievements can only be improved at the level, an achievement that has already been achieved will not be deleted.
Beware of obstacles on the way - floors in special colors. A dog cannot step on a gray floor, a cat cannot step on an orange floor and both cannot step on a blue floor (dog and cat do not like to shower).
If the player hits his head at the bottom of the obstacle he will not be disqualified. When disqualified the level will start again.
Along the way, you have to use the various objects on the game board. Button and switch opening gates and rotating mirrors in 90 degrees.
A button will only work when an object touches it while a switch will work when one of the players turns it on (does not have to stay on it).
You can know who controls whom by the colors of the objects.
The boxes can be moved and used to reach the destination.
In addition, there are mirror boxes and mirrors that rotate in 90 degrees that change the direction of the laser ray and direct it from the source point to the destination point.
When the laser reaches the destination a gate in its color will open.
Restrictions: The size of the board is fixed at 18x18. The board will be framed with floors.
A set of one laser, source, and destination per level.
Each controlling object has only one controlled object and vice versa and they are in the same color כor user convenience.
You cannot play a level if you have not finished the previous level (except the first level).

Design:
1)Board class - A class implements a board in the game. Opens the stage file, reads it, and also closes it at the end.
2)Box class - A class implements a box in the game. Inherits from the MoveableObject class.
3)Button class - A class implements a button in the game. Inherits from the ControllingObject class.
4)CollisionHandler class - A class implements a CollisionHandler in the game.
5)Command class - A class implements a CollisionListener in the game.
6)CollisionListener class - A class implements a CollisionListener in the game. Inherits from the b2ContactListener class.
7)ControlledObject class - A class implements a ControlledObject in the game. Inherits from the StaticObject class.
8)Controller class - A class implements a Controller in the game.
9)ControllingObject class - A class implements a ControlledObject in the game.  Inherits from the StaticObject class.
10)Exit class - A class implements a exit in the game.  Inherits from the Command class.
11)Factory class - A class implements a factory in the game.
12)Floor class - A class implements a floor in the game. Inherits from the StaticObject class.  Inherits from the StaticObject class.
13)GameObject class -  A class that implements an object in the game. Includes members that implements the object.
14)Gate class - A class implements a gate in the game. Inherits from the ControlledObject class.
15)Help class - A class implements a help in the game. Inherits from the Command class.
16)HomeCommand class - A class implements a home command in the game. Inherits from the Command class.
17)House class - A class implements a house in the game. Inherits from the StaticObject class.
18)LaserDestination - A class implements a laser destinationin the game. Inherits from the ControllingObjectclass.
19)LaserSource - A class implements a laser source the game. Inherits from the StaticObject class.
20)Levels - A class implements a levels the game.  Inherits from the Command class.
21)Menu -  A class implements a menu the game. 
22)MenuButton -  A class implements a menu button the game. 
23)MirrorBox class - A class implements a mirror box in the game. Inherits from the MoveableObject class.
24)MoveableObject class -  A class that implements a objects that can move or be moved in the game, inherits from the GameObject class.
25)Obstacle class - A class implements a obstacle the game. Inherits from the StaticObject class.
26)Pause class - A class implements a pause the game. Inherits from the Command class.
27)Play class - A class implements a play the game. Inherits from the Command class.
28)Player class - Implements the players and is responsible for its implementation. Inherits from the MovableObject department.
29)Rsources class - Singleton class, a class that provides all the resources of the program - music, sounds, images and fonts.
30)Restart class - A class implements a restart the game. Inherits from the Command class.
31)Resume class - A class implements a resume the game. Inherits from the Command class.
32)RightAngleMirror class -  A class describing a rightAngleMirrorin the game. Inherits from the ControlledObject class.
33)StartLevel class - A class implements a startLevel the game.  Inherits from the Command class.
34)StaticObject class -  A class that describes a static object in the game, inherits from the GameObject class.
35)Switch class -  A class describing a switch in the game. Inherits from the ControllingObject class.
36)Treat class -  A class describing a treat in the game. Inherits from the StaticObject class.


List of project files:
Board.cpp + Board.h - contains the implementation of the Board class.
Box.cpp +Box.h - contains the implementation of the Box class.
Button.cpp + Button.h - contains the implementation of the Button class.
CollisionHandler.cpp + CollisionHandler.h - contains the implementation of the CollisionHandler class.
Command.cpp + Command.h class - contains the implementation of the Command class.
CollisionListener.cpp + CollisionListener.h - contains the implementation of the CollisionListener class.
ControlledObject.cpp + ControlledObject.h class - contains the implementation of the ControlledObject class.
Controller.cpp + Controller.h class - contains the implementation of the Controller class.
ControllingObject.cpp + ControllingObject.h - contains the implementation of the ControllingObject class.
Exit.h - contains the implementation of the Exit class.
Factory.h - contains the implementation of the Factory class.
Floor.cpp + Floor.cpp class - contains the implementation of the Floor class.
GameObject.cpp + GameObject.h -  contains the implementation of the GameObject class.
Gate.cpp + Gate.h - contains the implementation of the Gate class.
Help.h - contains the implementation of the Help class.
HomeCommand.h -  contains the implementation of the HomeCommand class.
House.cpp + House.h - contains the implementation of the House class.
LaserDestination.cpp + LaserDestination.h - contains the implementation of the LaserDestination class.
LaserSource.cpp + LaserSource.h - contains the implementation of the LaserSource class.
Levels.cpp + Levels.h - contains the implementation of the Levels class.
Menu.cpp + Menu.h - contains the implementation of the Menu class.
MenuButton.cpp + MenuButton.h - contains the implementation of the MenuButton class.
MirrorBox.cpp + MirrorBox.h - contains the implementation of the MirrorBox class.
MoveableObject.cpp + MoveableObject.h - contains the implementation of the MoveableObject class.
Obstacle.cpp + Obstacle.h - contains the implementation of the Obstacle class.
Pause.h - contains the implementation of the Pause class.
Play.h - contains the implementation of the Play class.
Player.cpp + Player.h -  contains the implementation of the Player class.
Rsources.cpp +  Rsources.h - contains the implementation of the Rsources class.
Restart.cpp + Restart.h - contains the implementation of the Restart class.
Resume.h - contains the implementation of the Resume class.
RightAngleMirror.cpp + RightAngleMirror.h class - contains the implementation of the RightAngleMirror class.
StartLevel.h - contains the implementation of the StartLevel class.
StaticObject.cpp + StaticObject.h -  contains the implementation of the StaticObject class.
Switch.cpp + Switch.h  - contains the implementation of the Switch class.
Treat.cpp + Treat.h -  contains the implementation of the Treat class.
main.cpp - implementation of the main function of the program.
Macros.h - A file that contains all the constants we have in the program.
TextureNames.txt- contains the names of all the textures in the game.
SoundNames.txt - contains the names of all the sounds in the game.
1.txt + 2.txt + 3.txt + 4.txt - stage files.
_. png - The textures of the object with the appropriate name.
_ .wav - The sounds of the program in the appropriate name.

Level file:
Each level will be received from a separate fixed name format file- numberlevel. For example, the name of the first level file is "1", etc.
These files should be of txt type.
The first line in the file is the time the players must complete the level in order to get the time achievement at the end of the level.
Then the floors will appear ('-'), an 18x18 floor frame must be written.
After the floors, we will write line by line the different objects as follows:
The char of an object, row and col (if the object has a certain type, it will be written at the end of the line according to the appropriate marking).
An object that is controlled by another object will be written a line before the controlling object.
You can see all the markups in the Macros.h file.

Main data structures:
Unique_ptr vectors hold the board objects according to the object type.
Unique_ptr pointers that hold both players.
const std::unordered_map <type, sf::Vector2i>.
std :: unordered_map <type, std :: array <float, 4 >> .

Notable algorithms:
3 design patterns:
Factory (templatic) - a factory for producing objects, creates the objects.
Command - a design template that produces menus. We implemented the main menu that provides the actions play, help, exit. Level creates a submenu that has the levels of the game.
From the game itself, you can pause and get to another submenu where there are the options, return to the level screen, restart, and resume.
Multimethod - CollisionHandler class which handles collisions between objects.

Known bugs:
When the player jumps close to the wall, if we press to move right or left it will stay in the air and try to walk.
There is a problem enlarging the screen to full size when the menu is displayed on the screen.

Other notes:
We have extensively used the Box2D physical library. The movement of objects in the game is physically calculated by the library, and the lasers are implemented with the library's ray-casting.
Any exception in the program will be written in the "log.txt" file located in the program folder and the program will end its execution.
