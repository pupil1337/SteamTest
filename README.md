# SteamTest
UE5 Connect to Stream by OnlineSubsystemSteam

# What It Is?
### MultiplayerSessions -- Handing online multiplayer session.
# How To Use?
## MultiplayerSessions
####  ①Download MultiplayerSessions.zip
####  ②Copy MultiplayerSessions folder to your project "/Plugins" folder
####  ③Copy and paste the following into: "/Config/DefaultEngine.ini"
    [/Script/Engine.GameEngine]
    +NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="OnlineSubsystemSteam.SteamNetDriver",DriverClassNameFallback="OnlineSubsystemUtils.IpNetDriver")

    [OnlineSubsystem]
    DefaultPlatformService=Steam

    [OnlineSubsystemSteam]
    bEnabled=true
    SteamDevAppId=480

    ; If using Sessions
    bInitServerOnClient=true

    [/Script/OnlineSubsystemSteam.SteamNetDriver]
    NetConnectionClassName="OnlineSubsystemSteam.SteamNetConnection"
#### ④Edit /*.uproject and Enable Plugin like the following:
    "Plugins": [
      {
        "Name": "MultiplayerSessions",
        "Enabled": true
      }
    ]
#### ⑤Generate Project and Open it
#### ⑥Open "Content/MultiplayerSessions/MultiplayerSessionsMap_Enter", PlayMode "Standalone Game", NetMode "Standalone"
#### ⑦Make sure that Steam is logged on to this computer
#### ⑧Play
