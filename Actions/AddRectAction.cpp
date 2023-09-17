#include "AddRectAction.h"


#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include<Windows.h>
#include"MMsystem.h"
AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->isVoiceOn())
		PlaySound(TEXT("rectanglevoice.wav"), NULL, SND_SYNC);
	/// calling the function in the application manager to check if the user wants to allow the voice

	if (pManager->isVoiceOn())
		PlaySound(TEXT("circlevoice.wav"), NULL, SND_SYNC);
	pOut->PrintMessage("New Rectangle: Click at first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	RectGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute(bool readparameters)
{
	//This action needs to read some parameters first
	if (readparameters==true)
	{
		ReadActionParameters();
		R = new CRectangle(P1, P2, RectGfxInfo);
		AddtoUndo();
	}
	//Create a rectangle with the parameters read from the user
	delete R;
	R = new CRectangle(P1, P2, RectGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
}
void AddRectAction::undo()
{
	pManager->RemoveUndone(R);
}
void AddRectAction::AddtoUndo()
{
	pManager->AddUndoAction(this);
}