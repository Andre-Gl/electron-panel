#import <AppKit/AppKit.h>
#import <CoreServices/CoreServices.h>
#import <Foundation/Foundation.h>
#import <objc/objc-runtime.h>

#include "functions.h"

@interface Panel : NSPanel
@property(strong, nonatomic) NSWindow *originalWindow;
@end

@implementation Panel
@synthesize originalWindow;
@synthesize canBecomeKeyWindow;
- (id)init {
  self = [super init];
  if (self) {
    canBecomeKeyWindow = NO;
  }
  return self;
}
@end

napi_value MakePanel(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value handleBuffer[1];

  status = napi_get_cb_info(env, info, &argc, handleBuffer, 0, 0);
  if (status != napi_ok || argc < 1) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return 0;
  }

  napi_handle_scope scope;
  status = napi_open_handle_scope(env, &scope);
  if (status != napi_ok) {
    return 0;
  }

  void *buffer;
  size_t bufferLength;
  status = napi_get_buffer_info(env, handleBuffer[0], &buffer, &bufferLength);
  if (status != napi_ok) {
    return handleBuffer[0];
  }
  NSView *mainContentView = *reinterpret_cast<NSView **>(buffer);
  if (!mainContentView)
    return handleBuffer[0];

  NSWindow *originalWindow = mainContentView.window;

  // Create NSPanel
  Panel *window = [[Panel alloc] init];
  [window setReleasedWhenClosed:YES];
  [window setOriginalWindow:originalWindow];

  [window setFrame:originalWindow.frame display:NO];
  [window setContentSize:mainContentView.frame.size];
  [window
      setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameDarkAqua]];
  [window setMovableByWindowBackground:YES];
  [window setFloatingPanel:YES];
  [window setLevel:NSFloatingWindowLevel];
  [window setCanHide:NO];
  [window setTitleVisibility:NSWindowTitleHidden];
  [window setTitlebarAppearsTransparent:YES];
  [window setStyleMask:NSWindowStyleMaskTitled |
                       NSWindowStyleMaskFullSizeContentView |
                       NSWindowStyleMaskNonactivatingPanel];
  [window setCollectionBehavior:NSWindowCollectionBehaviorCanJoinAllSpaces |
                                NSWindowCollectionBehaviorFullScreenAuxiliary];

  [window setHidesOnDeactivate:NO];

  // Apply Vibrancy
  NSView *visualEffectRootView =
      [[NSVisualEffectView alloc] initWithFrame:mainContentView.frame];

  [visualEffectRootView
      setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];

  [visualEffectRootView
      setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameVibrantDark]];
  [visualEffectRootView setState:NSVisualEffectStateActive];
  [mainContentView addSubview:visualEffectRootView
                   positioned:NSWindowBelow
                   relativeTo:nil];

  // Move content to NSPanel
  [mainContentView removeFromSuperview];
  [window setContentView:mainContentView];

  status = napi_close_handle_scope(env, scope);
  if (status != napi_ok) {
    return 0;
  }

  return handleBuffer[0];
}

napi_value ShowPanel(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value handleBuffer[1];

  status = napi_get_cb_info(env, info, &argc, handleBuffer, 0, 0);
  if (status != napi_ok || argc < 1) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return 0;
  }

  napi_handle_scope scope;
  status = napi_open_handle_scope(env, &scope);
  if (status != napi_ok) {
    return 0;
  }

  void *buffer;
  size_t bufferLength;
  status = napi_get_buffer_info(env, handleBuffer[0], &buffer, &bufferLength);
  if (status != napi_ok) {
    return handleBuffer[0];
  }
  NSView *mainContentView = *reinterpret_cast<NSView **>(buffer);
  if (!mainContentView)
    return handleBuffer[0];

  Panel *window = mainContentView.window;

  [window orderFrontRegardless];

  status = napi_close_handle_scope(env, scope);
  if (status != napi_ok) {
    return 0;
  }

  return handleBuffer[0];
}

napi_value DestroyPanel(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value handleBuffer[1];

  status = napi_get_cb_info(env, info, &argc, handleBuffer, 0, 0);
  if (status != napi_ok || argc < 1) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return 0;
  }

  napi_handle_scope scope;
  status = napi_open_handle_scope(env, &scope);
  if (status != napi_ok) {
    return 0;
  }

  void *buffer;
  size_t bufferLength;
  status = napi_get_buffer_info(env, handleBuffer[0], &buffer, &bufferLength);
  if (status != napi_ok) {
    return handleBuffer[0];
  }
  NSView *mainContentView = *reinterpret_cast<NSView **>(buffer);
  if (!mainContentView)
    return handleBuffer[0];

  Panel *window = mainContentView.window;

  [window.originalWindow close];
  [window close];

  status = napi_close_handle_scope(env, scope);
  if (status != napi_ok) {
    return 0;
  }

  return handleBuffer[0];
}

napi_value AnimatePanelEnter(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value handleBuffer[1];

  status = napi_get_cb_info(env, info, &argc, handleBuffer, 0, 0);
  if (status != napi_ok || argc < 1) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return 0;
  }

  napi_handle_scope scope;
  status = napi_open_handle_scope(env, &scope);
  if (status != napi_ok) {
    return 0;
  }

  void *buffer;
  size_t bufferLength;
  status = napi_get_buffer_info(env, handleBuffer[0], &buffer, &bufferLength);
  if (status != napi_ok) {
    return handleBuffer[0];
  }
  NSView *mainContentView = *reinterpret_cast<NSView **>(buffer);
  if (!mainContentView)
    return handleBuffer[0];

  Panel *window = mainContentView.window;

   // Hide the window at the start
  [window setAlphaValue:0.0];
  [window orderFrontRegardless];

  // Move the window down to its starting point
  NSRect originalFrame = [window frame];
  NSRect offsetFrame = NSOffsetRect(originalFrame, 0, -12);
  [window setFrame:offsetFrame display:true];

  // Animate the window back to its normal position and alpha
  [NSAnimationContext beginGrouping];
  [[window animator] setAlphaValue:1.0];
  [[window animator] setFrame:originalFrame display:true];
  [NSAnimationContext endGrouping];

  status = napi_close_handle_scope(env, scope);
  if (status != napi_ok) {
    return 0;
  }

  return handleBuffer[0];
}

napi_value AnimatePanelLeave(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value handleBuffer[1];

  status = napi_get_cb_info(env, info, &argc, handleBuffer, 0, 0);
  if (status != napi_ok || argc < 1) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return 0;
  }

  napi_handle_scope scope;
  status = napi_open_handle_scope(env, &scope);
  if (status != napi_ok) {
    return 0;
  }

  void *buffer;
  size_t bufferLength;
  status = napi_get_buffer_info(env, handleBuffer[0], &buffer, &bufferLength);
  if (status != napi_ok) {
    return handleBuffer[0];
  }
  NSView *mainContentView = *reinterpret_cast<NSView **>(buffer);
  if (!mainContentView)
    return handleBuffer[0];

  Panel *window = mainContentView.window;

  // Animate the window alpha
  [NSAnimationContext beginGrouping];
  __block __unsafe_unretained NSWindow *_originalWindow = window.originalWindow;
  __block __unsafe_unretained Panel *_window = window;
  [[NSAnimationContext currentContext] setCompletionHandler:^{
    [_originalWindow close];
    [_window close];
  }];
  [[window animator] setAlphaValue:0.0];
  [NSAnimationContext endGrouping];

  status = napi_close_handle_scope(env, scope);
  if (status != napi_ok) {
    return 0;
  }

  return handleBuffer[0];
}
