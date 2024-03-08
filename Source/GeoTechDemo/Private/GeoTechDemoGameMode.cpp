// Fill out your copyright notice in the Description page of Project Settings.


#include "GeoTechDemoGameMode.h"
#include "SScalabilityOptionsWidget.h"

DEFINE_LOG_CATEGORY(LogGeoTechDemo)

TSharedPtr<SScalabilityOptionsWidget> AGeoTechDemoGameMode::OptionsWidget = nullptr;
bool AGeoTechDemoGameMode::bIsShowingWidget = false;

void AGeoTechDemoGameMode::ShowOptionsUI()
{
	// Check GEngine not null.
	if (GEngine == nullptr)
	{
		UE_LOG(LogGeoTechDemo, Error, TEXT("Can't show scalability options: GEngine null"));
		return;
	}

	// Check Viewport not null.
	TObjectPtr<UGameViewportClient> Viewport = GEngine->GameViewport;
	if (Viewport == nullptr)
	{
		UE_LOG(LogGeoTechDemo, Error, TEXT("Can't show scalability options: Viewport null"));
		return;
	}

	// Build widget if it doesn't exist.
	if (OptionsWidget == nullptr)
	{
		OptionsWidget = SNew(SScalabilityOptionsWidget);
	}

	// Already showing - remove from Viewport.
	if (bIsShowingWidget)
	{
		Viewport->RemoveViewportWidgetContent(OptionsWidget.ToSharedRef());
		bIsShowingWidget = false;
	}
	// Not yet showing - add to Viewport.
	else
	{
		Viewport->AddViewportWidgetContent(OptionsWidget.ToSharedRef());
		bIsShowingWidget = true;
	}

	return;
}
