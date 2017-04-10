#include <GL/gl.h>
#include <GL/glx.h>
#include <FTGL/ftgl.h>
#include <stdio.h>
#include <dlfcn.h>

static void init () __attribute__((constructor));
void performOverlay();

void (*_glfwSwapBuffers)() = NULL;

void glfwSwapBuffers()
{
  printf("Hello from injected glfwSwapBuffers\n");
  if (_glfwSwapBuffers == NULL) {
    void *handle = dlopen("libglfw.so", RTLD_LAZY);
    if (handle) {
      _glfwSwapBuffers = dlsym(handle, "glfwSwapBuffers");
      dlclose(handle);
    }
  }

  performOverlay();
  
  _glfwSwapBuffers();
}

void (*_glSwapBuffers)() = NULL;

void glSwapBuffers()
{
  printf("Hello from injected glSwapBuffers\n");
  if (_glSwapBuffers == NULL) {
    void *handle = dlopen("libGL.so", RTLD_LAZY);
    if (handle) {
      _glSwapBuffers = dlsym(handle, "glSwapBuffers");
      dlclose(handle);
    }
  }

  performOverlay();
  
  _glSwapBuffers();
}

void (*_glXSwapBuffers)(Display *dpy, GLXDrawable drawable) = NULL;

void glXSwapBuffers(Display *dpy, GLXDrawable drawable)
{
  printf("Hello from injected glXSwapBuffers\n");
  if (_glSwapBuffers == NULL) {
    void *handle = dlopen("libGL.so", RTLD_LAZY);
    if (handle) {
      _glXSwapBuffers = dlsym(handle, "glXSwapBuffers");
      dlclose(handle);
    }
  }

  performOverlay();
  
  _glXSwapBuffers(dpy, drawable);
}

static void init()
{
printf("Hello from injector\n");
}

void performOverlay()
{
  static FTGLfont *font = NULL;

  printf("Hello from injected performOverlay\n");
  if (font == NULL) {
    font = ftglCreateTextureFont("font.ttf");
    ftglSetFontFaceSize(font, 16, 16);
  }

  glColor4f(0, 0, 0, 1);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, 800.0, 0.0, 600.0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(10, 590 - 16, 0.0);

  ftglRenderFont(font, "Here I should print some useful information.", FTGL_RENDER_ALL);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}
