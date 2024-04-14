// Copyright 2024 Spyridon Zervos


#include "Modules/ModuleManager.h"

class FScreenLayout : public IModuleInterface
{
	
public:

	FScreenLayout();
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

FScreenLayout::FScreenLayout() {}

void FScreenLayout::StartupModule() {}

void FScreenLayout::ShutdownModule() {}

IMPLEMENT_MODULE(FScreenLayout, ScreenLayout)
