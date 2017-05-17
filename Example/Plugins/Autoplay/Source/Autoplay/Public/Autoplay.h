#pragma once

#include "ModuleManager.h"

#include "Engine.h"
#include "AutoplayManager.h"
#include "AutoplayRecord.h"
#include "AutoplayResult.h"
#include "AutoplayGameViewportClient.h"

class AutoplayModuleImpl : public IModuleInterface
{
public:
	void StartupModule();
	void ShutdownModule();

private:
};