/**
 * @file kthread.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief Provides a platform-specific interface for controlling threads.
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
 * @brief Represents a process thread in the system to be used for work.
 * Generally should not be created directly in user code.
 * This calls to the platform-specific thread implementation.
*/
typedef struct kthread
{
    void* internal_data;
    u64 thread_id;
} kthread;

// A function pointer to be invoked when the thread starts.
typedef u32 (*pfn_thread_start)(void*);

/**
 * @brief Creates a new thread, immediately calling the function pointed to.
 * @param start_function_ptr The pointer to the function to be invoked immediately. Required.
 * @param params A pointer to any data to be passed to the start_function_ptr. Optional. Pass 0/NULL if not used.
 * @param auto_detach Indicates if the thread should immediately release its resources when the work is complete. If true, out_thread is not set.
 * @param out_thread A pointer to hold the created thread, if auto_detach is false.
 * @returns true if successfully created; otherwise false.
*/
b8 kthread_create(pfn_thread_start start_function_ptr, void* params, b8 auto_detach, kthread* out_thread);

/**
 * @brief Destroys the given thread.
 * 
 * @param thread A pointer to the thread to destroy.
*/
void kthread_destroy(kthread* thread);

/**
 * @brief Detaches the thread, automatically releasing resources when work is complete.
 * 
 * @param thread A pointer to the thread to detach.
*/
void kthread_detach(kthread* thread);

/**
 * @brief Cancels work on the thread, if possible, and releases resources when possible.
 * 
 * @param thread A pointer to the thread to cancel.
*/
void kthread_cancel(kthread* thread);

/**
 * @brief Indicates if the thread is currently active.
 * 
 * @param thread A pointer to the thread to check.
 * @returns true if active; otherwise false.
*/
b8 kthread_is_active(kthread* thread);

/**
 * @brief Sleeps on the given thread for a given number of milliseconds. Should be called from the
 * thread requiring the sleep.
 * 
 * @param thread A pointer to the thread to sleep.
 * @param ms The number of milliseconds the thread should sleep for.
*/
void kthread_sleep(kthread* thread, u64 ms);

/**
 * @brief Gets the id of thread that is currently running.
 * 
 * @returns The id of the thread that is currently running.
*/
u64 get_thread_id();
