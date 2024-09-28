//
//  XAccessory.h
//  PrinterSDK
//
//  Created by max on 2024/5/29.
//

@import Foundation;
@import ExternalAccessory;

extern NSString *EADSessionDataReceivedNotification;

/// XAccessory 类用于管理外部配件通信。
@interface XAccessory : NSObject <EAAccessoryDelegate, NSStreamDelegate>

/// 返回 XAccessory 的共享实例。
+ (XAccessory *)sharedInstance;

/// 配置指定的外部配件和协议字符串。
/// @param accessory 要配置的外部配件对象。
/// @param protocolString 使用的通信协议字符串。
- (void)setupControllerForAccessory:(EAAccessory *)accessory withProtocolString:(NSString *)protocolString;

/// 打开与外部配件的会话。
/// @return 打开会话是否成功。
- (BOOL)openSession;

/// 关闭与外部配件的会话。
- (void)closeSession;

/// 向外部配件写入数据。
/// @param data 要写入的数据。
- (void)writeData:(NSData *)data;

/// 返回当前可读取的字节数。
/// @return 当前可读取的字节数。
- (NSUInteger)readBytesAvailable;

/// 从外部配件读取指定字节数的数据。
/// @param bytesToRead 要读取的字节数。
/// @return 从外部配件读取的数据。
- (NSData *)readData:(NSUInteger)bytesToRead;

/// 外部配件对象。
@property (nonatomic, readonly) EAAccessory *accessory;

/// 使用的通信协议字符串。
@property (nonatomic, readonly) NSString *protocolString;

@end



