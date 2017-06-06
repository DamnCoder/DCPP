//
//	shadermanager
//	DCPP
//
//	Created by Jorge López González on 10/05/2017 22:53:49.
//

#ifndef CSHADERMANAGER_H
#define CSHADERMANAGER_H

#include "containers/proxy.h"

#include "shader.h"

namespace dc
{
	using TShaderManager = CProxy<CShader*>;
	using TShaderProgramManager = CProxy<CShaderProgram*>;
}
#endif /* CSHADERMANAGER_H */
