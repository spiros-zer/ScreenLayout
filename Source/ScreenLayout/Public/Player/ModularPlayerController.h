// Copyright 2024 Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/ScreenLayoutManagerController.h"
#include "ModularPlayerController.generated.h"

class UCommonActivatableWidget;
class UScreenLayout;

/** Fired when the screen layout has been added to the screen and passed to the controller. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScreenLayoutAddedDelegate);

/**
 * 
 */
UCLASS()
class SCREENLAYOUT_API AModularPlayerController : public APlayerController, public IScreenLayoutManagerController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintGetter)	UScreenLayout* GetScreenLayout() const {return ScreenLayout;}
	UFUNCTION(BlueprintSetter)	void SetScreenLayout(UScreenLayout* InScreenLayout);
	
	UPROPERTY(BlueprintAssignable)
	FOnScreenLayoutAddedDelegate OnScreenLayoutAdded;

	UFUNCTION(BlueprintNativeEvent)
	void ScreenLayoutReady();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintGetter = "GetScreenLayout")
	TObjectPtr<UScreenLayout> ScreenLayout{};
};
