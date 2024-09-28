//
//  NetProfile.h
//  PrinterSDK
//
//  Created by max on 2024/5/27.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NetProfile : NSObject
/// 打印机名称
@property (nonatomic, readonly) NSString *printerName;

/// 打印机描述
@property (nonatomic, readonly) NSString *printerDesc;

/// 设置MAC地址
- (void)setMAC:(NSData *)mac;

/// 设置IP地址
- (void)setIP:(NSData *)ip;

/// 设置子网掩码
- (void)setMask:(NSData *)mask;

/// 设置网关地址
- (void)setGateway:(NSData *)gw;

/// 设置DHCP
/// @param dhcp 是否启用DHCP，1表示启用，0表示禁用
- (void)setDHCP:(char)dhcp;

/// 获取IP地址的字符串表示
/// @return IP地址的字符串
- (NSString *)getIPString;

/// 获取子网掩码的字符串表示
/// @return 子网掩码的字符串
- (NSString *)getMaskString;

/// 获取网关地址的字符串表示
/// @return 网关地址的字符串
- (NSString *)getGatewayString;

/// 获取DHCP设置
/// @return DHCP设置，1表示启用，0表示禁用
- (char)getDHCP;

/// 获取MAC地址数组
/// @return MAC地址数组
- (Byte *)getMACArray;

@end

NS_ASSUME_NONNULL_END
