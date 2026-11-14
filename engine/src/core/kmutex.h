/**
 * @file kmutex.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief Provides a platform-specific interface for controlling mutexes (mutual exclusions).
 * Each platform should provide its own implementation of this in a .c file, and 
 * should be compiled exclusively of the rest.
 * @version 1.0
 * @date 2022-07-26
 * 
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
*/

#pragma once

#include "defines.h"

/**
 * @brief A mutex to be used for synchronization purposes. A mutex (or
 * mutual exclusion) is used to limit access to a resource when
 * there are multiple threads of execution around that resource.
*/
typedef struct kmutex
{
    void* internal_data;
} kmutex;

/**
 * @brief Creates a mutex.
 * 
 * @param out_mutex A pointer to hold the created mutex.
 * @returns true if created successfully; otherwise false.
*/
b8 kmutex_create(kmutex* out_mutex);

/**
 * @brief Destroys the provided mutex.
 * 
 * @param mutex A pointer to the mutex to be destroyed.
*/
void kmutex_destroy(kmutex* mutex);

/**
 * @brief Creates a mutex lock.
 * 
 * @param mutex A pointer to the mutex.
 * @returns true if locked successfully; otherwise false.
*/
b8 kmutex_lock(kmutex* mutex);

/**
 * @brief Unlocks the given mutex.
 * 
 * @param mutex The mutex to unlock.
 * @returns true if unlocked successfully; otherwise false.
*/
b8 kmutex_unlock(kmutex* mutex);
