#pragma once

#include "ModuleManager.h"
#include "IHeadMountedDisplayModule.h"
#include "HeadMountedDisplay.h"
#include "AutoplayGameViewportClient.h"

#include "Engine.h"

class AutoplayHMDModuleImpl : public IHeadMountedDisplayModule
{
public:
	virtual FString GetModuleKeyName() const override;
	virtual bool IsHMDConnected() override;
	virtual int GetGraphicsAdapter() override;
	virtual FString GetAudioInputDevice() override;
	virtual FString GetAudioOutputDevice() override;
	virtual TSharedPtr< class IHeadMountedDisplay, ESPMode::ThreadSafe > CreateHeadMountedDisplay() override;

private:
};

class FAutoplayHMD : public IHeadMountedDisplay
{
public:
	virtual FName GetDeviceName() const override
	{
		static FName DefaultName(TEXT("Autoplay"));
		return DefaultName;
	}
	virtual EHMDWornState::Type GetHMDWornState() 
	{
		auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

		if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing || !viewport->IsVRMode())
			return EHMDWornState::NotWorn;

		return EHMDWornState::Worn; 
	}

	virtual bool IsHMDConnected() override { return true; }
	virtual bool IsHMDEnabled() const override 
	{ 
		return FParse::Param(FCommandLine::Get(), TEXT("autoplay")); 
	}
	virtual void EnableHMD(bool bEnable = true) override {}

	virtual EHMDDeviceType::Type GetHMDDeviceType() const override { return EHMDDeviceType::DT_ES2GenericStereoMesh; }
	virtual bool	GetHMDMonitorInfo(MonitorInfo& MoitorDesc) override { return false; }
	virtual void	GetFieldOfView(float& InOutHFOVInDegrees, float& InOutVFOVInDegrees) const override 
	{
		InOutHFOVInDegrees = 0.0f;
		InOutVFOVInDegrees = 0.0f;
	}

	virtual bool	DoesSupportPositionalTracking() const override
	{
		return true;
	}

	virtual bool	HasValidTrackingPosition() override
	{
		return true;
	}

	virtual void	SetInterpupillaryDistance(float NewInterpupillaryDistance) override {}
	virtual float	GetInterpupillaryDistance() const { return 0.0f; }

	virtual void GetCurrentOrientationAndPosition(FQuat& CurrentOrientation, FVector& CurrentPosition) override
	{
		UE_LOG(LogTemp, Log, TEXT("OrientationPosition"));

		auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

		if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing)
			return;

		CurrentPosition = viewport->GetHMDPosition();
		CurrentOrientation = viewport->GetHMDOrientation().Quaternion();
	}
	
	virtual void RebaseObjectOrientationAndPosition(FVector& Position, FQuat& Orientation) const override
	{
	}

	virtual TSharedPtr<class ISceneViewExtension, ESPMode::ThreadSafe> GetViewExtension() override
	{
		return nullptr;
	}

	virtual void ApplyHmdRotation(class APlayerController* PC, FRotator& ViewRotation) override
	{
		auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

		if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing)
			return;

		ViewRotation = viewport->GetHMDOrientation();
	}

	virtual bool UpdatePlayerCamera(FQuat& CurrentOrientation, FVector& CurrentPosition) override
	{
		auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

		if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing)
			return false;

		CurrentPosition = viewport->GetHMDPosition();
		CurrentOrientation = viewport->GetHMDOrientation().Quaternion();

		return true;
	}

	virtual bool IsChromaAbCorrectionEnabled() const override
	{
		return false;
	}

	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override
	{
		return false;
	}

	virtual bool IsPositionalTrackingEnabled() const override
	{
		auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

		if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing || !viewport->IsVRMode())
			return false;

		return true;
	}

	virtual bool EnablePositionalTracking(bool enable)
	{
		return true;
	}

	virtual bool IsHeadTrackingAllowed() const override
	{
		auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

		if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing || !viewport->IsVRMode())
			return false;

		return true;
	}

	virtual bool IsInLowPersistenceMode() const override
	{
		return false;
	}

	virtual void EnableLowPersistenceMode(bool Enable = true) override
	{
	}

	virtual void ResetOrientationAndPosition(float Yaw = 0.f) override
	{
	}

	virtual bool IsStereoEnabled() const override
	{
		return false;
	}

	virtual bool EnableStereo(bool stereo = true) override
	{
		UE_LOG(LogTemp, Log, TEXT("Stereo"));
		return true;
	}

	virtual void AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override
	{
	}

	virtual void CalculateStereoViewOffset(const enum EStereoscopicPass StereoPassType, const FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation) override
	{
	}

	virtual FMatrix GetStereoProjectionMatrix(const enum EStereoscopicPass StereoPassType, const float FOV) const override
	{
		return FMatrix::Identity;
	}

	virtual void InitCanvasFromView(class FSceneView* InView, class UCanvas* Canvas) override
	{
	}
};