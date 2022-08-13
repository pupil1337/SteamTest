// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerSessionsOnCreateSessionComplete, FName, bool)
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerSessionsOnStartSessionComplete, FName, bool)
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerSessionsOnDestroySessionComplete, FName, bool)
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerSessionsOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>&, bool)
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerSessionsOnJoinSessionComplete, FName, EOnJoinSessionCompleteResult::Type)

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionsSubsystem();

	// 外部调用事件
	void CreateSession();
	void StartSession();
	void DestroySession();
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& Result);

	// Session回调函数中所需调用代理
	FMultiplayerSessionsOnCreateSessionComplete MultiplayerSessionsOnCreateSessionComplete;
	FMultiplayerSessionsOnStartSessionComplete MultiplayerSessionsOnStartSessionComplete;
	FMultiplayerSessionsOnDestroySessionComplete MultiplayerSessionsOnDestroySessionComplete;
	FMultiplayerSessionsOnFindSessionsComplete MultiplayerSessionsOnFindSessionsComplete;
	FMultiplayerSessionsOnJoinSessionComplete MultiplayerSessionsOnJoinSessionComplete;

protected:
	// Session事件的回调函数
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) const;
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful) const;
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful) const;
	void OnFindSessionsComplete(bool bWasSuccessful) const;
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type bWasSuccessful) const;
	
private:
	IOnlineSessionPtr OnlineSessionInterface;
	TSharedPtr<FOnlineSessionSettings> OnlineSessionSettings;
	TSharedPtr<FOnlineSessionSearch> OnlineSessionSearch;

	// 需要添加到Session代理列表的代理和其句柄
	FOnCreateSessionCompleteDelegate  CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate   StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	FOnJoinSessionCompleteDelegate    JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
};
