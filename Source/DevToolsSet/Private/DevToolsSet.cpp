// Copyright Epic Games, Inc. All Rights Reserved.

#include "DevToolsSet.h"
#include "DevToolsSetStyle.h"
#include "DevToolsSetCommands.h"
#if WITH_EDITOR
#include "LevelEditor.h"
#endif
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName DevToolsSetTabName("DevToolsSet");

#define LOCTEXT_NAMESPACE "FDevToolsSetModule"

void FDevToolsSetModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDevToolsSetStyle::Initialize();
	FDevToolsSetStyle::ReloadTextures();

	FDevToolsSetCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDevToolsSetCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDevToolsSetModule::PluginButtonClicked),
		FCanExecuteAction());

//#ifdef WITH_EDITOR
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDevToolsSetModule::RegisterMenus));
//#endif
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DevToolsSetTabName, FOnSpawnTab::CreateRaw(this, &FDevToolsSetModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FDevToolsSetTabTitle", "DevToolsSet"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FDevToolsSetModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

//#ifdef WITH_EDITOR
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);
//#endif

	FDevToolsSetStyle::Shutdown();

	FDevToolsSetCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DevToolsSetTabName);
}

TSharedRef<SDockTab> FDevToolsSetModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FDevToolsSetModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("DevToolsSet.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FDevToolsSetModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DevToolsSetTabName);
}

void FDevToolsSetModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDevToolsSetCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDevToolsSetCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDevToolsSetModule, DevToolsSet)