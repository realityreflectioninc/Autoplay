#pragma once

#include "ModuleManager.h"
#include "IInputDeviceModule.h"

#include "Engine.h"
#include "AutoplayManager.h"
#include "AutoplayRecord.h"
#include "AutoplayResult.h"
#include "AutoplayGameViewportClient.h"
#include "AutoplayHMD.h"
#include "AutoplayMotionController.h"

class AutoplayModuleImpl : public IInputDeviceModule
{
public:

	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override
	{
		return TSharedPtr<class IInputDevice>(new FAutoplayMotionController(InMessageHandler));
	}

private:
};