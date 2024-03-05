// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DevToolsSetStyle.h"

class FDevToolsSetCommands : public TCommands<FDevToolsSetCommands>
{
public:

	FDevToolsSetCommands()
		: TCommands<FDevToolsSetCommands>(TEXT("DevToolsSet"), NSLOCTEXT("Contexts", "DevToolsSet", "DevToolsSet Plugin"), NAME_None, FDevToolsSetStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};