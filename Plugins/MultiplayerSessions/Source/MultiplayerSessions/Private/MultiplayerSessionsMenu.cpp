// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsMenu.h"

#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

bool UMultiplayerSessionsMenu::Initialize()
{
	if (Super::Initialize())
	{
		BindButton();
		SetUpMenu();
		return true;
	}

	return false;
}

void UMultiplayerSessionsMenu::BindButton()
{
	if (Button_Host)
	{
		Button_Host->OnClicked.AddUniqueDynamic(this, &ThisClass::OnHostButtonClicked);
	}

	if (Button_Join)
	{
		Button_Join->OnClicked.AddUniqueDynamic(this, &ThisClass::OnJoinButtonClicked);
	}
}

void UMultiplayerSessionsMenu::SetUpMenu()
{
	// 设置Widget
	AddToViewport();
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	bIsFocusable = true;

	if (const UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeUIOnly InputModeUIOnly;
			InputModeUIOnly.SetWidgetToFocus(TakeWidget());
			InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			PlayerController->SetInputMode(InputModeUIOnly);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	// 初始化变量
	if (const UGameInstance* GameInstance = GetGameInstance())
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

void UMultiplayerSessionsMenu::OnHostButtonClicked()
{
	
}

void UMultiplayerSessionsMenu::OnJoinButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession();

		if (UWorld* World = GetWorld())
		{
			//World->ServerTravel()
		}
	}	
}
