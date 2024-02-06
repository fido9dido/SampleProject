// Fill out your copyright notice here.
#ifndef IBUTTON_H
#define IBUTTON_H

//////////////////////////////////////////////////////////
// Represents an interface for a button 
////////////////////////////////////////////////////////
class IButton
{

	virtual void SetButtonPosition(f32 posX, f32 posY) = 0;
	virtual void SetButtonWidthAndHeight(int32 width, int32 height) = 0;
	virtual void SetButtonWidth(int32 width) = 0;
	virtual void SetButtonHeight(int32 height) = 0;
	virtual void SetVisible(bool value) = 0;
};

#endif