#include "include/win_get_user/win_get_user_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <map>
#include <memory>
#include <sstream>
#include <lmcons.h>

namespace {

class WinGetUserPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  WinGetUserPlugin();

  virtual ~WinGetUserPlugin();

 private:

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
  
  std::string getPlatformVersion();

  std::string getLoggedUser();

};

// static
void WinGetUserPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "win_get_user",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<WinGetUserPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

WinGetUserPlugin::WinGetUserPlugin() {}

WinGetUserPlugin::~WinGetUserPlugin() {}

// Implementation of get windows version
std::string WinGetUserPlugin::getPlatformVersion() {
  std::ostringstream version_stream;
  version_stream << "Windows";
  if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    return version_stream.str();
}

std::string WinGetUserPlugin::getLoggedUser() {
  char username[UNLEN+1];
  DWORD username_len = UNLEN+1;
  GetUserNameA(username, &username_len);
  return std::string(username);
}

void WinGetUserPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  
   if (method_call.method_name().compare("getPlatformVersion") == 0) {
   
    result->Success(flutter::EncodableValue(WinGetUserPlugin::getPlatformVersion()));
    return;
  } else if (method_call.method_name().compare("getLoggedUser") == 0) {

    result->Success(flutter::EncodableValue(WinGetUserPlugin::getLoggedUser()));
    return;
  }
    
  result->NotImplemented();
}

}  // namespace

void WinGetUserPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  WinGetUserPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
