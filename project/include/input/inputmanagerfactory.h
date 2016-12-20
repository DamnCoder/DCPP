/*
 * inputmanagerfactory.h
 *
 *  Created on: 31 de may. de 2016
 *      Author: jorge
 */

#ifndef INPUT_INPUTMANAGERFACTORY_H_
#define INPUT_INPUTMANAGERFACTORY_H_

#include <input/keyinputmanager.h>

namespace dc
{
	enum EInputType
	{
		SDL,
	};

	class CInputManagerFactory
	{
	public:
		static CKeyInputManager* CreateKeyInputManager(EInputType type);
	};

} /* namespace dc */

#endif /* INPUT_INPUTMANAGERFACTORY_H_ */
