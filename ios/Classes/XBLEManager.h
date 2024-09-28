//
//  XBLEManager.h
//  PrinterSDK
//
//  Created by max on 2024/5/19.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "XAdvProtocol.h"

// 打印中/打印完成后的打印机状态
typedef NS_ENUM(NSInteger, POSPrinterStatus) {
    POSPrinterNormal = 0,                   // 打印机正常  0x12
    POSPrinterCoverOpen,                    // 开盖不缺纸  0x16
    POSPrinterPaperEnd,                     // 合盖缺纸    0x32
    POSPrinterCoverOpenPaperEnd,            // 开盖缺纸    0x36
    POSPrinterPaperFeed,                    // 走纸       0x1A
    POSPrinterOtherError                    // 其他错误
};

@protocol XBLEManagerDelegate <NSObject>
@optional

/// 发现蓝牙外设
/// @param peripheral 外设对象
/// @param advertisementData 广告数据
/// @param RSSI 信号强度
- (void)xbleDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI;

/// 连接成功
/// @param peripheral 连接的外设
- (void)xbleConnectPeripheral:(CBPeripheral *)peripheral;

/// 连接失败
/// @param peripheral 连接失败的外设
/// @param error 错误信息
- (void)xbleFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

/// 断开连接
/// @param peripheral 断开连接的外设
/// @param error 错误信息
- (void)xbleDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

/// 发送数据成功
/// @param characteristic 特征对象
/// @param error 错误信息
- (void)xbleWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/// 接收到打印机数据
/// @param characteristic 特征对象
/// @param error 错误信息
- (void)xbleReceiveValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/// 蓝牙中心管理器状态更新
/// @param state 蓝牙状态
- (void)xbleCentralManagerDidUpdateState:(NSInteger)state;

@end

/****************************************************************************************************/

/// 接收到数据时的回调块类型定义。
typedef void (^XBLEManagerReceiveCallBackBlock)(CBCharacteristic *characteristic, NSError *error);

/// 数据写入时的回调块类型定义。
typedef void (^XBLEManagerWriteCallBackBlock)(CBCharacteristic *characteristic, NSError *error);

/// 报告POS打印机状态时的回调块类型定义。
typedef void (^XBLEPOSPrinterStatusBlock)(NSData *status);

/// 报告标签打印机状态时的回调块类型定义。
typedef void (^XBLELabelPrinterStatusBlock)(NSData *status);

/// 报告打印机序列号时的回调块类型定义。
typedef void (^XBLEPrinterSNBlock)(NSString *sn);

/// 报告钱箱状态时的回调块类型定义。
typedef void (^XBLECashBoxBlock)(NSData *status);

/****************************************************************************************************/

@interface XBLEManager : NSObject <XAdvProtocol>

/// 蓝牙设备的名称。
@property (nonatomic, copy) NSString *name;

/// 蓝牙设备的连接状态。
@property (nonatomic, assign) BOOL isConnected;

/// 当前蓝牙设备的扫描状态。
@property (nonatomic, assign) BOOL isScaning;

/// 关联写特征值的外设设备。
@property (nonatomic, strong) CBPeripheral *writePeripheral;

/// 用于向外设设备写入数据的特征值。
@property (nonatomic, strong) CBCharacteristic *write_characteristic;

/// 用于从外设设备读取数据的特征值。
@property (nonatomic, strong) CBCharacteristic *read_characteristic;

/// 用于从外设设备接收通知的特征值。
@property (nonatomic, strong) CBCharacteristic *notify_characteristic;

/// 用于手动设置过滤条件查找特定打印机设备的UUID。
@property (nonatomic, strong) CBUUID *searchFilterUUID;

/// 特征值的UUID。
@property (nonatomic, strong) CBUUID *characteristicUUID;

/// 接收蓝牙管理器事件的代理。
@property (nonatomic, weak) id<XBLEManagerDelegate> delegate;

/// 接收到数据时调用的回调块。
@property (nonatomic, copy) XBLEManagerReceiveCallBackBlock receiveBlock;

/// 数据写入时调用的回调块。
@property (nonatomic, copy) XBLEManagerWriteCallBackBlock writeBlock;

/// 报告POS打印机状态时调用的回调块。
@property (nonatomic, copy) XBLEPOSPrinterStatusBlock statusPOSBlock;

/// 报告标签打印机状态时调用的回调块。
@property (nonatomic, copy) XBLELabelPrinterStatusBlock statusLabelBlock;

/// 报告打印机序列号时调用的回调块。
@property (nonatomic, copy) XBLEPrinterSNBlock snBlock;

/// 报告钱箱状态时调用的回调块。
@property (nonatomic, copy) XBLECashBoxBlock cashBoxBlock;

/// 单例对象
+ (instancetype)sharedInstance;

/// 移除委托对象
- (void)removeDelegate:(id<XBLEManagerDelegate>)delegate;

/// 移除所有委托对象
- (void)removeAllDelegates;

/// 开始扫描
- (void)startScan;

/// 停止扫描
- (void)stopScan;

/// 连接特定设备
/// @param peripheral 外设对象
- (void)connectDevice:(CBPeripheral *)peripheral;

/// 手动断开连接
- (void)disconnectRootPeripheral;

/// 发送指令(Write with Response)
/// @param data 待发送的数据
- (void)writeCommandWithData:(NSData *)data;

/// 发送指令并带有接收回调(Write with Response)
/// @param data 待发送的数据
/// @param receiveBlock 接收数据回调
- (void)writeCommandWithData:(NSData *)data receiveCallBack:(XBLEManagerReceiveCallBackBlock)receiveBlock;

/// 发送指令并带有写入回调(Write with Response)
/// @param data 待发送的数据
/// @param writeBlock 写入数据回调
- (void)writeCommandWithData:(NSData *)data writeCallBack:(XBLEManagerWriteCallBackBlock)writeBlock;

/// 发送指令(Write without Response)
/// @param data 待发送的数据
- (void)writeCommandDataWithoutResponse:(NSData *)data;

/// 设置蓝牙名称和密钥
/// @param btName 蓝牙名称
/// @param btKey 蓝牙密钥
- (void)setBluetoothNameAndKeyWith:(NSString *)btName btKey:(NSString *)btKey;

/// 打印机状态（针对票据打印机）
/// @param statusBlock 状态回调
- (void)printerPOSStatus:(XBLEPOSPrinterStatusBlock)statusBlock;

/// 打印机状态（针对标签打印机）
/// @param statusBlock 状态回调
- (void)printerLabelStatus:(XBLELabelPrinterStatusBlock)statusBlock;

/// 打印机序列号
/// @param snBlock 序列号回调
- (void)printerSN:(XBLEPrinterSNBlock)snBlock;

/// 钱箱状态
/// @param cashBoxBlock 状态回调
- (void)cashBoxCheck:(XBLECashBoxBlock)cashBoxBlock;

/// 获取版权信息
+ (NSString *)GetCopyRight;

@end

