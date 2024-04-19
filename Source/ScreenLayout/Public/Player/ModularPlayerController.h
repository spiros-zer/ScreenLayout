// Copyright 2024 Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "ModularPlayerController.generated.h"

class UCommonActivatableWidget;
class UScreenLayout;

/** Fired when the screen layout has been added to the screen and passed to the controller. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScreenLayoutAddedDelegate);

/**
 * 
 */
UCLASS()
class SCREENLAYOUT_API AModularPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual bool PushWidgetToLayer(UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag InLayerTag,
						   TSubclassOf<UCommonActivatableWidget> InActivatableWidgetClass);

	/** Binded to the FOnScreenLayoutAddedDelegate and called when the screen layout has been added to the screen. */
	UFUNCTION(BlueprintNativeEvent)
	void ScreenLayoutReady();
	virtual void ScreenLayoutReady_Implementation() {}

	UFUNCTION(BlueprintGetter)	UScreenLayout* GetScreenLayout() const {return ScreenLayout;}
	UFUNCTION(BlueprintSetter)	void SetScreenLayout(UScreenLayout* InScreenLayout);

	UFUNCTION(BlueprintSetter, Category = "Screen|State")
	void SetStateTag(const FGameplayTag InStateTag) {StateTag = InStateTag;}
	
	UFUNCTION(BlueprintGetter, Category = "Screen|State")
	FGameplayTag GetStateTag() const {return StateTag;}
	
	UFUNCTION(BlueprintSetter, Category = "Screen|State")
	void SetPrimaryWidgetClassForState(const TSubclassOf<UCommonActivatableWidget> InPrimaryWidget)
	{
		PrimaryWidgetClassForState = InPrimaryWidget;
	}

	UFUNCTION(BlueprintGetter, Category = "Screen|State")
	TSubclassOf<UCommonActivatableWidget> GetPrimaryWidgetClassForState() const {return PrimaryWidgetClassForState;}
	
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

	/** The current state at which the player has the screen layout. This could be game menu, game HUD etc. */
    	UPROPERTY(
    		EditDefaultsOnly,
    		BlueprintGetter = "GetStateTag",
    		BlueprintSetter = "SetStateTag",
    		Category = "Screen|State",
    		meta = (Categories = "UI.Layer")
    		)
    	FGameplayTag StateTag{};
    
    	/** The first widget that will be shown in for this state. */
    	UPROPERTY(
    		EditDefaultsOnly,
    		BlueprintGetter = "GetPrimaryWidgetClassForState",
    		BlueprintSetter = "SetPrimaryWidgetClassForState",
    		Category = "Screen|State"
    		)
    	TSubclassOf<UCommonActivatableWidget> PrimaryWidgetClassForState;
};
