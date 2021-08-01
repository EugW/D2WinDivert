#include "Filter.h"

Filter::Filter(D2WinDivert::MainWindow^ win, int mode) {
    window = win;
    players = window->playersID;
    const char* filter = "udp.DstPort >= 27000 and udp.DstPort <= 27100";
    // Divert traffic matching the filter:
    running = true;
    handle = WinDivertOpen(filter, WINDIVERT_LAYER_NETWORK, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        log("error: failed to open the WinDivert device", GetLastError());
        exit(EXIT_FAILURE);
    }
    if (mode == 0) {
        for (int i = 0; i < window->getThreads(); i++) {
            CreateThread(NULL, 0, staticFilterStart, this, 0, NULL);
        }
    }
    else if (mode == 1) {
        for (int i = 0; i < window->getThreads(); i++) {
            CreateThread(NULL, 0, staticScanStart, this, 0, NULL);
        }
    }
}

DWORD Filter::filterFunction() {
    WINDIVERT_ADDRESS addr;
    char* packet = (char*)malloc(WINDIVERT_MTU_MAX);
    unsigned int packetLen;

    if (packet == NULL) {
        log("error: failed to allocate buffer", GetLastError());
        exit(EXIT_FAILURE);
    }
    window->threadStateChange(1);
    // Main loop:
    while (running) {
        // Read a matching packet.
        if (!WinDivertRecv(handle, packet, WINDIVERT_MTU_MAX, &packetLen, &addr)) {
            if (running) {
                log("warning: failed to read packet", GetLastError());
            }
            continue;
        }

        std::string payload(packet, packetLen);
        int allow = 1;
        if (payload.find("steamid:7656") != std::string::npos) {
            allow = 0;
            for (int i = 0; i < players->size(); i++) {
                if (payload.find(players->at(i)) != std::string::npos) {
                    allow = 2;
                    break;
                }
            }
        }

        if (allow > 0) {
            // Re-inject the matching packet.
            if (!WinDivertSend(handle, packet, packetLen, NULL, &addr)) {
                log("warning: failed to reinject packet", GetLastError());
            }
        }
        if (allow == 2) {
            window->changeStatus(0);
        }
        else if (allow == 0) {
            window->changeStatus(1);
        }
    }
    free(packet);
    window->threadStateChange(0);
    return 0;
}

DWORD Filter::scanFunction() {
    WINDIVERT_ADDRESS addr;
    char* packet = (char*)malloc(WINDIVERT_MTU_MAX);
    unsigned int packetLen;

    if (packet == NULL) {
        log("error: failed to allocate buffer", GetLastError());
        exit(EXIT_FAILURE);
    }
    window->threadStateChange(2);
    // Main loop:
    while (running) {
        // Read a matching packet.
        if (!WinDivertRecv(handle, packet, WINDIVERT_MTU_MAX, &packetLen, &addr)) {
            if (running) {
                log("warning: failed to read packet", GetLastError());
            }
            continue;
        }

        std::string payload(packet, packetLen);

        // Re-inject the matching packet.
        if (!WinDivertSend(handle, packet, packetLen, NULL, &addr)) {
            log("warning: failed to reinject packet", GetLastError());
        }

        size_t pos;
        std::string id;
        if ((pos = payload.find("steamid:7656")) != std::string::npos) {
            pos++;
            if ((pos = payload.find("steamid:7656", pos)) != std::string::npos) {
                id = payload.substr(pos + 8, 17);
            }
            else if ((pos = payload.find("str:psn-400", pos)) != std::string::npos) {
                id = payload.substr(pos + 11, 16);
            }
            else if ((pos = payload.find("xboxpwid:", pos)) != std::string::npos) {
                id = payload.substr(pos + 9, 32);
            }
            window->appendTextBox(id);
            window->changeStatus(0);
        }
    }
    free(packet);
    window->threadStateChange(0);
    return 0;
}
