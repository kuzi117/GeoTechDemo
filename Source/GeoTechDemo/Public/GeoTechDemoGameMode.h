// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GeoTechDemoGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGeoTechDemo, Log, All);

class SScalabilityOptionsWidget;

UCLASS()
class GEOTECHDEMO_API AGeoTechDemoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	/** Console command to show options UI. */
	UFUNCTION(Exec)
	static void ShowOptionsUI();

private:
	/** The cached options widget. */
	static TSharedPtr<SScalabilityOptionsWidget> OptionsWidget;

	/** Is the widget showing right now. */
	static bool bIsShowingWidget;
};
