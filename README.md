# Flying Stickman Game

# Stage 3 additions
*DEMONSTRATION* Videos are available in the "Demonstration" folder, "Demonstration1.mp4" shows most of the stage 3 functionalities, including proper collision, score, lives & stage reset, power-ups, currency collectibles (EXTENSION), shop menu (EXTENSION) and result screen (EXTENSION). "Demonstration2.mp4" demonstrates the backwards compatibility.

*INSTRUCTIONS* Before running the game in stage 3 mode, please make sure to copy the "stage3config.txt" located in the "config" folder, and the pngs "tinyPowerUp.png", "normalPowerUp.png", "largePowerUp.png", "giantPowerUp.png" and "coin.png" within the "img" folder to the BUILD FOLDER.

Stage 3 saw a plethora of changes to the game, the following list of classes have been added to make these changes possible:

	- *EXTENSION* CurrencyFactory & Currency class : implements a flyweight design pattern which allows for active time generation of Currency objects (they are collectable currencies with randomized coordinates and freqeuncies generated at the start of a stage, collecting them gives a small score increase and when opening the pause menu, a shop is available to spend these collectable currencies to buy power-ups). NOTE: Currency collectibles DO NOT reset into existence when losing a life and restarting the stage, since it simply would not be fair, that was an intentional design decision.

	- GameObserver: implements an observer design pattern that tracks game data, including number of jumps executed, number of collisions (divided by top, bottom, left, right), number of shop purchases, etc. Stage3Player, Stage3Game and Stage3PauseDialog are all responsible for keeping a copy of GameObserver (a shared_ptr) and updating these counters (notify) when appropriate.

	- PlayerState and its 3 subclasses--GiantPlayerState, LargePlayerState and TinyPlayerState: PlayerState is kept by Stage3Player and implements a state design pattern, each state of stickman is associated with different collision effects or player initial stats changes.

	- ObstacleVelocityUpdateVisitor: visits the children of Entity/EmptyEntity objects to update all of its children's velocity.

	- PowerUpFactory & PowerUp class: implements a flyweight design pattern similar to CurrencyFactory & Currency classes. PowerUps are differed by an index abstracted using an enum for easy identification.

	- Stage3Background: overwrites the position update method of original Background so that background movement is dependent on a given velocity as well.

	- Stage3Config: reads stage 3 config. For format see #Config Format Style Changes.

	- Stage3Game: game dialog class that allows rendering of the entire game. Game componenets of a Stage 3 Game are: Stage3Player, Stage3Background, Stage3Obstacle (stored as a root entity using stage 2's composite design pattern), PowerUpFactory (maintains intrinsic & extrinsic state of create-on-demand PowerUp objects), CurrencyFactory (similar to PowerUpFactory but for Currency objects), GameObserver. Also maintains the current score, the formula is: each currency collectible and power up has a score worth (can be negative, e.g. the giant power up is set to -50 in the provided stage3config since the developer believes the power-up is too powerful and players should be penalized for using it), that adds to a base score (starts at 0) when collected. Each stage reset due to losing lives -100 from this base score. When a stage is completed, a clear score of 200 * number of obstacles overcome is added to the base score. In addition, there is a time bonus, which starts at 2000 when stage begins, and slowly decrease by 10 per second as time is spent within the stage, that is added to the base score upon stage completion, and is then reset to 2000 for the next stage.

	- Stage3Obstacle: A subclass of leaf entity, Stage3Obstacle now stores only its position, color, width and height, managed by a stage parent root and collisions with player are checked by player since the effects generally occur on the player.
	- *EXTENSION* Stage3PauseDialog: A new pause menu for the game, now has a shop menu that allows player to spend collectible currencies to buy power-ups. Continue or quit the game through this menu.

	- Stage3Player: now internally handles checking collisions of itself with obstacles, as well as y-velocity updates when jumping. Its state is affected by multiple objects, include obstacles, power-ups and currency collectibles.

	- Stage3Tester: testing framework for stage 3. This testing framework is created and ran automatically upon starting a game with stage 3 toggled on. Fail/Pass status is displayed in std output.

	- StageGoal: A subclass of leaf entity, a goal object also follows the last obstacle of a stage, and collision with this object is checked differently, by only checking x-coordinate range overlap

	- StageMemento: implements a Memento design pattern for restoring game components to initial stage at start of level when a left/right collision occurs and stickman loses a life.

# Behavioural design patterns used
	- State design pattern to manage different stickman behaviour under different sizes
	- Memento design pattern to store initial stage positions allowing for a rollback when left/right collision occurs
	- Flyweight design pattern to lessen the memory usage effects of creating powerUps and currency items
 	- Observer design pattern that observes game statistics chagnes and makes note of it using a counter, reported back to player when game cleared.
	- Visitor design pattern to add additional functionalities for the composite design pattern of stage 2.

# Config Format Style Changes
An additional parameter is added to config.txt called "stage3", 1 will toggle stage 3 on and 0 will turn it off (stage 1 or 2).

A new stage 3 config named "stage3config.txt" which must be located in the BUILD FOLDER is required if stage3 is toggled on. In addition, assets for the 4 basic power-ups must be present in the BUILD FOLDER as well, and their names are "tinyPowerUp.png", "normalPowerUp.png", "largePowerUp.png", "giantPowerUp.png". If you would like to also have the currency extension, the asset is in the BUILDFOLDER with name "coin.png".

Stage3Config file parameters:
	- "Lives" -- number of lives stickman has
	- "baseObstaclesPerStage" -- base amount of obstacle in a stage
	- "stageClearRequirementIncrementRate" -- amount of obstacle increment at this rate for each subsequent stage
	- "powerUpWidth" -- the width of your set of power-up assets to be rendered in
	- "powerUpHeight" -- the height of your set of power-up assets to be rendered in
	- "scoreWorth" -- defines the amount of score that obtaining each type of power-up will grant you, the sequence is "tiny,normal,large,giant", separated by comma(',') and no spaces in between
	- "currency" -- toggles the currency functionality on (1) and off (0)

FINAL REMARK: TO THE TWO PERSON THAT CODED (AND DIDN'T COMMENT :P) AND MADE THIS README BEFORE ME, PLEASE MAKE PROPER DOCUMENTATIONS FOR YOUR CODE FROM NOW ON THIS WAS HELL TO UNDERSTAND IN THE FIRST PLACE AND EVEN HARDER TO FIX WHAT THE SECOND GUY BROKE. :(

# STYLE GUIDE

The style for this project is based on the Google [C++ style guide](https://google.github.io/styleguide/cppguide.html). There are some variations:

## Headers:

  - System header includes come after local header includes
  - Only necessary headers, and all necessary headers, are included in each file

## Indentation:

  Indent your code with 4 spaces. Never use tabs or mix tabs and spaces. In cases of implied line continuation you should align wrapped elements vertically:

    <Class> foo(var_one,
                var_two,
                var_three,
                var_four)

## Naming:

  - ClassName, methodName, ui_action_functions, global_var_name, instance_var_name,
    function_parameter_name, local_var_name

  - Function names, variable names, and filenames should be descriptive; avoid abbreviation. In particular, do not use abbreviations that are ambiguous to the readers. Do not abbreviate by deleting letters within a word.

  ** Names to Avoid: single character names except for counters or iterators **

# EXTENSIONS

## Stage 1

  1. Main Menu screen where the user can select which background they would like to play the game in
  2. Parallax background to establish a scrolling background (stickman is stationary everything else is moving)
  3. Pause menu
    - User can change x position of the stickman as well as the size
    - Can resume play with the selected options
    - Options altered in real-time
  4. Background Music that has a infinite loop
  5. Animation of stickman, stickman is running.

## Stage 2
  1. Stickman can double jump. A variable can be changed to extend this to a triple jump or more. The Stickman also has a configurable jump height.
  2. Recursive Entity lookup. The GameState class has methods that allow the programmer to search the game state hierarchy for game entities by name, or by a substring of their name.

# DESIGN PATTERNS

## Stage 1

### Factory method

The game dialog is created by a factory to allow for easy extension. The separation of object construction from object use allows new game dialogs to be created without tight coupling of the start dialog and the game dialog.

### Singleton

The Config class is a singleton to make sure no more than one instance is ever created.

## Stage 2

### Composite pattern

The GameState class stores information about the current game's state. This includes a pointer to an  Entity object, the root of the game state hierarchy. The Entity class is an abstract class that defines pure virtual methods for updating, rendering and retrieving components (such as Colliders) for an object in the game (e.g. an Obstacle). There are two abstract subclasses of Entity: LeafEntity and CompositeEntity. LeafEntity currently does not add any additional functionality to the Entity class, but CompositeEntity allows for the updating and rendering of children Entities. There are three main concrete classes in the scene that have CompositeEntity as an ancestor: StickmanPlayer, Obstacle and EmptyEntity.

### Object adapter

There are two object adapters present in the code.
  1. Configuration is an abstract class, the target. ExtendedConfig (the adapter) accesses the Config singleton (adaptee) to extend the functionality of the Config class.
  2. Player is an abstract class, the target. StickmanPlayer (the adapter) accesses the Stickman object (adaptee) from the config singleton to allow for physics and collision operations.

### Factory method

The GameState class is the product (however instances of it can be created), produced by the createGameState() method in the abstract factory GameStateFactory. Stage2GameStateFactory is a concrete factory that produces Stage2GameState objects, which are concrete products inheriting from GameState. This allows for the customisation of GameState objects, and the easy creation of GameState instances in both the Stage2Game class and the Tester class.
