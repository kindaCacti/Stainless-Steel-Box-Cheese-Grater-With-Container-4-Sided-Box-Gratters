# What is it?

This is a repo for Mateusz Wawrzyniak and Mateusz Ogniewski's project for PROI. We decided to implement chess using c++ with a basic bot to come with it. We think we did a good job but the bot could be better.

# How is the code written?

We decided to split the work between us two more or less equally. Because none of us were expirienced in making GUI in c++ we decided that one of us will learn how to do it, while the other will write the chess api.

### What is CheesyApi?

It is the functionality of the game. We decided to split the parts into two APIs and the App that only asks the APIs for response. So in this folder we have described how the pieces move on the board, and the board itself.

### What is CheesyBot?

It is the API for the bot that plays chess. We wanted to do a lot more advanced bot, but in the end it turned out to be a bit harder than we firstly aticipated.

### What is CheesyEngine?

It is the core graphics code, responsible for communicating with graphics card via OpenGL. We are using there some basic libraries like stb_image to simplify image loading or glfw for easier window creation. But overall the entire engine is written from scratch in plain OpenGL.

### What is CheesyApp?

It contains the actual code that is being executed on start. It binds all of the above components into one. It is responsible for creating and running the game loop as well as handling all the inputs from the user.

# How to run the code?

First you have to have OpenGL configured on your device, we also require some non-default extensions for OpenGL - GLFW and GLEW. If you are using MINGW64 on windows they can be installed simply by typing in the console the following commands:\
\
`pacman -S mingw-w64-x86_64-glfw`\
`pacman -S mingw-w64-x86_64-glew`\
\
After that all you have to do is configure cmake to use the compiler with correct libraries installed and build the app.\
Be careful while running the app, because for it to work properly you have to be outside the build directory. We recommend using the command\
`./build/app` to run the app.\
\
If running the gui does not work for you, you can still play chess in command line by running a command `./build/demo`.

# What is the reason for the name Cheese?

While discussing the ideas for the app we mistyped "Chess" as "Cheese" and we thought that it was funny so we went with the name. Thus also all the parts of our project have cheese-related names.
