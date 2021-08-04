#include "Filter.h"
#include <chrono>
#include <thread>

Filter::Filter(D2WinDivert::MainWindow^ win, int mode) {
    window = win;
    players = window->playersID;
    int threads = window->threads;
    updint = window->updint;
    const char* filter = "udp.DstPort >= 27000 and udp.DstPort <= 27100";
    // Divert traffic matching the filter:
    running = true;
    debugging = false;
    updating = true;
    handle = WinDivertOpen(filter, WINDIVERT_LAYER_NETWORK, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        log("error: failed to open the WinDivert device", GetLastError());
        exit(EXIT_FAILURE);
    }
    if (mode == 0) {
        for (int i = 0; i < threads; i++) {
            CreateThread(NULL, 0, staticFilterStart, this, 0, NULL);
        }
    }
    else if (mode == 1) {
        for (int i = 0; i < threads; i++) {
            CreateThread(NULL, 0, staticScanStart, this, 0, NULL);
        }
    }
}

DWORD Filter::filterFunction() {
    WINDIVERT_ADDRESS* addr = (WINDIVERT_ADDRESS*)malloc(sizeof(WINDIVERT_ADDRESS));
    char* packet = (char*)malloc(WINDIVERT_MTU_MAX);
    unsigned int packetLen;
    unsigned int addrLen = sizeof(WINDIVERT_ADDRESS);
    if (packet == NULL || addr == NULL) {
        log("error: failed to allocate buffer", GetLastError());
        exit(EXIT_FAILURE);
    }
    window->threadStateChange(1);
    std::chrono::high_resolution_clock::time_point time;
    CreateThread(NULL, 0, staticStatusUpdateStart, this, 0, NULL);
    // Main loop:
    while (running) {
        if (debugging) {
            time = std::chrono::high_resolution_clock::now();
        }
        // Read a matching packet.
        if (!WinDivertRecvEx(handle, packet, WINDIVERT_MTU_MAX, &packetLen, 0, addr, &addrLen, NULL)) {
            if (running) {
                log("warning: failed to read packet", GetLastError());
            }
            continue;
        }

        std::string payload(packet, packetLen);
        allow = 1;
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
            if (!WinDivertSendEx(handle, packet, packetLen, NULL, 0, addr, addrLen, NULL)) {
                log("warning: failed to reinject packet", GetLastError());
            }
        }

        if (debugging) {
            time0 = std::chrono::duration_cast<std::chrono::nanoseconds>
                (std::chrono::high_resolution_clock::now() - time).count();
        }
    }
    updating = false;
    free(packet);
    window->threadStateChange(0);
    return 0;
}

DWORD Filter::scanFunction() {
    WINDIVERT_ADDRESS* addr = (WINDIVERT_ADDRESS*)malloc(sizeof(WINDIVERT_ADDRESS));
    char* packet = (char*)malloc(WINDIVERT_MTU_MAX);
    unsigned int packetLen;
    unsigned int addrLen = sizeof(WINDIVERT_ADDRESS);
    if (packet == NULL || addr == NULL) {
        log("error: failed to allocate buffer", GetLastError());
        exit(EXIT_FAILURE);
    }
    window->threadStateChange(2);
    std::chrono::high_resolution_clock::time_point time;
    CreateThread(NULL, 0, staticIdAppendStart, this, 0, NULL);
    // Main loop:
    while (running) {
        if (debugging) {
            time = std::chrono::high_resolution_clock::now();
        }
        // Read a matching packet.
        if (!WinDivertRecvEx(handle, packet, WINDIVERT_MTU_MAX, &packetLen, 0, addr, &addrLen, NULL)) {
            if (running) {
                log("warning: failed to read packet", GetLastError());
            }
            continue;
        }

        std::string payload(packet, packetLen);
        // Re-inject the matching packet.
        if (!WinDivertSendEx(handle, packet, packetLen, NULL, 0, addr, addrLen, NULL)) {
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
            pendingId.push_back(id);
        }

        if (debugging) {
            time0 = std::chrono::duration_cast<std::chrono::nanoseconds>
                (std::chrono::high_resolution_clock::now() - time).count();
        }
    }
    updating = false;
    free(packet);
    window->threadStateChange(0);
    return 0;
}

DWORD Filter::statusUpdateFunction() {
    while (updating) {
        if (allow == 2) {
            window->changeStatus(0);
        }
        else if (allow == 0) {
            window->changeStatus(1);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(updint));
    }
    window->changeStatus(2);
    return 0;
}

DWORD Filter::idAppendFunction() {
    while (updating) {
        while (pendingId.size() > 0) {
            window->appendTextBox(pendingId.at(pendingId.size() - 1));
            pendingId.pop_back();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(updint));
    }
    return 0;
}

DWORD Filter::debugFunction() {
    while (debugging) {
        dbg->debugTime(0, time0);
    }
    return 0;
}
