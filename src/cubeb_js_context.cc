#include "cubeb_js.h"

Napi::FunctionReference CubebJs::constructor;

Napi::Object CubebJs::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Cubeb", {
        InstanceMethod("getBackendId", &CubebJs::GetBackendId),
        InstanceMethod("getMaxChannelCount", &CubebJs::GetMaxChannelCount),
        InstanceMethod("getMinLatency", &CubebJs::GetMinLatency),
        InstanceMethod("getPreferredSampleRate", &CubebJs::GetPreferredSampleRate),
        InstanceMethod("destroy", &CubebJs::Destroy),
        // InstanceMethod("streamInit", &CubebJs::StreamInit),
        // InstanceMethod("streamDestroy", &CubebJs::StreamDestroy),
        // InstanceMethod("streamStart", &CubebJs::StreamStart),
        // InstanceMethod("", ),

        // Export cubeb_sample_format values
        StaticValue("CUBEB_SAMPLE_S16LE", Napi::Number::New(env, CUBEB_SAMPLE_S16LE), napi_static),
        StaticValue("CUBEB_SAMPLE_S16BE", Napi::Number::New(env, CUBEB_SAMPLE_S16BE), napi_static),
        StaticValue("CUBEB_SAMPLE_S16NE", Napi::Number::New(env, CUBEB_SAMPLE_S16NE), napi_static),
        StaticValue("CUBEB_SAMPLE_FLOAT32LE", Napi::Number::New(env, CUBEB_SAMPLE_FLOAT32LE), napi_static),
        StaticValue("CUBEB_SAMPLE_FLOAT32BE", Napi::Number::New(env, CUBEB_SAMPLE_FLOAT32BE), napi_static),
        StaticValue("CUBEB_SAMPLE_FLOAT32NE", Napi::Number::New(env, CUBEB_SAMPLE_FLOAT32NE), napi_static),

        // Export cubeb_channel_layout values
        StaticValue("CUBEB_LAYOUT_UNDEFINED", Napi::Number::New(env, CUBEB_LAYOUT_UNDEFINED), napi_static),
        StaticValue("CUBEB_LAYOUT_MONO", Napi::Number::New(env, CUBEB_LAYOUT_MONO), napi_static),
        StaticValue("CUBEB_LAYOUT_MONO_LFE", Napi::Number::New(env, CUBEB_LAYOUT_MONO_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_STEREO", Napi::Number::New(env, CUBEB_LAYOUT_STEREO), napi_static),
        StaticValue("CUBEB_LAYOUT_STEREO_LFE", Napi::Number::New(env, CUBEB_LAYOUT_STEREO_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_3F", Napi::Number::New(env, CUBEB_LAYOUT_3F), napi_static),
        StaticValue("CUBEB_LAYOUT_3F_LFE", Napi::Number::New(env, CUBEB_LAYOUT_3F_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_2F1", Napi::Number::New(env, CUBEB_LAYOUT_2F1), napi_static),
        StaticValue("CUBEB_LAYOUT_2F1_LFE", Napi::Number::New(env, CUBEB_LAYOUT_2F1_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_3F1", Napi::Number::New(env, CUBEB_LAYOUT_3F1), napi_static),
        StaticValue("CUBEB_LAYOUT_3F1_LFE", Napi::Number::New(env, CUBEB_LAYOUT_3F1_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_2F2", Napi::Number::New(env, CUBEB_LAYOUT_2F2), napi_static),
        StaticValue("CUBEB_LAYOUT_2F2_LFE", Napi::Number::New(env, CUBEB_LAYOUT_2F2_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_QUAD", Napi::Number::New(env, CUBEB_LAYOUT_QUAD), napi_static),
        StaticValue("CUBEB_LAYOUT_QUAD_LFE", Napi::Number::New(env, CUBEB_LAYOUT_QUAD_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_3F2", Napi::Number::New(env, CUBEB_LAYOUT_3F2), napi_static),
        StaticValue("CUBEB_LAYOUT_3F2_LFE", Napi::Number::New(env, CUBEB_LAYOUT_3F2_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_3F2_BACK", Napi::Number::New(env, CUBEB_LAYOUT_3F2_BACK), napi_static),
        StaticValue("CUBEB_LAYOUT_3F2_LFE_BACK", Napi::Number::New(env, CUBEB_LAYOUT_3F2_LFE_BACK), napi_static),
        StaticValue("CUBEB_LAYOUT_3F3R_LFE", Napi::Number::New(env, CUBEB_LAYOUT_3F3R_LFE), napi_static),
        StaticValue("CUBEB_LAYOUT_3F4_LFE", Napi::Number::New(env, CUBEB_LAYOUT_3F4_LFE), napi_static),

        // Export chbeb_stream_prefs values
        StaticValue("CUBEB_STREAM_PREF_NONE", Napi::Number::New(env, CUBEB_STREAM_PREF_NONE), napi_static),
        StaticValue("CUBEB_STREAM_PREF_LOOPBACK", Napi::Number::New(env, CUBEB_STREAM_PREF_LOOPBACK), napi_static),

        // Export cubeb_state values
        StaticValue("CUBEB_STATE_STARTED", Napi::Number::New(env, CUBEB_STATE_STARTED), napi_static),
        StaticValue("CUBEB_STATE_STOPPED", Napi::Number::New(env, CUBEB_STATE_STOPPED), napi_static),
        StaticValue("CUBEB_STATE_DRAINED", Napi::Number::New(env, CUBEB_STATE_DRAINED), napi_static),
        StaticValue("CUBEB_STATE_ERROR", Napi::Number::New(env, CUBEB_STATE_ERROR), napi_static),

        // Export cubeb_device_type values
        StaticValue("CUBEB_DEVICE_TYPE_UNKNOWN", Napi::Number::New(env, CUBEB_DEVICE_TYPE_UNKNOWN), napi_static),
        StaticValue("CUBEB_DEVICE_TYPE_INPUT", Napi::Number::New(env, CUBEB_DEVICE_TYPE_INPUT), napi_static),
        StaticValue("CUBEB_DEVICE_TYPE_OUTPUT", Napi::Number::New(env, CUBEB_DEVICE_TYPE_OUTPUT), napi_static),

        // Export cubeb_device_state values
        StaticValue("CUBEB_DEVICE_STATE_DISABLED", Napi::Number::New(env, CUBEB_DEVICE_STATE_DISABLED), napi_static),
        StaticValue("CUBEB_DEVICE_STATE_UNPLUGGED", Napi::Number::New(env, CUBEB_DEVICE_STATE_UNPLUGGED), napi_static),
        StaticValue("CUBEB_DEVICE_STATE_ENABLED", Napi::Number::New(env, CUBEB_DEVICE_STATE_ENABLED), napi_static),

        // Export cubeb_device_fmt values
        StaticValue("CUBEB_DEVICE_FMT_S16LE", Napi::Number::New(env, CUBEB_DEVICE_FMT_S16LE), napi_static),
        StaticValue("CUBEB_DEVICE_FMT_S16BE", Napi::Number::New(env, CUBEB_DEVICE_FMT_S16BE), napi_static),
        StaticValue("CUBEB_DEVICE_FMT_F32LE", Napi::Number::New(env, CUBEB_DEVICE_FMT_F32LE), napi_static),
        StaticValue("CUBEB_DEVICE_FMT_F32BE", Napi::Number::New(env, CUBEB_DEVICE_FMT_F32BE), napi_static),
        StaticValue("CUBEB_DEVICE_FMT_S16NE", Napi::Number::New(env, CUBEB_DEVICE_FMT_S16NE), napi_static),
        StaticValue("CUBEB_DEVICE_FMT_F32NE", Napi::Number::New(env, CUBEB_DEVICE_FMT_F32NE), napi_static),
        StaticValue("CUBEB_DEVICE_FMT_S16_MASK", Napi::Number::New(env, CUBEB_DEVICE_FMT_S16_MASK), napi_static),
        StaticValue("CUBEB_DEVICE_FMT_F32_MASK", Napi::Number::New(env, CUBEB_DEVICE_FMT_F32_MASK), napi_static),
        StaticValue("CUBEB_DEVICE_FMT_ALL", Napi::Number::New(env, CUBEB_DEVICE_FMT_ALL), napi_static),

        // Export cubeb_device_pref values
        StaticValue("CUBEB_DEVICE_PREF_NONE", Napi::Number::New(env, CUBEB_DEVICE_PREF_NONE), napi_static),
        StaticValue("CUBEB_DEVICE_PREF_MULTIMEDIA", Napi::Number::New(env, CUBEB_DEVICE_PREF_MULTIMEDIA), napi_static),
        StaticValue("CUBEB_DEVICE_PREF_VOICE", Napi::Number::New(env, CUBEB_DEVICE_PREF_VOICE), napi_static),
        StaticValue("CUBEB_DEVICE_PREF_NOTIFICATION", Napi::Number::New(env, CUBEB_DEVICE_PREF_NOTIFICATION), napi_static),
        StaticValue("CUBEB_DEVICE_PREF_ALL", Napi::Number::New(env, CUBEB_DEVICE_PREF_ALL), napi_static)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    // TODO: Figure out how to use finalizeCallback in classes to destroy the Cubeb context when garbage collecting.

    exports.Set("Cubeb", func);

    return exports;
}

CubebJs::CubebJs(const Napi::CallbackInfo& info) : Napi::ObjectWrap<CubebJs>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    int argc = info.Length();
    char const * context_name;
    char const * backend_name = "";

    if (argc < 1 || argc > 2) {
        Napi::TypeError::New(env, "Wrong amount of arguments").ThrowAsJavaScriptException();
        return;
    }

    if (info[0].IsString()) {
        std::string name = info[0].As<Napi::String>().Utf8Value();
        context_name = name.c_str();
    } else {
        Napi::TypeError::New(env, "Context name must be a string").ThrowAsJavaScriptException();
        return;
    }

    if (argc == 2) {
        if (info[1].IsString()) {
            std::string name = info[1].As<Napi::String>().Utf8Value();
            backend_name = name.c_str();
        } else {
            Napi::TypeError::New(env, "Backend name must be a string").ThrowAsJavaScriptException();
            return;
        }
    }

    this->internal_context = NULL;
    int status = cubeb_init(&this->internal_context, context_name, backend_name);

    if (status == CUBEB_ERROR) {
        Napi::TypeError::New(env, "Failed to initialize Cubeb context").ThrowAsJavaScriptException();
    }
}

Napi::Value CubebJs::GetBackendId(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int argc = info.Length();

    if (argc != 0) {
        Napi::TypeError::New(env, "Wrong amount of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    const char * backend_name = cubeb_get_backend_id(this->internal_context);

    return Napi::String::New(env, backend_name);
}

Napi::Value CubebJs::GetMaxChannelCount(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int argc = info.Length();

    if (argc != 0) {
        Napi::TypeError::New(env, "Wrong amount of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    uint32_t max_channels;
    int status = cubeb_get_max_channel_count(this->internal_context, &max_channels);

    if (status == CUBEB_OK) {
        return Napi::Number::New(env, max_channels);
    } else {
        // TODO: Throw status errors
        return env.Null();
    }
}

Napi::Value CubebJs::GetMinLatency(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int argc = info.Length();

    if (argc > 1) {
        Napi::TypeError::New(env, "Wrong amount of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    cubeb_stream_params * params = NULL;
    JsObjectToCubebParams(info[0], params);

    uint32_t latency_frames = 0;
    int status = cubeb_get_min_latency(this->internal_context, params, &latency_frames);

    if (status == CUBEB_OK) {
        return Napi::Number::New(env, latency_frames);
    } else {
        Napi::TypeError::New(env, "Failed to get minimum latency").ThrowAsJavaScriptException();
        // TODO: Throw status errors
        return env.Null();
    }
}

Napi::Value CubebJs::GetPreferredSampleRate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int argc = info.Length();

    if (argc > 0) {
        Napi::TypeError::New(env, "Wrong amount of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    uint32_t sample_rate = 0;

    int status = cubeb_get_preferred_sample_rate(this->internal_context, &sample_rate);

    if (status == CUBEB_OK) {
        return Napi::Number::New(env, sample_rate);
    } else {
        // TODO: Throw status errors
        return env.Null();
    }
}

Napi::Value CubebJs::Destroy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int argc = info.Length();

    if (argc > 0) {
        Napi::TypeError::New(env, "Wrong amount of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    cubeb_destroy(this->internal_context);

    return Napi::Boolean::New(env, true);
}

// Napi::Value CubebJs::EnumerateDevices(const Napi::CallbackInfo& info) {}

// Napi::Value CubebJs::DeviceCollectionDestroy(const Napi::CallbackInfo& info) {}

// Napi::Value CubebJs::RegisterDeviceCollectionChanged(const Napi::CallbackInfo& info) {}