#include "Autoplay.h"
#include "AutoplayMotionController.h"

FAutoplayMotionController::FAutoplayMotionController(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
	: MessageHandler(InMessageHandler)
{
	if (!IsRunningDedicatedServer())
	{
		if (FParse::Param(FCommandLine::Get(), TEXT("autoplay")))
		{
			//remove all other motion controllers(make this motion controller first) when autoplay mode
			TArray<IMotionController*> MotionControllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(GetModularFeatureName());
			for (auto MotionController : MotionControllers)
			{
				IModularFeatures::Get().UnregisterModularFeature(GetModularFeatureName(), MotionController);
			}
		}

		IModularFeatures::Get().RegisterModularFeature(GetModularFeatureName(), this);
	}
}

FAutoplayMotionController::~FAutoplayMotionController()
{
	IModularFeatures::Get().UnregisterModularFeature(GetModularFeatureName(), this);
}

void FAutoplayMotionController::Tick(float DeltaTime)
{
	auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

	if (viewport == nullptr || viewport->GetState() != EAutoplayState::Recording)
		return;

	//record vr motion controller state
	TArray<IMotionController*> MotionControllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());
	
	TArray<EControllerHand> hands = { EControllerHand::Left, EControllerHand::Right };
	
	for (auto hand : hands)
	{
		for (auto MotionController : MotionControllers)
		{
			FVector position;
			FRotator orientation;
			ETrackingStatus tracking;

			if ((MotionController != nullptr) && MotionController != this &&
				MotionController->GetControllerOrientationAndPosition(0, hand, orientation, position))
			{
				tracking = MotionController->GetControllerTrackingStatus(0, hand);

				viewport->RecordMotionController(hand, tracking, position, orientation);
				break;
			}
		}
	}
}

void FAutoplayMotionController::SendControllerEvents()
{
	//do nothing
}

void FAutoplayMotionController::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

bool FAutoplayMotionController::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return false;
}

void FAutoplayMotionController::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
}

void FAutoplayMotionController::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values)
{
}

bool FAutoplayMotionController::GetControllerOrientationAndPosition(const int32 ControllerIndex, const EControllerHand DeviceHand, FRotator& OutOrientation, FVector& OutPosition) const
{
	auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

	// in record mode, do nothing
	if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing)
		return false;
	
	// in play mode, return recorded data
	OutPosition = viewport->GetMotionControllerPosition(DeviceHand);
	OutOrientation = viewport->GetMotionControllerOrientation(DeviceHand);
	return true;
}

ETrackingStatus FAutoplayMotionController::GetControllerTrackingStatus(const int32 ControllerIndex, const EControllerHand DeviceHand) const
{
	auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

	// in record mode, do nothing
	if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing)
		return ETrackingStatus::NotTracked;

	// in play mode, return recorded data
	return viewport->GetMotionControllerTrackingStatus(DeviceHand);
}