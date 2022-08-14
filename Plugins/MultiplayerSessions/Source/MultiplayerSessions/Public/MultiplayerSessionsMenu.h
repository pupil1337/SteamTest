// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerSessionsMenu.generated.h"

class UButton;
class UMultiplayerSessionsSubsystem;

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Host;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Join;

public:
	virtual bool Initialize() override;

protected:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	void BindButton();
	void SetUpMenu();
	void TearDownMenu();

	UFUNCTION()
	void OnHostButtonClicked();
	UFUNCTION()
	void OnJoinButtonClicked();

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	UPROPERTY()
	UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
};
