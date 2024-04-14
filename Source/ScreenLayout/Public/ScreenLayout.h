// Copyright 2024 Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "ScreenLayout.generated.h"

/**
 * 
 */
UCLASS()
class SCREENLAYOUT_API UScreenLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushWidgetToLayer(UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayer(FGameplayTag LayerTag, UClass* ActivatableWidgetClass, TFunctionRef<void(ActivatableWidgetT&)> InitInstanceFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		if (LayerTag.IsValid())
		{
			if (UCommonActivatableWidgetContainerBase* Layer = Layers.FindRef(LayerTag))
			{
				return Layer->AddWidget<ActivatableWidgetT>(ActivatableWidgetClass, InitInstanceFunc);
			}
		}

		return nullptr;
	}


protected:

	/** Registers a widget to the layer denote by the gameplay tag. */
	UFUNCTION(BlueprintCallable, Category="Layer")
	void RegisterLayer(UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget);
	
private:

	/** Maps the gameplay tags with the layers they represent. */
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> Layers;
};
