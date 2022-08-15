# SteamTest
> UE5 Connect to Steam

# What It Is?
- ### [MultiplayerSessions](#MultiplayerSessions) -- Handing online multiplayer session.
- ### [Steam Voice Chat](#SteamVoiceChat)  -- How to use SteamVoice after join Steam Session
# How To Use?
<a name="MultiplayerSessions"></a>
## MultiplayerSessions
####  ① Download MultiplayerSessions.zip
####  ② Copy MultiplayerSessions folder to your project "/Plugins" folder
####  ③ Copy and paste the following into: "/Config/DefaultEngine.ini"
    [/Script/Engine.GameEngine]
    +NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="OnlineSubsystemSteam.SteamNetDriver",DriverClassNameFallback="OnlineSubsystemUtils.IpNetDriver")

    [OnlineSubsystem]
    DefaultPlatformService=Steam

    [OnlineSubsystemSteam]
    bEnabled=true
    ; Your AppId
    SteamDevAppId=480

    ; If using Sessions
    bInitServerOnClient=true

    [/Script/OnlineSubsystemSteam.SteamNetDriver]
    NetConnectionClassName="OnlineSubsystemSteam.SteamNetConnection"
#### ④ Edit /*.uproject and Enable Plugin like the following:
    "Plugins": [
      {
        "Name": "MultiplayerSessions",
        "Enabled": true
      }
    ]
#### ⑤ Generate Project and Open it
#### ⑥ Open "Content/MultiplayerSessions/MultiplayerSessionsMap_Enter", PlayMode "Standalone Game", NetMode "Standalone"
#### ⑦ Make sure that Steam is logged on to this computer
#### ⑧ Play

<a name="SteamVoiceChat"></a>
## Steam Voice Chat
#### ① Do the [MultiplayerSessions](#MultiplayerSessions) steps
#### ② Add the following into "DefaultEngine.ini"
    [Voice]
    bEnabled=true
    
    [OnlineSubsystem]
    bHasVoiceEnabled=true
#### ③ Add the following into "DefaultGame.ini"
    [/Script/Engine.GameSession]
    bRequiresPushToTalk=true
#### ④ Call the following [function](https://docs.unrealengine.com/5.0/en-US/API/Runtime/Engine/GameFramework/APlayerController/ToggleSpeaking/) at the appropriate location:
    UFUNCTION(exec)
	virtual void ToggleSpeaking(bool bInSpeaking);
#### ⑤ Play
    
