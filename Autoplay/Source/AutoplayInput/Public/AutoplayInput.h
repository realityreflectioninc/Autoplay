#pragma once

#include "ModuleManager.h"
#include "IInputDeviceModule.h"

#include "Engine.h"
#include "AutoplayGameViewportClient.h"
#include "AutoplayMotionController.h"

class AutoplayInputModuleImpl : public IInputDeviceModule
{
public:

	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override
	{
		return TSharedPtr<class IInputDevice>(new FAutoplayMotionController(InMessageHandler));
	}

private:
};