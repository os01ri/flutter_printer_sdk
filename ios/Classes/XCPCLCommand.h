//
//  XCPCLCommand.h
//  PrinterSDK
//
//  Created by max on 2024/5/24.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "XConstants.h"

NS_ASSUME_NONNULL_BEGIN

@interface XCPCLCommand : NSObject

/// 获得打印命令
///
/// 将获取当前CPCL对象的打印数据
- (NSData*)getCommand;

/// 设置字符编码
///
/// @param encoding 编码格式，默认使用GB_18030_2000
- (XCPCLCommand *)setCharEncoding:(NSStringEncoding)encoding;

/// 添加自定义数据
///
/// @param customData 自定义的数据内容
- (XCPCLCommand *)addData:(NSData *)customData;

/// 标签初始化
///
/// @param height 标签的最大高度
- (XCPCLCommand *)initLabelWithHeight:(int)height;

/// 标签初始化
///
/// @param height 标签的最大高度
/// @param count 要打印的标签数量，默认为 1
- (XCPCLCommand *)initLabelWithHeight:(int)height count:(int)count;

/// 标签初始化
///
/// @param height 标签的最大高度
/// @param count 要打印的标签数量，默认为 1
/// @param offsetx 标签的横向偏移量，默认为 0
- (XCPCLCommand *)initLabelWithHeight:(int)height count:(int)count offsetx:(int)offsetx;

/// 文本打印
///
/// @param x 文本的起始 X 值
/// @param y 文本的起始 y 值
/// @param content 文本内容
- (XCPCLCommand *)addTextAtX:(int)x
              y:(int)y
        content:(NSString *)content;

/// 文本打印
///
/// @param x 文本的起始 X 值
/// @param y 文本的起始 y 值
/// @param font 文本的字体类型，默认CPCLFont0
/// @param content 文本内容
- (XCPCLCommand *)addTextAtX:(int)x
              y:(int)y
           font:(FontCPCL)font
        content:(NSString *)content;

/// 文本打印
///
/// @param x 文本的起始 X 值
/// @param y 文本的起始 y 值
/// @param rotation 顺时针旋转角度，默认CPCLRotation0
/// @param font 文本的字体类型，默认CPCLFont0
/// @param content 文本内容
- (XCPCLCommand *)addTextAtX:(int)x
              y:(int)y
       rotation:(RotationCPCL)rotation
           font:(FontCPCL)font
        content:(NSString *)content;

/// 将常驻字体放大指定倍数
///
/// @param w 宽度放大倍数 1～16
/// @param h 高度放大倍数 1～16
- (XCPCLCommand *)setmagWithw:(int)w h:(int)h;


/// 整个命令集的结束命令，将会启动文件打印
- (XCPCLCommand *)addPrint;

#pragma mark - 绘制一维条码

/// 横向一维条码
///
/// @param x 条码起始点横坐标，单位为点
/// @param y 条码起始点纵坐标，单位为点
/// @param type 条码类型，详细参考CPCLBarCodeType
/// @param height 条码的单位高度
/// @param content 条码数据内容
- (XCPCLCommand *)addBarcodeAtX:(int)x
                 y:(int)y
              type:(CPCLBarCodeType)type
            height:(int)height
           content:(NSString *)content;

/// 横向一维条码
///
/// @param x 条码起始点横坐标，单位为点
/// @param y 条码起始点纵坐标，单位为点
/// @param type 条码类型，详细参考CPCLBarCodeType
/// @param width 窄条的单位宽度，默认为 1
/// @param ratio 宽条与窄条的比率，默认CPCLBarCodeRatio1(2.0:1)
/// @param height 条码的单位高度
/// @param content 条码数据内容
- (XCPCLCommand *)addBarcodeAtX:(int)x
                 y:(int)y
              type:(CPCLBarCodeType)type
             width:(int)width
             ratio:(BarCodeRatioCPCL)ratio
            height:(int)height
           content:(NSString *)content;

/// 纵向一维条码
///
/// @param x 条码起始点横坐标，单位为点
/// @param y 条码起始点纵坐标，单位为点
/// @param type 条码类型，详细参考CPCLBarCodeType
/// @param height 条码的单位高度
/// @param content 条码数据内容
- (XCPCLCommand *)addBarcodeVAtX:(int)x
                         y:(int)y
                      type:(CPCLBarCodeType)type
                    height:(int)height
                   content:(NSString *)content;

/// 纵向一维条码
///
/// @param x 条码起始点横坐标，单位为点
/// @param y 条码起始点纵坐标，单位为点
/// @param type 条码类型，详细参考CPCLBarCodeType
/// @param width 窄条的单位宽度，默认为 1
/// @param ratio 宽条与窄条的比率，默认CPCLBarCodeRatio1(2.0:1)
/// @param height 条码的单位高度
/// @param content 条码数据内容
- (XCPCLCommand *)addBarcodeVAtX:(int)x
                         y:(int)y
                      type:(CPCLBarCodeType)type
                     width:(int)width
                     ratio:(int)ratio
                    height:(int)height
                   content:(NSString *)content;

/// 添加条码注释
///
/// @param offsetx 文本距离条码的单位偏移量
- (XCPCLCommand *)barcodeText:(int)offsetx;

/// 取消条码注释
- (XCPCLCommand *)barcodeTextOff;


/// 绘制二维条码
/// @param x 二维码起始横坐标
/// @param y 二维码起始纵坐标
/// @param content 二维码数据内容
- (XCPCLCommand *)addQRCodeAtX:(int)x
                y:(int)y
          content:(NSString *)content;

/// 绘制二维条码
/// @param x 二维码起始横坐标
/// @param y 二维码起始纵坐标
/// @param codeModel QR Code 规范编号，默认为 CPCLQRCodeModeEnhance
/// @param cellWidth 单元格大小，范围【1，32】,默认为 6
/// @param content 二维码数据内容
- (XCPCLCommand *)addQRCodeAtX:(int)x
                y:(int)y
        codeModel:(QRCodeModesCPCL)codeModel
        cellWidth:(int)cellWidth
          content:(NSString *)content;

/// 绘制矩形
///
/// @param x 矩形起始横坐标，单位为点
/// @param y 矩形起始纵坐标，单位为点
/// @param width 矩形宽度，单位为点
/// @param height 矩形高度，单位为点
/// @param thickness 线条宽度
- (XCPCLCommand *)addBoxAtX:(int)x
             y:(int)y
         width:(int)width
        height:(int)height
     thickness:(int)thickness;

/// 绘制线条
///
/// @param x 线条起始横坐标，单位为点
/// @param y 线条起始纵坐标，单位为点
/// @param xend 线条结束横坐标，单位为点
/// @param yend 线条结束纵坐标，单位为点
/// @param width 线条宽度
- (XCPCLCommand *)addLineAtX:(int)x y:(int)y xend:(int)xend yend:(int)yend width:(int)width;

/// 将指定区域的数据黑白反向显示
///
/// @param x 反显区域起始横坐标，单位为点
/// @param y 反显区域起始纵坐标，单位为点
/// @param xend 反显区域结束横坐标，单位为点
/// @param yend 反显区域结束纵坐标，单位为点
/// @param width 反显区域宽度
- (XCPCLCommand *)addInverseLineAtX:(int)x
                     y:(int)y
                  xend:(int)xend
                  yend:(int)yend
                 width:(int)width;

/// 绘制图片
///
/// @param x 图片起始横坐标，单位为点
/// @param y 图片起始纵坐标，单位为点
/// @param image 图片对象
- (XCPCLCommand *)addGraphicsAtX:(int)x y:(int)y image:(UIImage *)image;


/// 设置字段的对齐方式
///
/// 默认情况下，打印机将左对齐所有字段。对齐命令将对所有后续字段 保持有效，直至指定了其他对齐命令
///
/// @param align 对齐方式
- (XCPCLCommand *)addAlign:(AlignmentsCPCL)align;

/// 设置字段的对齐方式
///
/// 默认情况下，打印机将左对齐所有字段。对齐命令将对所有后续字段 保持有效，直至指定了其他对齐命令
///
/// @param align 对齐方式
/// @param end 对齐的结束点
- (XCPCLCommand *)addAlign:(AlignmentsCPCL)align end:(int)end;

/// 设置打印速度
///
/// @param level 速度级别，范围【0，5】
- (XCPCLCommand *)addSpeed:(int)level;

/// 设置打印宽度
///
/// @param width 页面的单位宽度
- (XCPCLCommand *)addPageWidth:(int)width;

/// 设置蜂鸣发出时间
///
/// 此方法用于让打印机蜂鸣器发出给定时间长度的声音，未配备蜂鸣器的打印机将忽略此方法
///
/// @param length 蜂鸣持续时间，以 1/8 秒为单位，例如 16 表示发声时间为 2 秒
- (XCPCLCommand *)addBeep:(int)length;

/// 指示打印机在一页打印结束后切换至下一页顶部
- (XCPCLCommand *)form;

@end

NS_ASSUME_NONNULL_END

