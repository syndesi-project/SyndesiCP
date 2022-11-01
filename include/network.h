/**
 * @file network.h
 *
 * @brief Interfacing with the communication protocols (IP, UART, RS 485, ...)
 *
 * @author Sébastien Deriaz
 * @date 15.08.2022
 */

#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <stdint.h>

#include "frame.h"
#include "framemanager.h"
#include "interfaces.h"
#include "sdid.h"

using namespace std;

namespace syndesi {
class Network : SAP::INetwork_top, public SAP::INetwork_bottom {
    /**
     * @brief Network frame instance
     * @note contains a network header and a payload. The payload is forwarded
     * to the FrameManager
     */
    friend class Core;
    friend class IPController;
    friend class SAP::IController;

    static const unsigned short syndesi_port = 2608;

   private:
    // List of pendingConfirm IDs
    // std::list<SyndesiID*> pendingConfirm;

    unsigned short _port = syndesi_port;

    /**
     * @brief Look in the pendingConfirm list and determine wether or not the
     * received ID is for a confirm
     *
     * @param id
     * @return true
     * @return false
     */
    bool inPendingConfirm(SyndesiID& id);

    void setCustomPort(unsigned short port);

    /*
     * Upper layer
     */
    SAP::IFrameManager_bottom* _frameManager;
    void registerFrameManager(SAP::IFrameManager_bottom* frameManager) {
        _frameManager = frameManager;
    };
    // <-frameManager
    void request(Frame& frame);
    // <-frameManager
    void response(Frame& frame);

    /*
     * Lower layers
     */
    void controllerDataAvailable (SAP::IController* controller);

    void registerIPController(SAP::IController* controller) {
        IPController = controller;
    }

    /**
     * @brief Read a frame from the given controller
     * 
     * @param controller 
     */
    Frame readFrame(SyndesiID& id, SAP::IController* controller);

   public:
    SAP::IController* IPController = nullptr;
    // SAP::IController_top* UARTController;
    // SAP::IController_top* RS485Controller;

    void setDefaultPort();
    unsigned short port();

    void init();
};

}  // namespace syndesi

#endif  // NETWORK_INTERFACE_H
