#include "Diamondhook.h"
#include "../../../Common.h"
#include "../../../D2Ptrs.h"

using namespace std;
using namespace Drawing;

/* Basic Hook Initializer
 *		Used for just drawing basic crosses of screen.
 */
Diamondhook::Diamondhook(HookVisibility visiblity, unsigned int x, unsigned int y) :
	Hook(visiblity, x, y) {
	//Set the extra variables
	SetColor(0);
}

/* Group Hook Initializer
 *		Used in conjuction with other basic hooks to create an advanced hook.
 */
Diamondhook::Diamondhook(HookGroup* group, unsigned int x, unsigned int y) :
	Hook(group, x, y) {
	//Set the extra variables
	SetColor(0);
}

/* GetColor()
 *	Returns the color of the crosshook.
 */
unsigned int Diamondhook::GetColor() {
	return color;
}

/* SetColor(unsigned int color)
 *	Sets the color of the crosshook.
 */
void Diamondhook::SetColor(unsigned int newColor) {
	if (newColor < 0 || newColor > 255)
		return;
	Lock();
	color = newColor;
	Unlock();
}

/* Get(X/Y)Size()
 *	Used by click handlers, fuck clicking crosss.
 */
unsigned int Diamondhook::GetXSize() { return 0; };
unsigned int Diamondhook::GetYSize() { return 0; };


/* OnDraw()
 *	Draws the cross
 */
void Diamondhook::OnDraw() {
	if (!IsActive())
		return;

	Lock();
	CHAR szLines[][2] = { 0,-3, 3,0, 0,3, -3,0, 0,-3 };
	for (unsigned int x = 0; x < 4; x++)
		D2GFX_DrawLine(GetX() + szLines[x][0], GetY() + szLines[x][1], GetX() + szLines[x + 1][0], GetY() + szLines[x + 1][1], GetColor(), -1);
	Unlock();
}

bool Diamondhook::Draw(unsigned int x, unsigned int y, unsigned int color, unsigned int radius) {
	CHAR szLines[][2] = { 0,-radius, radius,0, 0,radius, -radius,0, 0,-radius };
	for (unsigned int n = 0; n < 4; n++)
		D2GFX_DrawLine(x + szLines[n][0], y + szLines[n][1], x + szLines[n + 1][0], y + szLines[n + 1][1], color, -1);
	return true;
}