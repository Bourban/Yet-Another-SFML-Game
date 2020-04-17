## Disclaimer
I'm not sure what value this project on its own really has, most of the features have been added not because they'd be beneficial to the game, but because I'd read about them and wanted some practice implementing them. This is made worse by the time frame of the development, some of these files are close to a year old and it shows. What you'll find is inconsistencies in all sorts of things from variable names in various styles -- some of them are in Hungarian notation, some just camelCase -- to inconsistencies in design -- the `screens` vector in main is a vector of raw pointers but elsewhere I've employed smart pointers -- and plenty of unnecessary features (does a game with 6 inputs and no rebindable keys *really* need a dedicated input handler class?) because I just wanted some coding practice.

# Yet-Another-SFML-Game
Small platformer game made in SFML/C++. 

I have been using this game to apply techniques I've learned about in books and on StackOverflow, particularly the idea of having a "screen" system and trying to learn more about memory management. Older files may be of lower quality than newer ones as this experience has been quite beneficial to me and this project reflects that skill development.

### Character State Machine

The base character class in this project contains a pseudo state machine (just an enum member) which allows me to ceffectively control the flow of the character's `update()` function depending on the current state, making it far easier to manage (and read). For example if the character's current state is 'jumping' then `update()` will move the character down the appropriate amount. The value of this state member is also a condition for many of the character's input functions, for instance the character cannot crouch if they are currently 'jumping' conversely, if a character is crouching and they jump, the character will simply stand up (by changing the value of state to 'idle') instead. 

I decided to give this a go after reading about the State pattern in Game Programming Patterns. It tidied up the mess of booleans and 3-way if statements of previous iterations of this project and made my code much more manageable.

### Component classes

Several classess in the project are implemented through dependency injection as component classes. These classes are only instantiated as members (components) of other classes. They have an 'owner' reference member which points to the object that 'owns' it at runtime. The `PlayerController` class is one such class, and has a constructor which takes a `Player*` parameter, this is assigned to `m_owner` in an initialiser list:

`PlayerController::PlayerController(Player* player) : m_player(player){}`

An instance of this class is created whenever a `Player` is instantiated automatically, by way of having a `PlayerController` member and initialising it with the `this` pointer:

`Player::Player(params) : m_controller(this) {} `

The component class can access its parent through its `m_owner` member and the parent class can access the component class through its `m_controller` member.

I plan to combine this component system with the command pattern to handle inputs in future, where the `Character` class will recieve its commands from a method in its `CharacterController`, which can point at one of two derived classes by exploiting Polymorphism (either `PlayerController` or `EnemyController`), which will override this method with the appropriate behaviour --  either getting the player's inputs and returning commands, or getting commands from an AI controller.

### Screen system

This one's mostly ~~nicked from~~ inspired by the SFML Wiki, to be honest.
 
The game's hierarchical screen system is built from a single base abstract class, `Screen`, from which all menu classes directly inherit, and from which the (soon to be) abstract `GameScreen` inherits. This `GameScreen` class contains all the common functionality for any of the game's levels, including data structures to hold enemies, platforms, projectiles and functions to handle all these, meaning that for any level created by another programmer, all they have to do is load the needed resources for the level and emplace back objects into the appropriate data structures, and let the parent class handle everything else. 

As for actually loading different screens, that's handled by this little block here:

```
while (currentScreen >= 0 && currentScreen <= screens.size()) //as long as the 'currentScreen' value is still in the range
{							      //of the screens vector the loop will continue

	//every screen's run() function returns an int which points this loop the the 'next' screen
	currentScreen = screens[currentScreen]->run(window);
}
```
Where the `run()` function of the screen at the index (`currentScreen`) will be executed next, and can return an int to break the loop and also return the index of the next desired screen (or return a value outside of the range of the vector to close the game)

New levels can be played by simply adding an instance of them to the `screens` vector in Source.cpp and having another screen's `run()` return the index of the screen (or placing it at the front of the vector). Adding a screen to `screens` is as easy as:
```
MenuScreen menu;		//create a new screen object
screens.push_back(&menu);	//push the address of this object to the vector
```

### Handling `update()` and `draw()` for objects in new levels (In progress!)

As mentioned earlier, all I have to do to make a new level is popluate the appropriate vectors and the base `GameScreen` class will handle the rest, as long as I call `GameScreen::run()` in the new derived class's `run()` function.

This is all handled by having `GameScreen` iterate through each of the vectors of game objects (which are inherited and can be populated by the child class) in its own `update()` and `draw()` functions , which are then called by its `run()` function.

All a new derived screen would need would be something like:

```
class Level2Screen : public GameScreen
{

int run(sf::RenderWindow &window) { GameScreen::run(window) + level specific things here };

bool loadContent() { load your resources and populate your lists here };

};
```

### Memory Management

Currently, the `GameScreen` class has vectors of unique pointers which are iterated through in the `render()` and `update()` methods to handle the game loops of the derived classes described above. Unique pointers go great with vectors; all you need to do is declare it like you would a vector of raw pointers but, well, with `std::unique_pointer` instead, like so:

`std::vector<std::unique_ptr<Platform>> platforms;`

Then, simply populate the vector:

`platforms.emplace_back(std::make_unique<Platform>(params));`

These were initially vectors of raw pointers handled by iterators but I have since updated them to smart pointers and now simply handle iterating through the vectors with a range-based for loop. I simply iterate through the vector and call each element's `update()` and `draw()` within `GameScreen`'s own `update()` and `draw()` and then any amount of objects will be automatically handled:

```
//In GameScreen::update()

for(auto &p : projectiles)
{
	p->update(params);
}
```
and
```
//In GameScreen::draw()

for(auto &p : projectiles)
{
	p->draw(params);
}
```

And to clean everything up, rather than iterating through the vector and deleting each element, I just clear the vector. The smart pointers will then handle the garbage collection themselves.

### Resource allocation

I make several ~~basically unnoticable~~ optimisations when populating my vectors. First and foremost, using `reserve()` before populating the list to prevent it from having to be resized (and thus having to copy each element to new memory) when adding new elements and secondly, using `emplace_back()` to create the new object (or rather, the pointer to it, since I use `make_unique`) directly where I want it rather than using `push_back()` as I did earlier in the project with screen system. This prevents yet another needless copy operation.

Rather than something like this:
```
platforms.push_back( new Platform(params)); //don't forget to delete!
platforms.push_back( new Platform(params)); //don't forget to delete!
platforms.push_back( new Platform(params)); //don't forget to delete!
```
We have (for example):
```
platforms.reserve(3);

platforms.emplace_back(std::make_unique<Platform>(params));
platforms.emplace_back(std::make_unique<Platform>(params));
platforms.emplace_back(std::make_unique<Platform>(params));
```
From at least 1 unnecessary copy operation per new element plus more when resized to *none!*

### Character Platforming and Physics

I should point out that this mechanic is one of the oldest and probably the worst code in the project, but, since it works, and in the interest of working towards finishing the game, I'm just going to leave this in, as a reminder of how *not* to implement a jump feature.

Built on this state system is the platforming system; every `Character` objecct has an `fDeltaY` member which, as you might guess, is the character's movement delta on the Y axis. This is applied to the character's movement if they are in the 'jumping' state, when the character jumps this is given a large positive value (controlled by `jumpHeight` in the `Character` class) and every subsequent frame this is reduced by the character's maximum fall speed (`maxFallSpeed`) to act as gravity, so that the character's jump mimics a real jump; a large initial impulse that is gradually reduced by gravity until it turns negative, and the character begins to fall. This negative velocity is capped at `maxFallSpeed` to mimic a terminal velocity.

```
//in Character::update()
switch(state)

...

case jumping:
	if (fDeltaY > -maxFallSpeed)
		fDeltaY -= maxFallSpeed * elapsed;
	else
		fDeltaY = -maxFallSpeed;

	this->move(0, -(fDeltaY * elapsed));

	break;
```

(I should point out that these values are multiplied by `elapsed` in an attempt to compensate for varying frame rates. Like I said, some areas of this project are older, and I would not implement this in this manner if I were to start the project again because it technically makes the game non-deterministic (with the caveat of always having varying frame rates), and could be the source of some *interesting* bugs. Instead of just running `update()` as often as possible, I'd now just limit `update()` to a specific update rate and just use smaller values in these functions.)

The positive value of `fDeltaY` is set directly in the `jump()` function:
```
void Character::jump()
{
	if (state == crouching)
	{
		state = idle;
		return;
	}
	if (state != jumping && state != attacking)
	{
		bIsTouchingFloor = false;
		state = jumping;
		fDeltaY = jumpHeight;
	}
}
```
As for knowing when to stop 'jumping', the character has a rectangle member to act as the character's feet. This is used in `GameScreen` to check for collisions against all the elements of the `platforms` vector (wow this older code is quite messy, looking back):

```
//In GameScreen::update()
for(auto& p : platforms)
{
	if (p_player->m_feetBox.intersects(p->getTop()) && p_player->getDeltaY() < 0)
	{
		p_player->setIsTouchingFloor(true);
		break;
	}

	p_player->setIsTouchingFloor(false);
}
```

If there is a collision, then a boolean in the character object, `bIsTouchingFloor`, is set to true via a getter (seriously, this gets messier the more I explain). The value of this boolean is checked against in `Character`'s `update()` function:

```
if (bIsTouchingFloor)
{
	if (state == jumping)
	{
			state = idle;
		fDeltaY = -50;
	}
}
```

Writing this bit of readme has really made me want to tear this whole mechanic out and do it *better*. All these getters for `Character` members when I could have just referenced `platforms` in a function in the `Character` class and saved myself a lot of trouble.

