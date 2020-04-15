## Sorry, first draft of the readme might be a bit rough

# Yet-Another-SFML-Game
Small platformer game made in SFML/C++. 

I have been using this game to apply techniques I've learned about in books and on StackOverflow, particularly the idea of having a "screen" system and trying to learn more about memory management. Older files may be of lower quality than newer ones as this experience has been quite beneficial to me and this project reflects that skill development.

### Screen system

This one's mostly ~~nicked from~~ inspired by the SFML Wiki, to be honest.
 
The game's hierarchical screen system is built from a single base abstract class, `Screen`, from which all menu classes directly inherit, and from which the (soon to be) abstract `GameScreen` inherits. This `GameScreen` class contains all the common functionality for any of the game's levels, including data structures to hold enemies, platforms, projectiles and functions to handle all these, meaning that for any level created by another programmer, all they have to do is load the needed resources for the level and emplace back objects into the appropriate data structures, and let the parent class handle everything else. 

As for actually loading different screens, that's handled by this little block here:

```
while (currentScreen >= 0 && currentScreen <= screens.size()) 
{
	currentScreen = screens[currentScreen]->run(window);
}
```
Where the `run()` function of the screen at the index (`currentScreen`) will be executed next, and can return an int to break the loop and also return the index of the next desired screen (or return a value outside of the range of the vector to close the game)

New levels can be played by simply adding an instance of them to the `screens` vector in Source.cpp and having another screen's `run()` return the index of the screen (or placing it at the front of the vector). Adding a screen to `screens` is as easy as:
```
MenuScreen menu;
screens.push_back(&menu);
```

### Handling `update()` and `draw()` for objects in new levels (In progress!)

As mentioned earlier, all I have to do to make a new level is popluate the appropriate vectors and the base `GameScreen` class will handle the rest, as long as I call `GameScreen::run()` in the new derived class's `run()` function.

This is all handled by having `GameScreen` iterate through each of the vectors of game objects (which are inherited and can be populated by the child class) in its own `update()` and `draw()` functions , which are then called by its `run()` function.

### Memory Management

Currently, the `GameScreen` class has vectors of unique pointers which are iterated through in the `render()` and `update()` methods to handle the game loops of the derived classes described above. Unique pointers go great with vectors; all you need to do is declare it like you would a vector of raw pointers but, well, with `std::unique_pointer` instead, like so:

`std::vector<std::unique_ptr<Platform>> platforms;`

Then, simply populate the vector:

`platforms.emplace_back(std::make_unique<Platform>(params));`

These were initially vectors of raw pointers handled by iterators but I have since updated them to smart pointers and now simply handle iterating through the vectors with an auto for loop, for example:

```
for(auto &p : projectiles)
{
	p->draw(window);
}
```
And to clean everything up, rather than iterating through the vector and deleting everything, I just do nothing. Simply let it go out of scope and the unique pointers will handle the garbage collection themselves

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
