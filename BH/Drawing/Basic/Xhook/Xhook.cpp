#include "Xhook.h"
#include "../../../Common.h"
#include "../../../D2Ptrs.h"

using namespace std;
using namespace Drawing;

/* Basic Hook Initializer
 *		Used for just drawing basic crosses of screen.
 */
Xhook::Xhook(HookVisibility visiblity, unsigned int x, unsigned int y) :
	Hook(visiblity, x, y) {
	//Set the extra variables
	SetColor(0);
}

/* Group Hook Initializer
 *		Used in conjuction with other basic hooks to create an advanced hook.
 */
Xhook::Xhook(HookGroup* group, unsigned int x, unsigned int y) :
	Hook(group, x, y) {
	//Set the extra variables
	SetColor(0);
}

/* GetColor()
 *	Returns the color of the crosshook.
 */
unsigned int Xhook::GetColor() {
	return color;
}

/* SetColor(unsigned int color)
 *	Sets the color of the crosshook.
 */
void Xhook::SetColor(unsigned int newColor) {
	if (newColor < 0 || newColor > 255)
		return;
	Lock();
	color = newColor;
	Unlock();
}

/* Get(X/Y)Size()
 *	Used by click handlers, fuck clicking crosss.
 */
unsigned int Xhook::GetXSize() { return 0; };
unsigned int Xhook::GetYSize() { return 0; };


/* OnDraw()
 *	Draws the cross
 */
void Xhook::OnDraw() {
	if (!IsActive())
		return;

	Lock();
	D2GFX_DrawLine(GetX() - 2, GetY() - 2, GetX() + 2, GetY() + 2, color, -1);
	D2GFX_DrawLine(GetX() - 2, GetY() + 2, GetX() + 2, GetY() - 2, color, -1);
	Unlock();
}

bool Xhook::Draw(unsigned int x, unsigned int y, unsigned int color, unsigned int radius) {
	D2GFX_DrawLine(x - radius, y - radius, x + radius, y + radius, color, -1);
	D2GFX_DrawLine(x - radius, y + radius, x + radius, y - radius, color, -1);
	return true;
}