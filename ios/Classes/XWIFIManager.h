//
//  XWIFIManager.h
//  PrinterSDK
//
//  Created by max on 2024/5/19.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "NetProfile.h"
#import "XAdvProtocol.h"
@class XWIFIManager;
@protocol XWIFIManagerDelegate <NSObject>
@optional

/// 连接成功回调
///
/// @param host 主机地址
/// @param port 端口号
- (void)xWifiConnectedToHost:(NSString *)host port:(UInt16)port;

/// 断开连接错误回调
/// @param error 错误信息
- (void)xWifiDisconnectWithError:(NSError *)error;

/// 发送数据成功回调
/// @param tag 标签值
- (void)xWifiWriteValueWithTag:(long)tag;

/// 接收到打印机数据回调
/// @param data 接收到的数据
- (void)xWifiReceiveValueForData:(NSData *)data;

@end

/****************************************************************************************************/

/// 接收到数据时的回调块类型定义。
typedef void (^XWIFIManagerReceiveBlock)(NSData *data);

/// 数据写入时的回调块类型定义。
typedef void (^XWIFIManagerWriteBlock)(BOOL success, NSError *error);

/// 报告POS打印机状态时的回调块类型定义。
typedef void (^XWIFIPOSPrinterStatusBlock)(NSData *status);

/// 报告标签打印机状态时的回调块类型定义。
typedef void (^XWIFILabelPrinterStatusBlock)(NSData *status);

/// 报告打印机序列号时的回调块类型定义。
typedef void (^XWIFIPrinterSNBlock)(NSString *sn);

/// 检查POS打印机状态时的回调块类型定义。
typedef void (^XWIFIPOSPrinterCheckBlock)(NSData *check);

/// 发现打印机时的回调块类型定义。
typedef void (^XWIFIManagerFoundPrinterBlock)(NetProfile *foundPrinter);

/// 报告钱箱状态时的回调块类型定义。
typedef void (^XWIFICashBoxBlock)(NSData *status);


@class NetProfile;

/****************************************************************************************************/

@interface XWIFIManager : NSObject <XAdvProtocol>
/// 主机地址字符串。
@property (nonatomic, copy) NSString *hostStr;

/// 端口号。
@property (nonatomic, assign) UInt16 port;

/// 连接状态。
@property (nonatomic, assign) BOOL isConnected;

/// 接收WiFi管理器事件的代理。
@property (nonatomic, weak) id<XWIFIManagerDelegate> delegate;

/// 接收到数据时调用的回调块。
@property (nonatomic, copy) XWIFIManagerReceiveBlock receiveBlock;

/// 数据写入时调用的回调块。
@property (nonatomic, copy) XWIFIManagerWriteBlock writeBlock;

/// 报告POS打印机状态时调用的回调块。
@property (nonatomic, copy) XWIFIPOSPrinterStatusBlock statusPOSBlock;

/// 报告标签打印机状态时调用的回调块。
@property (nonatomic, copy) XWIFILabelPrinterStatusBlock statusLabelBlock;

/// 报告打印机序列号时调用的回调块。
@property (nonatomic, copy) XWIFIPrinterSNBlock snBlock;

/// 检查POS打印机状态时调用的回调块。
@property (nonatomic, copy) XWIFIPOSPrinterCheckBlock checkPOSBlock;

/// 发现打印机时调用的回调块。
@property (nonatomic, copy) XWIFIManagerFoundPrinterBlock foundPrinterBlock;

/// 报告钱箱状态时调用的回调块。
@property (nonatomic, copy) XWIFICashBoxBlock cashBoxBlock;

/// 已连接的打印机的配置文件。
@property (nonatomic, strong) NetProfile *connectedPrinter;


/// 获取单例对象
+ (instancetype)sharedInstance;

/// 移除一个委托对象
/// @param delegate 委托对象
- (void)removeDelegate:(id<XWIFIManagerDelegate>)delegate;

/// 移除所有委托对象
- (void)removeAllDelegates;

/// 连接打印机地址
/// @param hostStr 打印机主机地址
/// @param port 端口号
- (void)connectWithHost:(NSString *)hostStr port:(UInt16)port;

/// 断开连接
- (void)disconnect;

/// 向打印机写入指令
/// @param data 指令数据
- (void)writeCommandWithData:(NSData *)data;

/// 向打印机写入指令，并指定接收回调
/// @param data 指令数据
/// @param receiveBlock 接收回调
- (void)writeCommandWithData:(NSData *)data receiveCallBack:(XWIFIManagerReceiveBlock)receiveBlock;

/// 向打印机写入指令，并指定写入完成回调
/// @param data 指令数据
/// @param writeBlock 写入完成回调
- (void)writeCommandWithData:(NSData *)data writeCallBack:(XWIFIManagerWriteBlock)writeBlock;

/// 创建 UDP Socket
/// @return 是否创建成功
- (BOOL)createUdpSocket;

/// 关闭 UDP Socket
- (void)closeUdpSocket;

/// 搜索打印机
/// @param foundPrinterBlock 搜索到打印机的回调
- (void)sendFindCmd:(XWIFIManagerFoundPrinterBlock)foundPrinterBlock;

/// 设置 IP 配置
/// @param ip IP 地址
/// @param mask 子网掩码
/// @param gateway 网关
/// @param dhcp 是否启用 DHCP
- (void)setIPConfigWithIP:(NSString *)ip Mask:(NSString *)mask Gateway:(NSString *)gateway DHCP:(BOOL)dhcp;

/// 设置 WiFi 配置
///
/// @param ip IP 地址
/// @param mask 子网掩码
/// @param gateway 网关
/// @param ssid WiFi SSID
/// @param password WiFi 密码
/// @param encrypt 加密方式
- (void)setWiFiConfigWithIP:(NSString *)ip mask:(NSString *)mask gateway:(NSString *)gateway ssid:(NSString *)ssid password:(NSString *)password encrypt:(NSUInteger)encrypt;

/// 检查打印机连接状态
/// @return 是否连接
- (BOOL)printerIsConnect;

/// 获取打印机序列号
/// @param snBlock 序列号回调
- (void)printerSN:(XWIFIPrinterSNBlock)snBlock;

/// 通过 MAC 地址连接打印机
/// @param macStr MAC 地址
- (void)connectWithMac:(NSString *)macStr;

/// 打印机状态（针对票据打印机）
/// @param statusBlock 状态回调
- (void)printerPOSStatus:(XWIFIPOSPrinterStatusBlock)statusBlock;

/// 打印机状态（针对标签打印机）
/// @param statusBlock 状态回调
- (void)printerLabelStatus:(XWIFILabelPrinterStatusBlock)statusBlock;

/// 查询打印机状态
/// @param type 查询类型（1: 常用状态, 2: 脱机状态, 3: 错误状态, 4: 传送纸状态）
/// @param checkBlock 查询结果回调
- (void)printerPOSCheck:(int)type checkBlock:(XWIFIPOSPrinterCheckBlock)checkBlock;

/// 钱箱状态
/// @param cashBoxBlock 状态回调
- (void)cashBoxCheck:(XWIFICashBoxBlock)cashBoxBlock;

/// 获取版权信息
/// @return 版权信息字符串
+ (NSString *)GetCopyRight;

@end

