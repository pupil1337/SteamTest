// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
	:
	// 创建Session代理
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	StartSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete)),
	DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete))
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.0f,
				FColor::Blue,
				FString::Printf(TEXT("OnlineSubsystem is: %s"), *OnlineSubsystem->GetSubsystemName().ToString())
			);
		}
	}
}

/* --public-- ========================================================================*/

void UMultiplayerSessionsSubsystem::CreateSession()
{
	if (OnlineSessionInterface)
	{
		// 销毁已经创建的Session
		if (OnlineSessionInterface->GetNamedSession(NAME_GameSession))
		{
			OnlineSessionInterface->DestroySession(NAME_GameSession, DestroySessionCompleteDelegate);
		}

		// 添加到代理列表
		CreateSessionCompleteDelegateHandle = OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

		// SessionSettings和创建Session
		OnlineSessionSettings = MakeShareable(new FOnlineSessionSettings);
		OnlineSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
		OnlineSessionSettings->NumPublicConnections = 4;
		OnlineSessionSettings->bAllowJoinInProgress = true;
		OnlineSessionSettings->bAllowJoinViaPresence = true;
		OnlineSessionSettings->bUsesPresence = true;
		OnlineSessionSettings->bShouldAdvertise = true;
		OnlineSessionSettings->bUseLobbiesIfAvailable = true;
		OnlineSessionSettings->Set(FName("MatchType"), FString("PupilTest"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		if (!OnlineSessionInterface->CreateSession(*GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId(), NAME_GameSession, *OnlineSessionSettings))
		{
			OnlineSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

			MultiplayerSessionsOnCreateSessionComplete.Broadcast(NAME_GameSession, false);
		}
	}
}

void UMultiplayerSessionsSubsystem::StartSession()
{
}

void UMultiplayerSessionsSubsystem::DestroySession()
{
}

void UMultiplayerSessionsSubsystem::FindSessions(int32 MaxSearchResults)
{
}

void UMultiplayerSessionsSubsystem::JoinSession(const FOnlineSessionSearchResult& Result)
{
}

/* --protected-- ========================================================================*/

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSessionInterface)
	{
		OnlineSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}
	
	MultiplayerSessionsOnCreateSessionComplete.Broadcast(SessionName, bWasSuccessful);
}

void UMultiplayerSessionsSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful) const
{
	MultiplayerSessionsOnStartSessionComplete.Broadcast(SessionName, bWasSuccessful);
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful) const
{
	MultiplayerSessionsOnDestroySessionComplete.Broadcast(SessionName, bWasSuccessful);
}

void UMultiplayerSessionsSubsystem::OnFindSessionsComplete(bool bWasSuccessful) const
{
	MultiplayerSessionsOnFindSessionsComplete.Broadcast(OnlineSessionSearch.IsValid() ? OnlineSessionSearch->SearchResults : TArray<FOnlineSessionSearchResult>(), bWasSuccessful);
}

void UMultiplayerSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type bWasSuccessful) const
{
	MultiplayerSessionsOnJoinSessionComplete.Broadcast(SessionName, bWasSuccessful);
}
