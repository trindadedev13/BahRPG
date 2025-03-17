#include <jni.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "gles.h"
#include "cube/cube.hpp"
#include "shader/shader_program.hpp"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

struct engine {
  struct android_app* app;
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;
  int32_t width;
  int32_t height;
};

static int engine_init_display(struct engine* engine) {
  const EGLint attribs[] = {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_DEPTH_SIZE, 16,
    EGL_NONE
  };
  EGLint w, h, format;
  EGLConfig config;
  EGLint numConfigs;
  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  eglInitialize(display, nullptr, nullptr);
  eglChooseConfig(display, attribs, &config, 1, &numConfigs);
  eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
  engine->surface = eglCreateWindowSurface(display, config, engine->app->window, nullptr);
  engine->context = eglCreateContext(display, config, nullptr, nullptr);
  eglMakeCurrent(display, engine->surface, engine->surface, engine->context);
  eglQuerySurface(display, engine->surface, EGL_WIDTH, &w);
  eglQuerySurface(display, engine->surface, EGL_HEIGHT, &h);
  engine->display = display;
  engine->width = w;
  engine->height = h;
  glViewport(0, 0, w, h);
  return 0;
}

static void engine_draw_frame(struct engine* engine) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const char* vertexShaderCode = R"(
  attribute vec3 aPosition;
  attribute vec3 aColor;
  varying vec3 vColor;
  void main() {
    gl_Position = vec4(aPosition, 1.0);
    vColor = aColor;
  })";

  const char* fragmentShaderCode = R"(
  precision mediump float;
  varying vec3 vColor;
  void main() {
    gl_FragColor = vec4(vColor, 1.0);
  })";

  static BahRPG::ShaderProgram shader(vertexShaderCode, fragmentShaderCode);
  static BahRPG::Cube cube(shader);
  cube.draw();

  eglSwapBuffers(engine->display, engine->surface);
}

static void engine_term_display(struct engine* engine) {
  if (engine->display != EGL_NO_DISPLAY) {
    eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (engine->context != EGL_NO_CONTEXT) {
      eglDestroyContext(engine->display, engine->context);
    }
    if (engine->surface != EGL_NO_SURFACE) {
      eglDestroySurface(engine->display, engine->surface);
    }
    eglTerminate(engine->display);
  }
  engine->display = EGL_NO_DISPLAY;
  engine->context = EGL_NO_CONTEXT;
  engine->surface = EGL_NO_SURFACE;
}

void android_main(struct android_app* state) {
  struct engine engine{};
  state->userData = &engine;
  engine.app = state;
  while (true) {
    int events;
    struct android_poll_source* source;
    while (ALooper_pollOnce(-1, nullptr, &events, (void**)&source) >= 0) {
      if (source) {
        source->process(state, source);
      }
      if (state->destroyRequested) {
        engine_term_display(&engine);
        return;
      }
    }
    engine_draw_frame(&engine);
  }
}
