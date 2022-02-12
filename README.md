![Heavy Engine](https://github.com/xSnapi/Heavy/blob/master/Images/heavy.png?raw=true)

# Heavy
## Engine for SFML games
The main goal of Heavy is to make it as close to SFML syntax as possible. For example creating rigid body is easy as ```hv::RigidBody rb;``` and thats really it.
***

## Heavy uses:

![alt text](https://www.sfml-dev.org/images/logo.png "SFML")
![alt text](https://box2d.org/images/logo.svg "box2D")
![alt text](https://github.com/bombomby/optick/blob/master/samples/UnrealEnginePlugin/Resources/Icon128.png?raw=true "OPTICK")


### [SFML](https://github.com/SFML/SFML) | [Box2D](https://github.com/erincatto/box2d) | [Optick](https://github.com/bombomby/optick) | [ImGui](https://github.com/ocornut/imgui)


<br/>
<br/>

## Why "Heavy" tho? 
As inexperienced programmer I thought it will come up clumsy and inefficient so I called it heavy.
In the opposite it come up pretty well (beside few things).


## Heavy Features:

### Main Features:
* **Uses separate thread for drawing resulting in higher performance**
* **Separate update and fixed update allows for better physics simulations**
* **Custom renderer makes lights and shadow possible**
* **Delta time and fixed delta time accessible from everywhere**
* **Well abstracted [box2d](https://github.com/erincatto/box2d) made easy to use for everyone**
* **Many profiler macros integrated from [Optick](https://github.com/bombomby/optick)**
* **Lights and shadows easy in use and control**
* **Asynchronous asset load**

### Classes and their use
* **Runtime** - main class, runs the application
* **Asset Manager** - used to store textures etc.
* **Asset Loader** - used to asynchronously load assets
* **Camera** - overall camera controll features functions as shake etc.
* **Colliders** - different colliders for convex shapes featuring drawing
* **Event Dispatcher** - allows you to control events from everywhere
* **Fixed Clock** - featuring start and stop
* **Heavy Math and Utilities** - different math and conversion functions
* **Key Check** - checks user input can work in not repeat mode
* **Particle Emitter** - creating and controlling squared particles
* **Profile Timer** - used to time function
* **Random** - simple random numbers generator
* **Timer** - repeats it's given function every period of time
* **Animator** - handles sprite sheet animations
* 
