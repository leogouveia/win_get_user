import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:win_get_user/win_get_user.dart';

void main() {
  const MethodChannel channel = MethodChannel('win_get_user');

  TestWidgetsFlutterBinding.ensureInitialized();

  setUp(() {
    channel.setMockMethodCallHandler((MethodCall methodCall) async {
      return '42';
    });
  });

  tearDown(() {
    channel.setMockMethodCallHandler(null);
  });

  test('getPlatformVersion', () async {
    expect(await WinGetUser.platformVersion, '42');
  });
}
