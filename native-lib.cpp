#include <jni.h>
#include <algorithm>

// Prototype stereo-width stage, using interleaved float samples: L, R, L, R...
// This is not yet an HRTF renderer or a complete surround processor.
extern "C" JNIEXPORT jfloatArray JNICALL
Java_com_example_immersiveaudio_MainActivity_nativeProcessStereo(
        JNIEnv* env, jobject /* thiz */, jfloatArray inputArray, jfloat width) {
    if (inputArray == nullptr) return nullptr;
    const jsize length = env->GetArrayLength(inputArray);
    if (length % 2 != 0) return nullptr;

    jfloat* input = env->GetFloatArrayElements(inputArray, nullptr);
    if (input == nullptr) return nullptr;
    jfloatArray outputArray = env->NewFloatArray(length);
    if (outputArray == nullptr) {
        env->ReleaseFloatArrayElements(inputArray, input, JNI_ABORT);
        return nullptr;
    }

    const float w = std::clamp(static_cast<float>(width), 0.0f, 1.5f);
    for (jsize i = 0; i < length; i += 2) {
        const float left = input[i];
        const float right = input[i + 1];
        const float mid = 0.5f * (left + right);
        const float side = 0.5f * (left - right);
        input[i] = std::clamp(mid + w * side, -1.0f, 1.0f);
        input[i + 1] = std::clamp(mid - w * side, -1.0f, 1.0f);
    }
    env->SetFloatArrayRegion(outputArray, 0, length, input);
    env->ReleaseFloatArrayElements(inputArray, input, JNI_ABORT);
    return outputArray;
}
