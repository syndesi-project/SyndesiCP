/**
 * @file syndesicp.h
 * @author Sébastien Deriaz
 * @brief Public header file
 * @version 0.1
 * @date 2022-08-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SYNDESICP_H
#define SYNDESICP_H

#include "callbacks.h"
#include "core.h"
#include "payloads.h"
#include "syndesi_config.h"

#if !defined(SYNDESI_HOST_MODE) && !defined(SYNDESI_DEVICE_MODE)
    #error "MODE unspecified"
#endif


#endif  // SYNDESICP_H