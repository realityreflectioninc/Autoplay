#pragma once
#include "IInputDevice.h"
#include "IMotionController.h"

class AutoplayGameViewportClient;

class FAutoplayMotionController : public IInputDevice, public IMotionController
{

public:

	/** Constructor that takes an initial message handler that will receive motion controller events */
	FAutoplayMotionController(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);

	/** Clean everything up */
	virtual ~FAutoplayMotionController();

	// IInputDevice overrides
	virtual void Tick(float DeltaTime) override;
	virtual void SendControllerEvents() override;
	virtual void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;

	// IMotionController overrides
	virtual bool GetControllerOrientationAndPosition(const int32 ControllerIndex, const EControllerHand DeviceHand, FRotator& OutOrientation, FVector& OutPosition) const override;
	virtual ETrackingStatus GetControllerTrackingStatus(const int32 ControllerIndex, const EControllerHand DeviceHand) const override;

private:
	/** The recipient of motion controller input events */
	TSharedPtr<FGenericApplicationMessageHandler> MessageHandler;
};