#include <fstream>
#include <iostream>
#include "windivert.h"
#include "util.h"

using namespace std;

#define MTU 1500

typedef struct {
    HANDLE handle;
    vector<string>* players;
} CONFIG, * PCONFIG;

ofstream logfl;

void log(string msg, int code) {
    logfl.open("log_divert.txt", ofstream::app);
    logfl << msg << " " << code << endl;
    logfl.close();
}

void log(string msg) {
    log(msg, -1);
}

// Passthru thread.
DWORD WINAPI passthru(LPVOID lpParam) {
    PCONFIG config = (PCONFIG)lpParam;
    vector<string>* players = config->players;

    HANDLE handle = config->handle;
    WINDIVERT_ADDRESS addr;
    char* packet = (char*)malloc(WINDIVERT_MTU_MAX);
    unsigned int packetLen;

    if (packet == NULL) {
        log("error: failed to allocate buffer", GetLastError());
        exit(EXIT_FAILURE);
    }

    // Main loop:
    while (true) {
        // Read a matching packet.
        if (!WinDivertRecv(handle, packet, WINDIVERT_MTU_MAX, &packetLen, &addr)) {
            log("warning: failed to read packet", GetLastError());
            continue;
        }

        string payload(packet, packetLen);
        bool allow = true;
        if (payload.find("steamid:7656") != string::npos) {
            allow = false;
            for (int x = 0; x < players->size(); x++)
                if (payload.find(players->at(x)) != string::npos) {
                    allow = true;
                    break;
                }
        }

        if (allow) {
            // Re-inject the matching packet.
            WinDivertHelperCalcChecksums(packet, packetLen, &addr, 0);
            if (!WinDivertSend(handle, packet, packetLen, NULL, &addr)) {
                log("warning: failed to reinject packet", GetLastError());
            }
        }
    }
    return 0;
}

void filter(int threads, vector<string>* players) {
    const char* filter = "udp.DstPort >= 27000 and udp.DstPort <= 27200";
    int i;
    HANDLE handle, thread;
    PCONFIG config = new CONFIG();

    // Divert traffic matching the filter:
    handle = WinDivertOpen(filter, WINDIVERT_LAYER_NETWORK, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        log("error: failed to open the WinDivert device",  GetLastError());
        exit(EXIT_FAILURE);
    }

    // Start the threads
    config->handle = handle;
    config->players = players;
    for (i = 0; i < threads; i++) {
        thread = CreateThread(NULL, 0, passthru, (LPVOID)config, 0, NULL);
        if (thread == NULL) {
            log("error: failed to create thread", GetLastError());
            exit(EXIT_FAILURE);
        }
    }
}

