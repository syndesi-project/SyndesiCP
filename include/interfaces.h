/**
 * @file interfaces.h
 *
 * @brief Interfaces between layers.
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#ifndef INTERFACES_H
#define INTERFACES_H

#include "buffer.h"
#include "frame.h"
//#include "protocols_config.h"
#include "syndesi_config.h"

namespace syndesi {

class Network;
namespace SAP {

class IFrameManager_top {
   public:
    // From top layer
    virtual void response(Frame& payload) = 0;
};

class IFrameManager_bottom {
   public:
    // From bottom layer
    virtual void indication(Frame& frame) = 0;
    virtual void confirm(Frame& frame) = 0;
};

class INetwork_top {
   public:
    // From top layer
    virtual void request(Frame& frame) = 0;
    virtual void response(Frame& frame) = 0;
};

class IController;

class INetwork_bottom {
   public:
    virtual unsigned short port() = 0;
    virtual void setCustomPort(unsigned short port) = 0;
    virtual void registerIPController(IController* controller) = 0;
    virtual void controllerDataAvailable(IController* controller) = 0;
};

class IController {
    friend class syndesi::Network;
    IController(const IController&) = delete;
    IController(const IController&&) = delete;

   private:
    INetwork_bottom* network;

   public:
    IController(INetwork_bottom* _network) {
        network = _network;
        network->registerIPController(this);
    }

    /*
     * Callable by the user
     */ 
   public:
    void dataAvailable() { network->controllerDataAvailable(this);}

   protected:
    unsigned short IPPort() { return network->port(); };
    void setCustomIPPort(unsigned short port) { network->setCustomPort(port); };

    /*
     * Implemented by the user
     */
   protected:
    virtual void init() = 0;
    virtual SyndesiID& getSyndesiID() = 0;
    virtual size_t read(char* buffer, size_t length) = 0;
    virtual void write(SyndesiID& deviceID, char* buffer, size_t length) = 0;
    virtual void close() = 0;
};

}  // namespace SAP
}  // namespace syndesi

#endif  // INTERFACES_H
