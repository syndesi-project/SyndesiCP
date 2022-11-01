/**
 * @file core.h
 *
 * @brief Syndesi core
 *
 * @author Sébastien Deriaz
 * @date 09.08.2022
 */

#ifndef CORE_H
#define CORE_H

#include "frame.h"
#include "callbacks.h"
#include "framemanager.h"
#include "network.h"

namespace syndesi {

class Core {
   private:

    void factory_init();

    /*
    * Layers
    */
   Callbacks callbacks;
   FrameManager frameManager;
   
   public:

    Network network;

    void sendRequest(Payload& payload, SyndesiID& id);

    void init();

    Core() {factory_init();};
    ~Core(){};
};

}  // namespace syndesi

#endif  // CORE_H