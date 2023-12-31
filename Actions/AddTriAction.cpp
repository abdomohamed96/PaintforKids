#include "AddTriAction.h"


#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include<Windows.h>
#include"MMsystem.h"
AddTriAction::AddTriAction(ApplicationManager * pApp):Action(pApp)
{}

void AddTriAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	/// calling the function in the application manager to check if the user wants to allow the voice
	
	if (pManager->isVoiceOn())
		PlaySound(TEXT("trianglevoice.wav"), NULL, SND_SYNC);
	pOut->PrintMessage("New Triangle: Click at first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Triangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	pOut->PrintMessage("New Triangle: Click at third corner");

	//Read 3nd corner and store in point P2
	pIn->GetPointClicked(P3.x, P3.y);

	TriGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	TriGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddTriAction::Execute(bool readparameters)
{
	//This action needs to read some parameters first
	if (readparameters)
	{
		ReadActionParameters();
		T = new CTriangle(P1, P2, P3, TriGfxInfo);
		AddtoUndo();
	}
	
	//Create a rectangle with the parameters read from the user
	delete T;
	T = new CTriangle(P1, P2, P3, TriGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(T);

}
void AddTriAction::undo()
{
	pManager->RemoveUndone(T);
}
void AddTriAction::AddtoUndo()
{
	pManager->AddUndoAction(this);
}