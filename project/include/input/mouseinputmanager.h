/*
 * mouseinputmanager.h
 *
 *  Created on: 31 de jul. de 2016
 *      Author: jorge
 */

#ifndef INPUT_MOUSEINPUTMANAGER_H_
#define INPUT_MOUSEINPUTMANAGER_H_

#include <map>
#include <SDL2/SDL_events.h>

#include "inputdefs.h"
#include "signals/signal.h"

namespace dc
{
	enum EMouseEvent
	{
		MOTION = 0x400,
		BUTTON_DOWN,
		BUTTON_UP,
		WHEEL,
	};
	
	struct TMouseEvent
	{
		EKeyState	buttonState;
		Uint8		buttonID;
		Uint8		clicks;		/**< 1 for single-click, 2 for double-click, etc. */
		int			x;          /**< X coordinate, relative to window */
		int			y;          /**< Y coordinate, relative to window */
		int			xrel;       /**< The relative motion in the X direction */
		int			yrel;       /**< The relative motion in the Y direction */
		int			xwheel;		/**< The amount scrolled horizontally, positive to the right and negative to the left */
		int			ywheel;		/**< The amount scrolled vertically, positive away from the user and negative toward the user */
		
		TMouseEvent() {}
		
		TMouseEvent(int xwheel, int ywheel):
			buttonState(EKeyState::NONE), buttonID(0), clicks(0),
			x(0), y(0), xrel(0), yrel(0), xwheel(xwheel), ywheel(ywheel){}
		
		TMouseEvent(const EKeyState buttonState, int x, int y, int xrel, int yrel):
			buttonState(buttonState), buttonID(0), clicks(0),
			x(x), y(y), xrel(xrel), yrel(yrel), xwheel(0), ywheel(0){}
		
		TMouseEvent(const EKeyState buttonState, const Uint8 buttonID, const Uint8 clicks,
					int x, int y):
			buttonState(buttonState), buttonID(buttonID), clicks(clicks),
			x(x), y(y), xrel(0), yrel(0), xwheel(0), ywheel(0){}
		
		TMouseEvent(const EKeyState buttonState, const Uint8 buttonID, const Uint8 clicks,
					int x, int y, int xrel, int yrel):
			buttonState(buttonState), buttonID(buttonID), clicks(clicks),
			x(x), y(y), xrel(xrel), yrel(yrel), xwheel(0), ywheel(0){}
		
	};
	
	using TMouseSignal = CSignal<void(const TMouseEvent& event)>;
	
	class CMouseInputManager
	{
	// ===========================================================
	// Constant / Static fields / Enums / Typedefs
	// ===========================================================
	private:
		using TMouseEventMap = std::map<const EMouseEvent, TMouseSignal>;

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================
	public:
		const bool HasSignals() const
		{
			return m_eventMap.size();
		}

	// ===========================================================
	// Constructors
	// ===========================================================
	public:
		CMouseInputManager() {}
		virtual ~CMouseInputManager() {}
		
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
	public:
		TMouseSignal& GetSignal(const EMouseEvent event);

	// ===========================================================
	// Methods
	// ===========================================================
	public:
		void CheckEvent(const SDL_Event& event);
		
	private:
		const TMouseEvent Adapt(const SDL_MouseButtonEvent& buttonEvent);
		const TMouseEvent Adapt(const SDL_MouseMotionEvent& motionEvent);
		const TMouseEvent Adapt(const SDL_MouseWheelEvent& wheelEvent);
		
		const EKeyState UpdateKeyState(const Uint8 state, const EKeyState previousState);

	// ===========================================================
	// Fields
	// ===========================================================
	private:
		EKeyState		m_keyState;
		TMouseEventMap	m_eventMap;
	};

} /* namespace dc */

#endif /* INPUT_MOUSEINPUTMANAGER_H_ */
