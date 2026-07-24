#include <jni.h>
#include <pthread.h>
#include <android/log.h>
#include <atomic>
#include <string>
#include <thread>
#include <chrono>

#define LOG_TAG "EclipseMod"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static std::atomic<bool> g_initialized{false};
static std::atomic<bool> g_menuVisible{false};
static std::atomic<bool> g_authorized{false};

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("JNI_OnLoad called");
    // Start a background thread to initialize hooking and pattern scanning
    std::thread([](){
        LOGI("Init thread started");
        // Minimal delay to allow the process to stabilize
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // TODO: wait for libil2cpp.so / GameAssembly to load, run pattern scanner, install hooks
        // For now, mark initialized so UI can interact with JNI toggles
        g_initialized.store(true);
        LOGI("EclipseMod: initialized (scaffold only)");
    }).detach();

    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT void JNICALL
Java_com_pixellabs_pixelstrike3d_EclipseBridge_toggleMenu(JNIEnv* env, jclass clazz) {
    bool visible = g_menuVisible.load();
    g_menuVisible.store(!visible);
    LOGI("toggleMenu: %d", !visible);
}

extern "C" JNIEXPORT void JNICALL
Java_com_pixellabs_pixelstrike3d_EclipseBridge_setAuthorized(JNIEnv* env, jclass clazz, jboolean val) {
    g_authorized.store(val);
    LOGI("setAuthorized: %d", val);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_pixellabs_pixelstrike3d_EclipseBridge_isInitialized(JNIEnv* env, jclass clazz) {
    return (jboolean)g_initialized.load();
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_pixellabs_pixelstrike3d_EclipseBridge_isMenuVisible(JNIEnv* env, jclass clazz) {
    return (jboolean)g_menuVisible.load();
}
