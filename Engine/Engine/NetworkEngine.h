#pragma once

#ifndef NETWORK_ENGINE_H
#define NETWORK_ENGINE_H

#include "SceneManager.h"

enum class NetworkState {
    INITIALIZE_NETWORK,
    WAITING_FOR_CONNECTION,
    RUNNING,
    DISABLED,
    NETWORK_ERROR,
};

class NetworkEngine {
public:
    bool IsClient() { return isClient; }
    bool IsServer() { return isServer; }
    void SendPacket(RakNet::BitStream& bs);

private:
    int port;
    bool isServer;
    bool isClient;
    std::string ipAddress;
    NetworkState state;

    RakNet::RakPeerInterface* rakInterface;
    std::vector<RakNet::RakNetGUID> connections;

    friend class Engine;

    void Initialize(bool _isServer);
    void InitializeNetwork();
    void LoadSettings();
    void PreUpdate();
    void ReceivePackets();
    void PostUpdate();
};

#endif