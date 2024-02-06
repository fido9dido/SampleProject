CryEngine 5.7 LTE

Currently it

*	has a Default Map with a basic Island made with SDK Assets
*	has a Player Component with a Camera
   	*	Use Middle Mouse to Rotate the Camera
	*	WASD to move the player 
	*	LShift + WASD to move the Camera 
	*	Space to Jump - Player Only!
	*	Tab Reset Camera
*	Mixamo Asset (Animation is not set yet)
*	UI
   	*	Button classes are still Work in Progress!
   	*	Assets made using AS3 and button classes Implemented in C++, I am not using flow graph.
   	*	ButtonWithText and ButtonWithImage have inital assets for displaying buttons
   	*	UIComponent is used to test UI code for now
   	*	Make an Empty Entity and add UI component then Add a buttons from there, 
   	*	use ButtonWithImage or ButtonWithText seperately, each in a different component
	
   	
issues:	
*	UI
   	*	Padding doesn't work properly for some reason
   	*	you can overlap ButtonWithText and ButtonWithImage
			in this case ButtonWithText will be drawn on top of ButtonWithImage, make sure they have in a different position
	
