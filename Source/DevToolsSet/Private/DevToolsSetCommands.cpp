// Copyright Epic Games, Inc. All Rights Reserved.

#include "DevToolsSetCommands.h"

#define LOCTEXT_NAMESPACE "FDevToolsSetModule"

void FDevToolsSetCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "DevToolsSet", "Bring up DevToolsSet window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
