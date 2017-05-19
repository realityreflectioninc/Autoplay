#include "AutoplayHMD.h"

FString AutoplayHMDModuleImpl::GetModuleKeyName() const
{
	return FString(TEXT("Autoplay"));
}

bool AutoplayHMDModuleImpl::IsHMDConnected()
{
	if (!IsRunningDedicatedServer() && FParse::Param(FCommandLine::Get(), TEXT("autoplay")))
		return true;

	return false;
}

int AutoplayHMDModuleImpl::GetGraphicsAdapter()
{
	return -1;
}

FString AutoplayHMDModuleImpl::GetAudioInputDevice()
{
	return "";
}

FString AutoplayHMDModuleImpl::GetAudioOutputDevice()
{
	return "";
}

TSharedPtr<class IHeadMountedDisplay, ESPMode::ThreadSafe> AutoplayHMDModuleImpl::CreateHeadMountedDisplay()
{
	TSharedPtr< FAutoplayHMD, ESPMode::ThreadSafe > autoplayHMD(new FAutoplayHMD());

	return autoplayHMD;
}


IMPLEMENT_MODULE(AutoplayHMDModuleImpl, AutoplayHMD);