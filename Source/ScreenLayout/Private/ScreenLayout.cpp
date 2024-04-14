// Copyright 2024 Spyridon Zervos


#include "ScreenLayout.h"

UCommonActivatableWidget* UScreenLayout::PushWidgetToLayer(FGameplayTag LayerTag,
                                                           TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (UCommonActivatableWidgetContainerBase* Layer = Layers.FindRef(LayerTag))
	{
		return Layer->AddWidget<UCommonActivatableWidget>(ActivatableWidgetClass, [](UCommonActivatableWidget&) {});
	}

	return nullptr;
}

void UScreenLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	Layers.Add(LayerTag, LayerWidget);
}
