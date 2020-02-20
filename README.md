# SGE

> A component-based engine for the development of 2D physically simulated games.

As the name very originally states this is a very crude game engine developed as part of a project for a programming course.
And even if the definition of "game engine" is pretty blurried this probably isn't even a proper one in the modern sense.

As said this is build as the core of another project (see Non Gravitar), and it's meant to lay down the few systems and
abstractions needed in order to build the game comfortably. This is done as a separate library and will be developed with
reusability in mind not because it will be reused, rather because the separation between the engine and the content feels
like good practice and hopefully will help to make things more scalable and easier to conceptualize.

### A few key features

The main objects the user will work with and their purpose:

- **Scenes** - Game states that can be pushed in a stack-like structure, only the top one is executed through the game loop
- **GameObjects** - In this kind of design their function is basically just to hold Components
- **Components** - Object that specify the behaviour of a GameObject on some
- **Logic** - Object that have a series of overridable callbacks guaranteed to be called in a specific moment of the
game loop, it's the main mean through which the user can define his game logic doing so from a GameObject perspective

You can refer to [**Non Gravitar**](https://github.com/paolettiandrea/non-gravitar) as an example project that uses most of the features of this library.
If you want more information about this project you can find a brief report (in italian) [here](https://github.com/paolettiandrea/non-gravitar/blob/master/doc/Relazione.pdf).


### What this DOESN'T do
Since this is made in order to facilitate the development of a specific game and needs to be kept really simple there are a lot of things that are
commonly expected from an engine that won't be implemented. A few of the big ones:
- a GUI editor
- a set of content creation tools, all the content creation happens in code
- multi-threading
- serialization
- it probably won't even completely wrap around the two main library that it uses (SFML and Box2D)

## Dependencies
    git
    cmake
    
Additional dependencies are handled as git submodules and are built with the project(`SFML` and `Box2D`).
