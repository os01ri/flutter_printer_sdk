import 'package:flutter/services.dart';

class PrinterManager {
  static const MethodChannel _channel = MethodChannel('flutter_printer_sdk_plugin');

  // Private constructor to prevent external instantiation
  PrinterManager._internal() {
    _channel.setMethodCallHandler(_handleMethodCall);
  }

  // Singleton instance
  static final PrinterManager _instance = PrinterManager._internal();

  // Factory constructor to return the same instance
  factory PrinterManager() {
    return _instance;
  }

  Function(int result)? _onConnectRet;

  Function? searchCallback;

  Future<void> _handleMethodCall(MethodCall call) async {
    switch (call.method) {
      case 'connectRet':
        int result = call.arguments['result'];
        if (_onConnectRet != null) {
          _onConnectRet!(result);
        }
        break;
      case 'searchBt':
        searchCallback?.call(call.arguments);
        break;
      default:
        print('Unknown method ${call.method}');
    }
  }

  Future<void> sendESC(List<Map<String, dynamic>> data) async {
    try {
      Map<String, Object> args = {};
      args['data'] = data;
      await _channel.invokeMethod('sendESC', args);
    } on PlatformException catch (e) {
      print("Failed to sendESC: '${e.message}'.");
      rethrow;
    }
  }

  Future<bool> checkPermissions() async {
    try {
      final bool result = await _channel.invokeMethod('checkPermissions');
      return result;
    } on PlatformException catch (e) {
      print("Failed to check permissions: '${e.message}'.");
      return false;
    }
  }

  Future<void> startScan() async {
    try {
      await _channel.invokeMethod('startScan');
    } on PlatformException catch (e) {
      print("Failed to start scan: '${e.message}'.");
    }
  }

  Future<void> disconnect() async {
    try {
      await _channel.invokeMethod('disconnect');
    } on PlatformException catch (e) {
      print("Failed to disconnect: '${e.message}'.");
    }
  }

  Future<int> checkIsConnect() async {
    try {
      final int result = await _channel.invokeMethod('checkIsConnect');
      return result;
    } on PlatformException catch (e) {
      print("Failed to checkIsConnect: '${e.message}'.");
      return 0;
    }
  }

  Future<void> connectBt(String address, Function(int result) callback) async {
    try {
      _onConnectRet = callback;
      await _channel.invokeMethod('connectBt', {"address": address});
    } on PlatformException catch (e) {
      print("Failed to connect Bluetooth: '${e.message}'.");
      rethrow;
    }
  }

  Future<void> setBluetooth(String name, String pin) async {
    try {
      await _channel.invokeMethod('setBluetooth', {"name": name, "pin": pin});
    } on PlatformException catch (e) {
      print("Failed to csetBluetooth: '${e.message}'.");
      rethrow;
    }
  }

  /// POS set Codepage
  Future<void> selectCodePage(int codepage) async {
    try {
      await _channel.invokeMethod('selectCodePage', {"page": codepage});
    } on PlatformException catch (e) {
      print("Failed to selectCodePage: '${e.message}'.");
      rethrow;
    }
  }
}
