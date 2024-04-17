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

	/**
	 * Initializes the UScreenLayoutManagerSystem state related variables. It does not and shouldn't check for the
	 * validity of the variables; it is just a mediator.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void InitState();

	/** Binded to the FOnScreenLayoutAddedDelegate and called when the screen layout has been added to the screen. */
	UFUNCTION(BlueprintNativeEvent)
	void ScreenLayoutReady();
	virtual void ScreenLayoutReady_Implementation() {}

	UFUNCTION(BlueprintGetter)	UScreenLayout* GetScreenLayout() const {return ScreenLayout;}
	UFUNCTION(BlueprintSetter)	void SetScreenLayout(UScreenLayout* InScreenLayout);
	
	UPROPERTY(BlueprintAssignable)
	FOnScreenLayoutAddedDelegate OnScreenLayoutAdded;

protected:

	/**
	 * Initializes any state related operations, binds the FOnScreenLayoutAddedDelegate and begins the addition of the
	 * screen layout to player screen. The order at which the functions are called are of high importance.
	 */
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintGetter = "GetScreenLayout")
	TObjectPtr<UScreenLayout> ScreenLayout{};
};
