import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'flutter_printer_sdk_platform_interface.dart';

/// An implementation of [FlutterPrinterSdkPlatform] that uses method channels.
class MethodChannelFlutterPrinterSdk extends FlutterPrinterSdkPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_printer_sdk');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
