#include "Filter.h"
#include <chrono>

typedef struct {
    Filter* fltr;
    WINDIVERT_ADDRESS addr;
    char* packet;
    unsigned int packetLen;
} Data;

Filter::Filter(D2WinDivert::MainWindow^ _window, int _mode) {
    window = _window;
    mode = _mode;
    players = window->playersID;
    const char* filter = "udp.DstPort >= 27000 and udp.DstPort <= 27100";
    running = true;
    handle = WinDivertOpen(filter, WINDIVERT_LAYER_NETWORK, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        log("error: failed to open the WinDivert device", GetLastError());
        exit(EXIT_FAILURE);
    }
    CreateThread(NULL, 0, staticCoreStart, this, 0, NULL);
}

DWORD WINAPI Filter::staticCoreStart(LPVOID lpParam) {
    return ((Filter*)lpParam)->coreFunction();
}

DWORD WINAPI Filter::staticFilterStart(LPVOID lpParam) {
    Data* data = (Data*)lpParam;
    DWORD th = data->fltr->filterFunction(data->addr, data->packet, data->packetLen);
    free(lpParam);
    return th;
}

DWORD WINAPI Filter::staticScanStart(LPVOID lpParam) {
    Data* data = (Data*)lpParam;
    DWORD th = data->fltr->scanFunction(data->addr, data->packet, data->packetLen);
    free(lpParam);
    return th;
};

DWORD Filter::coreFunction() {
    if (mode == 0) {
        window->threadStateChange(1);
    }
    else {
        window->threadStateChange(2);
    }
    while (running) {
        Data* data = new Data();
        data->fltr = this;
        data->packet = (char*)malloc(WINDIVERT_MTU_MAX);
        if (data->packet == NULL) {
            log("error: failed to allocate buffer", GetLastError());
            exit(EXIT_FAILURE);
        }
        if (!WinDivertRecv(handle, data->packet, WINDIVERT_MTU_MAX, &(data->packetLen), &(data->addr))) {
            if (running) {
                log("warning: failed to read packet", GetLastError());
            }
            continue;
        }
        if (mode == 0) {
            CreateThread(NULL, 0, staticFilterStart, data, 0, NULL);
        }
        else {
            CreateThread(NULL, 0, staticScanStart, data, 0, NULL);
        }
    }
    window->threadStateChange(0);
    return 0;
}

DWORD Filter::filterFunction(WINDIVERT_ADDRESS addr, char* packet, unsigned int packetLen) {
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
        WinDivertHelperCalcChecksums(packet, packetLen, &addr, 0);
        if (!WinDivertSend(handle, packet, packetLen, NULL, &addr)) {
            log("warning: failed to reinject packet", GetLastError());
        }
    }
    if (allow == 2) {
        window->changeStatus(0);
    }
    else {
        window->changeStatus(1);
    }
    free(packet);
    return 0;
}

DWORD Filter::scanFunction(WINDIVERT_ADDRESS addr, char* packet, unsigned int packetLen) {
    std::string payload(packet, packetLen);
    WinDivertHelperCalcChecksums(packet, packetLen, &addr, 0);
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
    free(packet);
    return 0;
}