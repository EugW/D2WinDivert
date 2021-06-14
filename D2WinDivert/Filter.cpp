#include "Filter.h"
#include "windivert.h"
#include <fstream>

Filter::Filter(D2WinDivert::MainWindow^ win, int mode) {
    window = win;
    players = window->playersID;
    const char* filter = "udp.DstPort >= 27000 and udp.DstPort <= 27200";
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

void Filter::closeHandle() {
    running = false;
    if (!WinDivertClose(handle)) {
        log("error: failed to close handle", GetLastError());
    }
}

DWORD WINAPI Filter::staticFilterStart(LPVOID lpParam) {
    return ((Filter*)lpParam)->filterFunction();
}

DWORD WINAPI Filter::staticScanStart(LPVOID lpParam) {
    return ((Filter*)lpParam)->scanFunction();
}

DWORD Filter::filterFunction() {
    WINDIVERT_ADDRESS addr;
    char* packet = (char*)malloc(WINDIVERT_MTU_MAX);
    unsigned int packetLen;

    if (packet == NULL) {
        log("error: failed to allocate buffer", GetLastError());
        exit(EXIT_FAILURE);
    }
    window->threadStateChange(0, 0);
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
        bool allow = true;
        if (payload.find("steamid:7656") != std::string::npos) {
            allow = false;
            for (int x = 0; x < players->size(); x++)
                if (payload.find(players->at(x)) != std::string::npos) {
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
    free(packet);
    window->threadStateChange(0, 1);
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
    window->threadStateChange(1, 0);
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
        }
        auto str = window->getLines();
        if (str.find(id) == std::string::npos) {
            window->appendTextBox(id);
        }
        // Re-inject the matching packet.
        WinDivertHelperCalcChecksums(packet, packetLen, &addr, 0);
        if (!WinDivertSend(handle, packet, packetLen, NULL, &addr)) {
            log("warning: failed to reinject packet", GetLastError());
        }
    }
    free(packet);
    window->threadStateChange(1, 1);
    return 0;
}

void Filter::log(std::string msg, int code) {
    std::ofstream logfl;
    logfl.open("log_divert.txt", std::ofstream::app);
    logfl << msg << " " << code << std::endl;
    logfl.close();
}

void Filter::log(std::string msg) {
    log(msg, -1);
}
