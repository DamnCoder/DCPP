/*
 * SkinLoader.h
 *
 *  Created on: 01/06/2011
 *      Author: jorge
 */

#ifndef SKINLOADER_H_
#define SKINLOADER_H_

#include "md3structs.h"
#include "md3model.h"

#include <string>

namespace dc
{

	class CSkinLoader
	{
	public:
		CSkinLoader();
		~CSkinLoader();

		bool importSkin(tModel* pModel, const std::string& path, const std::string& pattern);

	private:

		bool loadSkin(tModel* pModel, tSkin* skin, const std::string& path, const std::string& name);

	};

}

#endif /* SKINLOADER_H_ */
