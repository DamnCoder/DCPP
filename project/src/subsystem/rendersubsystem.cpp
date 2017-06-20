//
//  rendersubsystem.cpp
//  DCPPTest
//
//  Created by Jorge López on 1/4/17.
//
//

#include "rendersubsystem.h"

#include "app.h"

namespace dc
{
	void CRenderSubsystem::Initialize()
	{
		mp_renderer = CRenderer::New();
		mp_renderer->Initialize();
		
		mp_windowSubsystem = CApp::Instance().GetSubsystem<CWindowSubsystem>();
	}
	
	void CRenderSubsystem::PrepareUpdate()
	{
		mp_renderer->Prepare();
	}
	
	void CRenderSubsystem::Run()
	{
		mp_renderer->Render();
	}
	
	void CRenderSubsystem::FinishUpdate()
	{
		mp_renderer->Finish();
		mp_windowSubsystem->Window()->SwapBuffers();
	}
	
	void CRenderSubsystem::Terminate()
	{
		mp_renderer->Terminate();
		CRenderer::Destroy();
	}
}
