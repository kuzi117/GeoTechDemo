// Fill out your copyright notice in the Description page of Project Settings.


#include "SScalabilityOptionsWidget.h"
#include "Internationalization/Internationalization.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SScaleBox.h"

#define LOCTEXT_NAMESPACE "GeoTechDemo"

namespace
{

// Normal button names + auto.
const TArray<FText> SettingButtonNames
{
	LOCTEXT("allLow", "Low"),
	LOCTEXT("allMedium", "Medium"),
	LOCTEXT("allHigh", "High"),
	LOCTEXT("allEpic", "Epic"),
	LOCTEXT("allCinematic", "Cinematic"),
	LOCTEXT("allAuto", "Auto")
};

// View distance button unique names.
const TArray<FText> ViewDistanceButtonNames
{
	LOCTEXT("viewDistanceNear", "Near"),
	LOCTEXT("viewDistanceMedium", "Medium"),
	LOCTEXT("viewDistanceFar", "Far"),
	LOCTEXT("viewDistanceEpic", "Epic"),
	LOCTEXT("viewDistanceCinematic", "Cinematic")
};

// Option descriptions.
const TArray<FText> OptionDescriptions
{
	LOCTEXT("optViewDistance", "View Distance"),
	LOCTEXT("optAntiAliasing", "Anti-Aliasing (TSR)"),
	LOCTEXT("optPostProcessing", "Post Processing"),
	LOCTEXT("optShadows", "Shadows"),
	LOCTEXT("optGlobalIllumination", "Global Illumination"),
	LOCTEXT("optReflections", "Reflections"),
	LOCTEXT("optTextures", "Textures"),
	LOCTEXT("optEffects", "Effects"),
	LOCTEXT("optFoliages", "Foliages"),
	LOCTEXT("optShading", "Shading")
};

} // End anonymous namespace.

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SScalabilityOptionsWidget::Construct(const FArguments& InArgs)
{
	TSharedPtr<SGridPanel> ButtonGrid;

	// Fill in overall layout.
	ChildSlot
	[
		SNew(SScaleBox)
			.Stretch(EStretch::ScaleToFit)
		[
			// Title bar.
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
				.AutoHeight()
			[
				SNew(STextBlock)
					.Text(LOCTEXT("scalabilityGroups", "Scalability Groups"))
					.Justification(ETextJustify::Left)
			]
			// Options groups.
			+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					SAssignNew(ButtonGrid, SGridPanel)
				]
			]
			// Check box.
			+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(20.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SCheckBox)
					.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
				[
					SNew(STextBlock)
						.Text(LOCTEXT("monitorEditorPerf", "Monitor Editor Performance?"))
				]
			]
		]
	];

	// Adding update all settings button names.
	// An unfortunate hack here to match the layout of the Segmented Control, which lays out its internal
	// buttons in a horizontal box. To match it, the first five buttons go in a multi-column-spanning
	// box to mimic the control, then the final Auto button gets its own cell. Actually makes it convenient
	// to handle the on clicked callbacks though.
	{
		// The box for the first set of buttons.
		TSharedPtr<SHorizontalBox> Box;
		ButtonGrid->AddSlot(1, 0)
			.ColumnSpan(SettingButtonNames.Num() - 1)
			.Padding(0.0f, 0.0f, 0.0f, 5.0f)
		[
			SAssignNew(Box, SHorizontalBox)
		];

		// Add the set all buttons.
		for (int i = 0; i < SettingButtonNames.Num() - 1; ++i)
		{
			TSharedPtr<SButton> Button;
			Box->AddSlot()
			[
				SNew(SButton)
					.OnClicked(FOnClicked::CreateLambda([this, i]() {
						for (TSharedPtr<SSegmentedControl<uint32>> Control : Controls)
						{
							Control->SetValue(i);
						}
						return FReply::Handled();
					}))
				[
					SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text(SettingButtonNames[i])
						.Clipping(EWidgetClipping::Inherit)
				]
			];
		}
		
		// The grid slot for the final button.
		ButtonGrid->AddSlot(SettingButtonNames.Num(), 0)
		[
			SNew(SBox)
				.Padding(0.0f, 0.0f, 0.0f, 5.0f)
			[
				SNew(SButton)
					.OnClicked(FOnClicked::CreateLambda([this]() {
						for (TSharedPtr<SSegmentedControl<uint32>> Control : Controls)
						{
							Control->SetValue(-1);
						}
						return FReply::Handled();
					}))
				[
					SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text(*SettingButtonNames.rbegin())
						.Clipping(EWidgetClipping::Inherit)
				]
			]
		];
	}

	// Add view distance button special names.
	{
		// SegmentedControl for view distance.
		TSharedPtr<SSegmentedControl<uint32>> Control;
		ButtonGrid->AddSlot(1, 1)
			.ColumnSpan(ViewDistanceButtonNames.Num())
		[
			SAssignNew(Control, SSegmentedControl<uint32>)
		];

		// Add control buttons with text.
		for (int32 i = 0; i < ViewDistanceButtonNames.Num(); ++i)
		{
			Control->AddSlot(i)
			[
				SNew(STextBlock)
					.Justification(ETextJustify::Center)
					.Text(ViewDistanceButtonNames[i])
			];
		}

		// Cache the control.
		Controls.Emplace(MoveTemp(Control));
	}

	// Adding normal button names, skipping view distance.
	for (int i = 0; i < OptionDescriptions.Num() - 1; ++i)
	{
		// Segmented control for each of the remaining settings rows.
		TSharedPtr<SSegmentedControl<uint32>> Control;
		ButtonGrid->AddSlot(1, i + 2)
			.ColumnSpan(SettingButtonNames.Num() - 1)
		[
			SAssignNew(Control, SSegmentedControl<uint32>)
		];

		// Add control buttons with text.
		for (int j = 0; j < SettingButtonNames.Num() - 1; ++j)
		{
			Control->AddSlot(j)
			[
				SNew(STextBlock)
					.Justification(ETextJustify::Center)
					.Text(SettingButtonNames[j])
			];
		}

		// Cache the control.
		Controls.Emplace(MoveTemp(Control));
	}

	// Add descriptions.
	for (int i = 0; i < OptionDescriptions.Num(); ++i)
	{
		ButtonGrid->AddSlot(0, i + 1)
		[
			// Box for a little right padding between text and buttons.
			SNew(SBox)
				.Padding(0.0f, 0.0f, 10.0f, 0.0f)
			[
				SNew(STextBlock)
					.Text(OptionDescriptions[i])
					.Justification(ETextJustify::Left)
			]
		];
	}

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
