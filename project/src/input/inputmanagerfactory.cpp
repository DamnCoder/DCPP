/*
 * inputmanagerfactory.cpp
 *
 *  Created on: 31 de may. de 2016
 *      Author: jorge
 */

#include "input/inputmanagerfactory.h"

namespace dc
{

	CKeyInputManager* CInputManagerFactory::CreateKeyInputManager(EInputType type)
	{
		switch (type)
		{
			case EInputType::SDL:
			{
				return 0;
			}
		}

		return 0;
	}

} /* namespace dc */
