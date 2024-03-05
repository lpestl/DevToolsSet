// Copyright Epic Games, Inc. All Rights Reserved.

#include "DevToolsSetStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
//#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FDevToolsSetStyle::StyleInstance = nullptr;

void FDevToolsSetStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FDevToolsSetStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FDevToolsSetStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DevToolsSetStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

// Note, these sizes are in Slate Units.
// Slate Units do NOT have to map to pixels.
const FVector2D Icon5x16(5.0f, 16.0f);
const FVector2D Icon8x4(8.0f, 4.0f);
const FVector2D Icon8x8(8.0f, 8.0f);
const FVector2D Icon10x10(10.0f, 10.0f);
const FVector2D Icon12x12(12.0f, 12.0f);
const FVector2D Icon12x16(12.0f, 16.0f);
const FVector2D Icon14x14(14.0f, 14.0f);
const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon22x22(22.0f, 22.0f);
const FVector2D Icon24x24(24.0f, 24.0f);
const FVector2D Icon25x25(25.0f, 25.0f);
const FVector2D Icon32x32(32.0f, 32.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon64x64(64.0f, 64.0f);
const FVector2D Icon36x24(36.0f, 24.0f);
const FVector2D Icon128x128(128.0f, 128.0f);

TSharedRef< FSlateStyleSet > FDevToolsSetStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("DevToolsSetStyle"));
#if WITH_EDITOR
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("DevToolsSet")->GetBaseDir() / TEXT("Resources"));
#elif IS_PROGRAM
	Style->SetContentRoot(FPaths::ProjectDir() / TEXT("Plugins") / TEXT("DevToolsSet") / TEXT("Resources"));
#endif

	Style->Set("DevToolsSet.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FDevToolsSetStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FDevToolsSetStyle::Get()
{
	return *StyleInstance;
}
