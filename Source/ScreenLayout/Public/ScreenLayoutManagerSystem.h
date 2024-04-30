// Copyright 2024 Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ScreenLayoutManagerSystem.generated.h"

class UCommonActivatableWidget;
class UScreenLayout;

/**
 * The heart of the screen layout plugin. Manages the proper function of the screen layout. It also provides a means of
 * setting states which refer to game concepts such as game menu, game HUD etc. These states have to have a correlation
 * with a gameplay tag. Based on that, it has the ability to display the proper first (primary) widget that should be
 * shown in said state.
 */
UCLASS(Config = ScreenLayout)
class SCREENLAYOUT_API UScreenLayoutManagerSystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	/** Allows this subsystem to be created or not depending on if there are derived classes. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Tries to async load the screen layout widget and then calls OnScreenLayoutLoaded(). */
	UFUNCTION(BlueprintCallable, Category = "Screen")
	virtual void SetupScreenLayoutForPlayer();
	
	UFUNCTION(BlueprintGetter, Category = "Screen")
	TSoftClassPtr<UScreenLayout> GetScreenLayoutClass() const {return ScreenLayoutClass;}

protected:

	/** Called when the screen layout has finally loaded. It then proceeds to set it up for the pc. */
	virtual void OnScreenLayoutLoaded();

	/**
	 * The screen layout class that will be added to the player controller. The default provided contains three
	 * UCommonActivatableWidgetStacks 
	 */
	UPROPERTY(
		Config,
		BlueprintGetter = "GetScreenLayoutClass",
		Category = "Screen"
		)
	TSoftClassPtr<UScreenLayout> ScreenLayoutClass;
};
