#import "FlutterPrinterSdkPlugin.h"
#import "XSDKPrinter.h"
#import "LogicM.h"

typedef NS_ENUM(NSInteger, ConnectMethod) {
    ConnectMethodNone = -1,
    ConnectMethodBluetooth = 0,
    ConnectMethodWiFi = 1,
    ConnectMethodMFiDevice = 2,
};

@interface FlutterPrinterSdkPlugin ()<XBLEManagerDelegate,XWIFIManagerDelegate>
@property(nonatomic, retain) FlutterMethodChannel *channel;
@property(nonatomic) NSMutableDictionary *scannedPeripherals;
@property(nonatomic, assign) int connectMethod;
@end

@implementation FlutterPrinterSdkPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
    FlutterMethodChannel* channel = [FlutterMethodChannel
                                     methodChannelWithName:@"flutter_printer_sdk_plugin"
                                     binaryMessenger:[registrar messenger]];
    FlutterPrinterSdkPlugin* instance = [[FlutterPrinterSdkPlugin alloc] init];
    [registrar addMethodCallDelegate:instance channel:channel];
    instance.channel = channel;
    [XBLEManager sharedInstance].delegate = instance;
    [XWIFIManager sharedInstance].delegate = instance;
}

- (NSMutableDictionary *)scannedPeripherals {
    if (!_scannedPeripherals) {
        _scannedPeripherals = [NSMutableDictionary dictionary];
    }
    return _scannedPeripherals;
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    if ([@"checkPermissions" isEqualToString:call.method]) {
        [self checkPermissions:result];
    } else if ([@"startScan" isEqualToString:call.method]) {
        [self startScan:result];
    } else if ([@"connectBt" isEqualToString:call.method]) {
        [self connectBt:call result:result];
    } else if ([@"connectNet" isEqualToString:call.method]) {
        [self connectNet:call result:result];
    } else if ([@"sendESC" isEqualToString:call.method]) {
        [self sendESC:call result:result];
    } else if ([@"disconnect" isEqualToString:call.method]) {
        [self disconnect:result];
    } else if ([@"posPrinterStatus" isEqualToString:call.method]) {
        [self posPrinterStatus:result];
    } else if ([@"getUsbPaths" isEqualToString:call.method]) {
        [self getUsbPaths:result];
    } else if ([@"sendTSPL" isEqualToString:call.method]) {
        [self sendTSPL:call result:result];
    } else if ([@"getSerialNumber" isEqualToString:call.method]) {
        [self getSerialNumber:result];
    } else if ([@"checkIsConnect" isEqualToString:call.method]) {
        [self checkIsConnect:result];
    } else if ([@"openCashBox" isEqualToString:call.method]) {
        [self openCashBox:result];
    } else if ([@"labelPrinterStatus" isEqualToString:call.method]) {
        [self labelPrinterStatus:call result:result];
    } else if ([@"connectUsb" isEqualToString:call.method]) {
        [self connectUsb:call result:result];
    } else if ([@"setBluetooth" isEqualToString:call.method]) {
        [self setBluetooth:call result:result];
    } else if ([@"cashBoxCheck" isEqualToString:call.method]) {
        [self cashBoxCheck:result];
    } else if ([@"sendZPL" isEqualToString:call.method]) {
        [self sendZPL:call result:result];
    } else if ([@"setCodePage" isEqualToString:call.method]) {
        [self setCodePage:call result:result];
    } else if ([@"selectCodePage" isEqualToString:call.method]) {
        [self selectCodePage:call result:result];
    }  else {
        result(FlutterMethodNotImplemented);
    }
}

- (void)setCodePage:(FlutterMethodCall*)call result:(FlutterResult)result {
    if (![call.arguments isKindOfClass:[NSDictionary class]]) {
        result([FlutterError errorWithCode:@"INVALID_ARGUMENT"
                                   message:@"Expected a dictionary with address key"
                                   details:nil]);
        return;
    }
    
    NSDictionary *arguments = (NSDictionary *)call.arguments;
    NSString *codepage = arguments[@"codepage"];
    
    if (![codepage isKindOfClass:[NSString class]] || codepage.length == 0) {
        result([FlutterError errorWithCode:@"INVALID_CODEPAGE"
                                   message:@"codepage string is either missing or empty"
                                   details:nil]);
        return;
    }
    
    XTSPLCommand *command = [[XTSPLCommand alloc] init];
    [command codePage:codepage];
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] writeCommandWithData:[command getCommand]];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] writeCommandWithData:[command getCommand]];
    }
}

- (void)selectCodePage:(FlutterMethodCall*)call result:(FlutterResult)result {
    if (![call.arguments isKindOfClass:[NSDictionary class]]) {
        result([FlutterError errorWithCode:@"INVALID_ARGUMENT"
                                   message:@"Expected a dictionary with address key"
                                   details:nil]);
        return;
    }
    
    NSDictionary *arguments = (NSDictionary *)call.arguments;
    NSNumber *codepage = arguments[@"page"];
    
    if (![codepage isKindOfClass:[NSNumber class]]) {
        result([FlutterError errorWithCode:@"INVALID_PAGE"
                                   message:@"page value is either missing or empty"
                                   details:nil]);
        return;
    }
    
    XPOSCommand *command = [[XPOSCommand alloc] init];
    [command initializePrinter];
    [command selectCodePage:[codepage intValue]];
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] writeCommandWithData:[command getCommand]];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] writeCommandWithData:[command getCommand]];
    }
}

- (void)checkPermissions:(FlutterResult)result {
    // iOS no need to check permissions
}

- (void)startScan:(FlutterResult)result {
    [[XBLEManager sharedInstance] startScan];
}

- (void)connectBt:(FlutterMethodCall*)call result:(FlutterResult)result {
    
    if (![call.arguments isKindOfClass:[NSDictionary class]]) {
        result([FlutterError errorWithCode:@"INVALID_ARGUMENT"
                                   message:@"Expected a dictionary with address key"
                                   details:nil]);
        return;
    }
    
    NSDictionary *arguments = (NSDictionary *)call.arguments;
    NSString *uuid = arguments[@"address"];
    
    if (![uuid isKindOfClass:[NSString class]] || uuid.length == 0) {
        result([FlutterError errorWithCode:@"INVALID_UUID"
                                   message:@"UUID string is either missing or empty"
                                   details:nil]);
        return;
    }
    
    CBPeripheral *per = [self.scannedPeripherals objectForKey:uuid];
    
    if (per == nil) {
        result([FlutterError errorWithCode:@"PERIPHERAL_NOT_FOUND"
                                   message:[NSString stringWithFormat:@"No peripheral found with UUID: %@", uuid]
                                   details:nil]);
        return;
    }
    
    @try {
        [[XBLEManager sharedInstance] connectDevice:per];
        result(@"Connection attempt started");
    }
    @catch (NSException *exception) {
        result([FlutterError errorWithCode:@"CONNECTION_FAILED"
                                   message:exception.reason
                                   details:nil]);
    }
}

- (void)connectNet:(FlutterMethodCall*)call result:(FlutterResult)result {
    
    if (![call.arguments isKindOfClass:[NSDictionary class]]) {
        result([FlutterError errorWithCode:@"INVALID_ARGUMENT"
                                   message:@"Expected a dictionary with address key"
                                   details:nil]);
        return;
    }
    
    NSDictionary *arguments = (NSDictionary *)call.arguments;
    NSString *ip = arguments[@"address"];
    
    if (![ip isKindOfClass:[NSString class]] || ip.length == 0) {
        result([FlutterError errorWithCode:@"INVALID_ADDRESS"
                                   message:@"address string is either missing or empty"
                                   details:nil]);
        return;
    }
    
    @try {
        [[XWIFIManager sharedInstance] connectWithHost:ip port:9100];
        result(@"Connection attempt started");
    }
    @catch (NSException *exception) {
        result([FlutterError errorWithCode:@"CONNECTION_FAILED"
                                   message:exception.reason
                                   details:nil]);
    }
    
}

- (void)disconnect:(FlutterResult)result {
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] disconnectRootPeripheral];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] disconnect];
    }
}

- (void)posPrinterStatus:(FlutterResult)result {
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] printerPOSStatus:^(NSData *status) {
            result(@([LogicM posStatus:status]));
        }];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] printerPOSStatus:^(NSData *status) {
            result(@([LogicM posStatus:status]));
        }];
    }
}

- (void)getUsbPaths:(FlutterResult)result {
    // iOS not getUsbPaths
}

- (void)sendESC:(FlutterMethodCall*)call result:(FlutterResult)result {
    NSArray<NSDictionary<NSString *, id> *> *data = [call.arguments objectForKey:@"data"];
    NSData *sendData = [LogicM sendESC:data];
    if (self.connectMethod == ConnectMethodBluetooth) {
       [self printWithData:sendData];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] writeCommandWithData:sendData];
    }
}

- (void)printWithData:(NSData *)data {
    NSUInteger maxWriteLength = [[XBLEManager sharedInstance].writePeripheral maximumWriteValueLengthForType:CBCharacteristicWriteWithoutResponse];
    if (data.length > maxWriteLength) {
        NSLog(@"Send in packets");
        NSUInteger offset = 0;
        while (offset < data.length) {
            NSUInteger chunkLength = MIN(maxWriteLength, data.length - offset);
            NSData *chunk = [data subdataWithRange:NSMakeRange(offset, chunkLength)];
            [[XBLEManager sharedInstance] writeCommandWithData:chunk];
            offset += chunkLength;
        }
    } else {
        NSLog(@"Direct Send");
        [[XBLEManager sharedInstance] writeCommandWithData:data];
    }
}

- (void)sendTSPL:(FlutterMethodCall*)call result:(FlutterResult)result {
    NSArray<NSDictionary<NSString *, id> *> *data = [call.arguments objectForKey:@"data"];
    NSData *sendData = [LogicM sendTSPL:data];
    
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] writeCommandWithData:sendData];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] writeCommandWithData:sendData];
    }
}

- (void)sendZPL:(FlutterMethodCall*)call result:(FlutterResult)result {
    
    NSArray<NSDictionary<NSString *, id> *> *data = [call.arguments objectForKey:@"data"];
    NSData *sendData = [LogicM sendZPL:data];
    
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] writeCommandWithData:sendData];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] writeCommandWithData:sendData];
    }
}

- (void)getSerialNumber:(FlutterResult)result {
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] printerSN:^(NSString *sn) {
            result(sn);
        }];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] printerSN:^(NSString *sn) {
            result(sn);
        }];
    }
}

- (void)checkIsConnect:(FlutterResult)result {
    if (self.connectMethod == ConnectMethodBluetooth) {
        result (([XBLEManager sharedInstance].isConnected)?@1:@0);
    } else if (self.connectMethod == ConnectMethodWiFi) {
        result(([[XWIFIManager sharedInstance] isConnected])?@1:@0);
    }
}

- (void)openCashBox:(FlutterResult)result {
    XPOSCommand *command = [[XPOSCommand alloc] init];
    [command openCashBoxWithPinNumber:CashDrawerPin2 onTime:30 offTime:255];
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] writeCommandWithData:[command getCommand]];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] writeCommandWithData:[command getCommand]];
    }
}

- (void)labelPrinterStatus:(FlutterMethodCall*)call result:(FlutterResult)result {
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] printerLabelStatus:^(NSData *status) {
            result(@([LogicM labelStatus:status]));
        }];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] printerLabelStatus:^(NSData *status) {
            result(@([LogicM labelStatus:status]));
        }];
    }
}

- (void)connectUsb:(FlutterMethodCall*)call result:(FlutterResult)result {
  // iOS not use usb
}

- (void)setBluetooth:(FlutterMethodCall *)call result:(FlutterResult)result {
    NSString *name = call.arguments[@"name"];
    NSString *pin = call.arguments[@"pin"];
    if (name && pin) {
        [[XBLEManager sharedInstance] setBluetoothNameAndKeyWith:name btKey:pin];
    }
}

- (void)cashBoxCheck:(FlutterResult)result {
    if (self.connectMethod == ConnectMethodBluetooth) {
        [[XBLEManager sharedInstance] cashBoxCheck:^(NSData *status) {
            result(@([LogicM cashBoxStatus:status]));
        }];
    } else if (self.connectMethod == ConnectMethodWiFi) {
        [[XWIFIManager sharedInstance] cashBoxCheck:^(NSData *status) {
            result(@([LogicM cashBoxStatus:status]));
        }];
    }
}

#pragma mark - XBLEManagerDelegate

/// 发现蓝牙外设
/// @param peripheral 外设对象
/// @param advertisementData 广告数据
/// @param RSSI 信号强度
- (void)xbleDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI {
    NSString *peripheralName = peripheral.name ? peripheral.name : @"Unknown";
    [_channel invokeMethod:@"searchBt" arguments:@{peripheral.identifier.UUIDString: peripheralName}];
    [self.scannedPeripherals setObject:peripheral forKey:[[peripheral identifier] UUIDString]];
}

/// 连接成功
/// @param peripheral 连接的外设
- (void)xbleConnectPeripheral:(CBPeripheral *)peripheral {
    _connectMethod = ConnectMethodBluetooth;
    [_channel invokeMethod:@"connectRet" arguments:@{@"result":@0}];
}

/// 连接失败
/// @param peripheral 连接失败的外设
/// @param error 错误信息
- (void)xbleFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    _connectMethod = ConnectMethodNone;
    [_channel invokeMethod:@"connectRet" arguments:@{@"result":@-1}];
}

/// 断开连接
/// @param peripheral 断开连接的外设
/// @param error 错误信息
- (void)xbleDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    _connectMethod = ConnectMethodNone;
    [_channel invokeMethod:@"connectRet" arguments:@{@"result":@-2}];
}

/// 发送数据成功
/// @param characteristic 特征对象
/// @param error 错误信息
- (void)xbleWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    NSLog(@"ble write success");
}

/// 接收到打印机数据
/// @param characteristic 特征对象
/// @param error 错误信息
- (void)xbleReceiveValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    NSLog(@"ble receive data:%@",characteristic.value);
}

/// 蓝牙中心管理器状态更新
/// @param state 蓝牙状态
- (void)xbleCentralManagerDidUpdateState:(NSInteger)state {
    NSLog(@"BLE state:%ld",state);
}

#pragma mark - XWIFIManagerDelegate

/// 连接成功回调
///
/// @param host 主机地址
/// @param port 端口号
- (void)xWifiConnectedToHost:(NSString *)host port:(UInt16)port {
    _connectMethod = ConnectMethodWiFi;
    [_channel invokeMethod:@"connectRet" arguments:@{@"result":@0}];
}

/// 断开连接错误回调
/// @param error 错误信息
- (void)xWifiDisconnectWithError:(NSError *)error {
    _connectMethod = ConnectMethodNone;
    [_channel invokeMethod:@"connectRet" arguments:@{@"result":@-2}];
}

/// 发送数据成功回调
/// @param tag 标签值
- (void)xWifiWriteValueWithTag:(long)tag {
    
}

/// 接收到打印机数据回调
/// @param data 接收到的数据
- (void)xWifiReceiveValueForData:(NSData *)data {
    NSLog(@"wifi receive data:%@",data);
}

@end
