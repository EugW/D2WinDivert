#include <fstream>
#include <iostream>
#include "windivert.h"
#include "util.h"

using namespace std;

#define MTU 1500

typedef struct {
    HANDLE handle;
    int batch;
    vector<string>* players;
} CONFIG, * PCONFIG;

// Passthru thread.
DWORD WINAPI passthru(LPVOID lpParam) {
    UINT8* packet;
    UINT packet_len, recv_len, addr_len;
    WINDIVERT_ADDRESS* addr;
    PCONFIG config = (PCONFIG)lpParam;
    HANDLE handle = config->handle;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    vector<string>* players = config->players;
    int batch = config->batch;
    packet_len = batch * MTU;
    packet_len = (packet_len < WINDIVERT_MTU_MAX ? WINDIVERT_MTU_MAX : packet_len);
    packet = (UINT8*)malloc(packet_len);
    addr = (WINDIVERT_ADDRESS*)malloc(batch * sizeof(WINDIVERT_ADDRESS));
    if (packet == NULL || addr == NULL) {
        exit(EXIT_FAILURE);
    }
    // Main loop:
    while (true) {
        // Read a matching packet.
        addr_len = batch * sizeof(WINDIVERT_ADDRESS);
        WinDivertRecvEx(handle, packet, packet_len, &recv_len, 0, addr, &addr_len, NULL);

        string payload((char*)packet, recv_len);
        bool allow = true;
        if (payload.find("steamid:7656") != string::npos) {
            allow = false;
            for (int x = 0; x < players->size(); x++) {
                if (payload.find(players->at(x)) != string::npos) {
                    allow = true;
                    break;
                }
            }
        }

        if (allow) {
            // Re-inject the matching packet.
            WinDivertSendEx(handle, packet, recv_len, NULL, 0, addr, addr_len, NULL);
        }
    }
    return 0;
}

void filter(int threads, int batch, int priority, vector<string>* players) {
    const char* filter = "udp.DstPort >= 27000 and udp.DstPort <= 27200";
    int i;
    HANDLE handle, thread;
    PCONFIG config = new CONFIG();

    // Divert traffic matching the filter:
    handle = WinDivertOpen(filter, WINDIVERT_LAYER_NETWORK, (INT16)priority, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        exit(EXIT_FAILURE);
    }

    // Start the threads
    config->handle = handle;
    config->batch = batch;
    config->players = players;
    for (i = 0; i < threads; i++) {
        thread = CreateThread(NULL, 0, passthru, (LPVOID)config, 0, NULL);
        if (thread == NULL) {
            exit(EXIT_FAILURE);
        }
    }
}

