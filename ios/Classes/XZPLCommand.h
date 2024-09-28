//
//  XZPLCommand.h
//  PrinterSDK
//
//  Created by max on 2024/5/24.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "XConstants.h"

@interface XZPLCommand : NSObject

/// 获得打印命令
///
/// 将获取当前ZPL对象的打印数据
- (NSData*)getCommand;

/// 设置字符编码
///
/// @param encoding 编码格式，默认使用GB_18030_2000
- (XZPLCommand *)setCharEncoding:(NSStringEncoding)encoding;

/// 添加自定义数据
///
/// @param customData 自定义的数据内容
- (XZPLCommand *)addData:(NSData *)customData;

/// 此方法用于标签的开头
///
/// - Note: 注意，打印内容开头，必须添加start命令
- (XZPLCommand *)start;

/// 标签格式的结束。调用此方法后，即会打印标签
///
/// - Note: 注意，打印内容结束，必须添加end命令
- (XZPLCommand *)end;

/// 文本打印
///
/// 文本的字体类型，默认 ZPLFont26_13
///
/// @param x 文本的起始 x 值
/// @param y 文本的起始 y 值
/// @param content 文本内容
- (XZPLCommand *)addTextAtX:(int)x y:(int)y content:(NSString *)content;

/// 文本打印
///
/// @param x 文本的起始 x 值
/// @param y 文本的起始 y 值
/// @param fontName 文本的字体类型，默认 FNT_F
/// @param content 文本内容
- (XZPLCommand *)addTextAtX:(int)x
                 y:(int)y
          fontName:(NSString *)fontName
           content:(NSString *)content;

/// 文本打印
///
/// @param x 文本的起始 x 值
/// @param y 文本的起始 y 值
/// @param fontName 文本的字体类型，默认 FNT_F
/// @param sizeW 文字有效宽度，默认为基础尺寸。请使用基础尺寸的整数倍
/// @param sizeH 文字有效高度。默认为基础尺寸。请使用基础尺寸的整数倍
/// @param content 文本内容
- (XZPLCommand *)addTextAtX:(int)x
              y:(int)y
       fontName:(NSString *)fontName
          sizeW:(int)sizeW
          sizeH:(int)sizeH
        content:(NSString *)content;

/// 文本打印
///
/// @param x 文本的起始 x 值
/// @param y 文本的起始 y 值
/// @param fontName 文本的字体类型，默认 FNT_F
/// @param rotation 顺时针旋转角度，默认 ZPLRotation0
/// @param sizeW 文字有效宽度，默认为基础尺寸。请使用基础尺寸的整数倍
/// @param sizeH 文字有效高度。默认为基础尺寸。请使用基础尺寸的整数倍
/// @param content 文本内容
- (XZPLCommand *)addTextAtX:(int)x
              y:(int)y
       fontName:(NSString *)fontName
       rotation:(RotationZPL)rotation
          sizeW:(int)sizeW
          sizeH:(int)sizeH
        content:(NSString *)content;

/// 设置自定义字体
///
/// @param fontName 字库字体名
/// @param extension 字体名后缀
/// @param alias 字体别名，对应 addText 中的 fontName。范围:A 至 Z 和 0 至 9。
/// @param codePage 具体参见CodePageZPL枚举
- (XZPLCommand *)setCustomFont:(NSString *)fontName
            extension:(NSString *)extension
                alias:(NSString *)alias
             codePage:(CodePageZPL)codePage;

/// 设置打印宽度
///
/// @param width 纸张的宽度，单位为点
- (XZPLCommand *)setPrinterWidth:(int)width;

/// 设置标签长度
///
/// 发出设置标签长度后，在关闭打印机或发送新的设置标签长度命令之前此设置将保持不变
///
/// @param height 标签的长度，单位为点【1 至 32000，不超过最大标签尺寸】
- (XZPLCommand *)setLabelLength:(int)height;

/// 区域反显
///
/// @param x 区域的起始 x 值
/// @param y 区域的起始 y 值
/// @param width 区域宽度
/// @param height 区域高度
- (XZPLCommand *)addReverseAtX:(int)x
                 y:(int)y
             width:(int)width
            height:(int)height;

/// 区域反显
///
/// @param x 区域的起始 x 值
/// @param y 区域的起始 y 值
/// @param width 区域宽度
/// @param height 区域高度
/// @param radius 圆角程度，范围:0~8，默认为 0
- (XZPLCommand *)addReverseAtX:(int)x
                 y:(int)y
             width:(int)width
            height:(int)height
            radius:(int)radius;

/// 绘制矩形
///
/// @param x 矩形的起始 x 值
/// @param y 矩形的起始 y 值
/// @param width 矩形宽度
/// @param height 矩形高度
/// @param thickness 线条宽度
- (XZPLCommand *)addBoxAtX:(int)x
             y:(int)y
         width:(int)width
        height:(int)height
     thickness:(int)thickness;

/// 绘制矩形
/// 
/// @param x 矩形的起始 x 值
/// @param y 矩形的起始 y 值
/// @param width 矩形宽度
/// @param height 矩形高度
/// @param thickness 线条宽度
/// @param radius 圆角程度，范围:0~8， 默认为 0
- (XZPLCommand *)addBoxAtX:(int)x
             y:(int)y
         width:(int)width
        height:(int)height
     thickness:(int)thickness
        radius:(int)radius;


/// 此函数功能为绘制对角线
///
/// @param x 水平起始位置
/// @param y 垂直起始位置
/// @param orientation 对角线的方向
/// @param width 框的宽度 (范围：1-32000 ，单位：dot)
/// @param height 框的高度 (范围：1-32000 ，单位：dot)
/// @param thickness 边界厚度 (范围：1-32000 ，单位：dot)
- (XZPLCommand *)addGraphicDiagonalLineAtX:(int)x
                             y:(int)y
                   orientation:(DiagonalDirection)orientation
                         width:(int)width
                        height:(int)height
                     thickness:(int)thickness;


/// 此函数功能为绘制图形椭圆
///
/// @param x 水平起始位置
/// @param y 垂直起始位置
/// @param width 椭圆宽度 (范围：3-4095 ，单位：dot)
/// @param height 椭圆高度 (范围：3-4095 ，单位：dot)
/// @param thickness 边界厚度 (范围：2-4095 ，单位：dot)
- (XZPLCommand *)addGraphicEllipseAtX:(int)x
                        y:(int)y
                    width:(int)width
                   height:(int)height
                thickness:(int)thickness;

/// 此函数用于打印圆形
///
/// @param x 水平起始位置
/// @param y 垂直起始位置
/// @param diameter 圆的直径 (范围：3-4095 ，单位：dot)
/// @param thickness 边界厚度 (范围：1-4095 ，单位：dot)
- (XZPLCommand *)addGraphicCircleAtX:(int)x
                       y:(int)y
                diameter:(int)diameter
               thickness:(int)thickness;

/// 添加一维条码
///
/// @param x 条码起始 x 值
/// @param y 条码起始 y 值
/// @param codeType 条码类型，详细见具体的ZPLBarCodeType枚举类型
/// @param content 条码文本内容
- (XZPLCommand *)addBarcodeAtX:(int)x
                 y:(int)y
          codeType:(ZPLBarCodeType)codeType
           content:(NSString *)content;

/// 添加一维条码
///
/// @param x 条码起始 x 值
/// @param y 条码起始 y 值
/// @param codeType 条码类型，详细见具体的ZPLBarCodeType枚举类型
/// @param content 条码文本内容
/// @param height 条码高度，默认 50 点
- (XZPLCommand *)addBarcodeAtX:(int)x
                 y:(int)y
          codeType:(ZPLBarCodeType)codeType
           content:(NSString *)content
            height:(int)height;

/// 添加一维条码
///
/// @param x 条码起始 x 值
/// @param y 条码起始 y 值
/// @param codeType 条码类型，详细见具体的ZPLBarCodeType枚举类型
/// @param ratio 旋转角度
/// @param textPosition 文本位置，默认 ZPLHriTextBelow
/// @param content 条码文本内容
/// @param width 条码模块宽度,默认为 2 点
/// @param height 条码高度，默认 50 点
- (XZPLCommand *)addBarcodeAtX:(int)x
                 y:(int)y
          codeType:(ZPLBarCodeType)codeType
             ratio:(RotationZPL)ratio
      textPosition:(HriTextZPL)textPosition
           content:(NSString *)content
             width:(int)width
            height:(int)height;

/// 添加二维条码
///
/// @param x 二维码起始 x 值
/// @param y 二维码起始 y 值
/// @param factor 放大系数，范围 1~10，默认为 3
/// @param text 二维码内容
- (XZPLCommand *)addQRCodeAtX:(int)x y:(int)y factor:(int)factor text:(NSString *)text;

/// 打印图片
///
/// @param x 图片起始 x 值
/// @param y 图片起始 y 值
/// @param image 图片对象
- (XZPLCommand *)printImageAtX:(int)x y:(int)y image:(UIImage *)image;

/// 打印图片
///
/// @param x 图片起始 x 值
/// @param y 图片起始 y 值
/// @param wRatio 宽度缩放比例，范围1~10
/// @param hRatio 高度缩放比例，范围1~10
/// @param image 图片对象
- (XZPLCommand *)printImageAtX:(int)x y:(int)y wRatio:(int)wRatio hRatio:(int)hRatio image:(UIImage *)image;

/// 下载图形
/// @param source 存储图像的源设备，默认使用DeviceTypeR，可选类型参见ZPLDeviceType
/// @param name 存储图像的名称。接受的值：1 至 8 个字母数字字符。如果未指定名称，则使用 UNKNOWN
/// @param image 图片对象
- (XZPLCommand *)downloadGraphic:(ZPLDeviceType)source name:(NSString *)name image:(UIImage *)image;

/// 调用图形
/// @param x 图片起始 x 值
/// @param y 图片起始 y 值
/// @param source 存储图像的源设备，默认使用DeviceTypeR，可选类型参见ZPLDeviceType
/// @param name 下载图片时取得名称和拓展名
/// @param mx x 轴方向的放大系数，默认值为 1，范围为 1~10
/// @param my y 轴方向的放大系数，默认值为 1，范围为 1~10
- (XZPLCommand *)printGraphicAtX:(int)x
                   y:(int)y
              source:(ZPLDeviceType)source
                name:(NSString *)name
                  mx:(int)mx
                  my:(int)my;

/// 删除已下载的图形
/// @param source 存储图像的源设备，默认使用DeviceTypeR，可选类型参见ZPLDeviceType
/// @param name 存储图像的名称。接受的值：1 至 8 个字母数字字符。如果未指定名称，则使用 UNKNOWN
- (XZPLCommand *)deleteDownloadGraphic:(ZPLDeviceType)source name:(NSString *)name;

/// 设置打印数量
///
/// @param count 标签数量
- (XZPLCommand *)addPrintCount:(int)count;

/// 设置打印速度
///
/// @param speed 打印速度。单位为 inches/sec 1~14
- (XZPLCommand *)setPrintSpeed:(int)speed;

/// 该方法用于将标签格式反转 180 度
///
/// @param n 反转标签 YES=正常 NO=反转 默认值:YES
- (XZPLCommand *)direction:(BOOL)n;

/// 设置打印的浓度
///
/// @param density 打印浓度(范围: 0-30)
- (XZPLCommand *)setPrintDensity:(int)density;


@end

