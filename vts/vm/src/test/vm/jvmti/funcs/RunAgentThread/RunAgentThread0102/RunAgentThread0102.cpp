/*
    Copyright 2005-2006 The Apache Software Foundation or its licensors, as applicable

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

    See the License for the specific language governing permissions and
    limitations under the License.
*/
/**
 * @author Valentin Al. Sitnick
 * @version $Revision: 1.1 $
 *
 */

/* *********************************************************************** */

#define SHORT_TIME 5000
#define LONG_TIME 50000

/* *********************************************************************** */

#include "events.h"
#include "utils.h"
#include "fake.h"

static bool test_0 = false;
static bool flag = false;

void JNICALL function(jvmtiEnv* jvmti_env, JNIEnv* jni_env, void* arg);

/* *********************************************************************** */

/**
 * test of function RunAgentThread
 */
void RunAgentThread0102()
{
    //Fake method for docletting only
}

/* *********************************************************************** */

JNIEXPORT jint JNICALL Agent_OnLoad(prms_AGENT_ONLOAD)
{
    check_AGENT_ONLOAD;

    Callbacks CB;

    cb_exc;
    cb_death;

    AGENT_FOR_EVENTS_TESTS_PART_I; /* events.h */

    jvmtiEvent events[] = { JVMTI_EVENT_EXCEPTION, JVMTI_EVENT_VM_DEATH };

    AGENT_FOR_EVENTS_TESTS_PART_II;

    fprintf(stderr, "\n-------------------------------------------------\n");
    fprintf(stderr, "\ntest RunAgentThread0102 is started\n{\n");
    fflush(stderr);

    return JNI_OK;
}

/* *********************************************************************** */

void JNICALL callbackException(prms_EXCPT)
{
    check_EXCPT;

    if (flag) return;

    char* name;
    char* signature;
    char* generic;
    jvmtiPhase phase;
    jvmtiError result;
    long ethalon = JVMTI_THREAD_STATE_IN_NATIVE | JVMTI_THREAD_STATE_ALIVE | JVMTI_THREAD_STATE_RUNNABLE;
    jvmtiStartFunction proc = function;
    jthread mythread = NULL;

    result = jvmti_env->GetPhase(&phase);

    fprintf(stderr, "\tnative: GetPhase result = %d (must be zero) \n", result);
    fprintf(stderr, "\tnative: current phase is %d (must be 4 (LIVE-phase)) \n", phase);

    if ((result != JVMTI_ERROR_NONE) || (phase != JVMTI_PHASE_LIVE)) return;

    result = jvmti_env->GetMethodName(method, &name, &signature, &generic);
    fprintf(stderr, "\tnative: GetMethodName result = %d (must be zero) \n", result);
    fprintf(stderr, "\tnative: method name is %s \n", name);
    fprintf(stderr, "\tnative: signature name is %s \n", signature);
    fprintf(stderr, "\tnative: generic name is %s \n", generic);
    fflush(stderr);

    if (result != JVMTI_ERROR_NONE) return;

    if (strcmp(name, "special_method")) return;

    flag = true;

    fprintf(stderr, "\tnative: JNI: funcs start\n");

    jclass clazz = jni_env->FindClass("java/lang/Thread");

    if (clazz)
        fprintf(stderr, "\tnative: JNI: FindClass - Ok\n");
    else return;

    jmethodID mid = jni_env->GetMethodID(clazz, "<init>", "()V");

    if (mid)
        fprintf(stderr, "\tnative: JNI: GetMethodID - Ok\n");
    else return;

    jthread thread_1 = jni_env->NewObject(clazz, mid, "native_agent_thread");

    if (thread_1)
        fprintf(stderr, "\tnative: JNI: NewObject - Ok\n");
    else return;

    result = jvmti_env->RunAgentThread(thread_1, proc, NULL, 555);

    fprintf(stderr, "\tnative: RunAgentThread result = %d (must be JVMTI_ERROR_INVALID_PRIORITY (12)) \n", result);

    if (result != JVMTI_ERROR_INVALID_PRIORITY) return;

    test_0 = true;
}

void JNICALL callbackVMDeath(prms_VMDEATH)
{
    check_VMDEATH;

    fprintf(stderr, "\n\tTest of function RunAgentThread0102              : ");

    if (test_0)
        fprintf(stderr, " passed \n");
    else
        fprintf(stderr, " failed \n");

    fprintf(stderr, "\n} /* test RunAgentThread0102 is finished */ \n");
    fflush(stderr);
}

/* *********************************************************************** */

void JNICALL function(jvmtiEnv* jvmti_env, JNIEnv* jni_env, void* arg)
{
    fprintf(stderr, "\tnative: Native thread is STARTED\n");

    if (jni_env == NULL)
        fprintf(stderr, "\tnative: func was called with jni_env = NULL\n");
    if (jvmti_env == NULL)
        fprintf(stderr, "\tnative: func was called with jvmti_env = NULL\n");
    if (arg == NULL)
        fprintf(stderr, "\tnative: func was called with arg = NULL\n");

#ifndef LINUX
    Sleep(SHORT_TIME);
#else
    usleep(SHORT_TIME * 1000);
#endif
    return;
}

/* *********************************************************************** */


