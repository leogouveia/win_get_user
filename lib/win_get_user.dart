import 'dart:async';

import 'package:flutter/services.dart';

class WinGetUser {
  static const MethodChannel _channel = MethodChannel('win_get_user');

  static Future<String?> get platformVersion async {
    final String? version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  static Future<String?> get getLoggedUser async {
    try {
      return await _channel.invokeMethod("getLoggedUser");
    } catch (_) {
      return "Error";
    }
  }
}
