/**
 * @file syndesi.cpp
 *
 * @brief Syndesi device library
 *
 * @ingroup syndesi
 *
 * @author Sébastien Deriaz
 * @date 09.06.2022
 */

#include "core.h"

namespace syndesi {

void Core::factory_init() {
    // register interfaces (connect layers together)
    // Callbacks class
    callbacks.registerFrameManager(&frameManager);
    // FrameManager class
    frameManager.registerCallbacks(&callbacks);
    frameManager.registerNetwork(&network);
    // Network class
    network.registerFrameManager(&frameManager);
    // IP Controller class (if used)
}

void Core::sendRequest(Payload& payload, SyndesiID& id) {
    // This version is easier but requires a copy of the SyndesiID argument
    Frame frame(payload, id, true);
    frameManager.request(frame);
}

void Core::init() {
    network.init();
}

}  // namespace syndesi