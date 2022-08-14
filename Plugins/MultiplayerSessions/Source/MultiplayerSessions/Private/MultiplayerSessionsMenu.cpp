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

void UMultiplayerSessionsMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	TearDownMenu();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
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

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerSessionsOnCreateSessionComplete.AddUObject(this, &ThisClass::OnCreateSessionComplete);
	}
}

void UMultiplayerSessionsMenu::TearDownMenu()
{
	if (const UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			const FInputModeGameOnly InputModeGameOnly;

			PlayerController->SetInputMode(InputModeGameOnly);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

void UMultiplayerSessionsMenu::OnHostButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession();
	}
}

void UMultiplayerSessionsMenu::OnJoinButtonClicked()
{
	
}

void UMultiplayerSessionsMenu::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.0f,
			FColor::Blue,
			FString::Printf(TEXT("Create Success: %hs, SessionName: %s"), bWasSuccessful ? "true" : "false", *SessionName.ToString())
		);
	}

	if (bWasSuccessful)
	{
		if (UWorld* World = GetWorld())
		{
			World->ServerTravel("/MultiplayerSessions/MultiplayerSessionsMap_Lobby?listen");
		}
	}
}
