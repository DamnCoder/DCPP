//
//  rendersubsystem.cpp
//  DCPPTest
//
//  Created by Jorge López on 1/4/17.
//
//

#include "rendersubsystem.h"

namespace dc
{
	void CRenderSubsystem::Initialize()
	{
		mp_renderer = CRenderer::New();
		mp_renderer->Initialize();
	}
	
	void CRenderSubsystem::Run()
	{
		mp_renderer->Prepare();
		mp_renderer->Render();
	}
	
	void CRenderSubsystem::Terminate()
	{
		mp_renderer->Terminate();
		CRenderer::Destroy();
	}
}
