// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Input/SSegmentedControl.h"
#include "Widgets/SCompoundWidget.h"


/**
 * A widget to show scalability option groups and their settings.
 */
class GEOTECHDEMO_API SScalabilityOptionsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SScalabilityOptionsWidget)
	{}
	SLATE_END_ARGS()

	/** Construct widget with scalability option groups. */
	void Construct(const FArguments& InArgs);

private:
	/** The cached list of controls to enable set-all functionality. EE*/
	TArray<TSharedPtr<SSegmentedControl<uint32> >> Controls;
};
