// Copyright 2024 Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ScreenLayoutManagerSystem.generated.h"

class UScreenLayout;

/**
 * 
 */
UCLASS(Config = ScreenLayout)
class SCREENLAYOUT_API UScreenLayoutManagerSystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	/** Allows this subsystem to be created or not depending on if there are derived classes or not. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetupScreenLayoutForPlayer();
	
	UFUNCTION(BlueprintGetter)
	TSoftClassPtr<UScreenLayout> GetScreenLayoutClass() const {return ScreenLayoutClass;}

private:
	
	UPROPERTY(Config, BlueprintGetter = "GetScreenLayoutClass")
	TSoftClassPtr<UScreenLayout> ScreenLayoutClass;

	virtual void OnScreenLayoutLoaded();
};
