//
//  XTSPLCommand.h
//  PrinterSDK
//
//  Created by max on 2024/5/18.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "XConstants.h"

@interface XTSPLCommand : NSObject

/// 获得打印命令
///
/// 将获取当前TSPL对象的打印数据
- (NSData*)getCommand;

/// 设置字符编码
///
/// @param encoding 编码格式
- (XTSPLCommand *)setCharEncoding:(NSStringEncoding)encoding;

/// 添加自定义数据
///
/// @param customData 自定义的数据内容
- (XTSPLCommand *)addData:(NSData *)customData;

#pragma mark - Size Commands

/// 设置标签的尺寸
///
/// 尺寸单位为英寸
///
/// @param width 尺寸宽度
/// @param height 尺寸高度
- (XTSPLCommand *)sizeInch:(double)width height:(double)height;

/// 设置标签的尺寸
///
/// 尺寸单位为 mm
///
/// @param width 尺寸宽度
/// @param height 尺寸高度
- (XTSPLCommand *)sizeMm:(double)width height:(double)height;

#pragma mark - Gap Command

/// 定义两张标签纸中间的间隙高度
///
/// 单位为英寸
///
/// @param m 间隙高度
/// @param n 间隙高度的补偿值
- (XTSPLCommand *)gapInch:(double)m n:(double)n;

/// 定义两张标签纸中间的间隙高度
///
/// 单位为毫米
///
/// @param m 间隙高度
/// @param n 间隙高度的补偿值
- (XTSPLCommand *)gapMm:(double)m n:(double)n;

#pragma mark - Speed and Density Commands

/// 设置打印机打印速度
///
/// 每秒的打印速度，以英寸计算
///
/// @param speed 打印速度
- (XTSPLCommand *)speed:(double)speed;

/// 设置打印机打印浓度
///
/// 浓度, 范围【0, 15】
///
/// @param density 浓度
- (XTSPLCommand *)density:(int)density;

#pragma mark - Control Commands

/// 清空打印缓冲区
///
/// 清除打印机缓冲区并将打印机设置为初始状态
- (XTSPLCommand *)cls;

/// 设置标签纸的偏移量
///
/// 单位为英寸
///
/// @param offset 偏移量
- (XTSPLCommand *)offsetInch:(double)offset;

/// 设置标签纸的偏移量
///
/// 单位为毫米
///
/// @param offset 偏移量
- (XTSPLCommand *)offsetMm:(double)offset;

/// 设置打印机打印方向
/// 
/// @param direction 打印的方向
- (XTSPLCommand *)direction:(DirectionTSPL)direction;

/// 设置打印机打印方向，可以设置是否镜像
///
/// @param direction 打印的方向
/// @param isMirror 是否镜像
- (XTSPLCommand *)direction:(DirectionTSPL)direction isMirror:(BOOL)isMirror;

/// 向前走纸
///
/// 将标签纸推进对应的长度
///
/// @param length 走纸长度，单位为点。范围【1，9999】
- (XTSPLCommand *)feed:(int)length;

/// 定义标签纸的原点坐标
///
/// @param x 水平坐标 单位为点
/// @param y 垂直坐标，单位为点
- (XTSPLCommand *)referenceAtX:(int)x y:(int)y;

///  移动标签图像的垂直位置
///
/// @param n 标签图像的纵坐标，单位为dot，最大可设置尺寸为 1 inch
- (XTSPLCommand *)shift:(int)n;

#pragma mark - Print Commands

/// 在指定位置打印长条
///
/// @param x 长条起始横坐标，单位为点
/// @param y 长条起始纵坐标，单位为点
/// @param width 长条宽度，单位为点
/// @param height 长条高度，单位为点
- (XTSPLCommand *)barAtX:(int)x andY:(int)y width:(int)width height:(int)height;

/// 在指定位置打印方框
///
/// @param x 方框左上角x坐标
/// @param y 方框左上角y坐标
/// @param width 方框宽度
/// @param height 方框高度
/// @param thickness 边框厚度
- (XTSPLCommand *)boxAtX:(int)x y:(int)y width:(int)width height:(int)height thickness:(int)thickness;

/// 绘制一个椭圆
/// @param x 指定左上角的 X 坐标 (单位 DOT)
/// @param y 指定左上角的 Y 坐标 (单位 DOT)
/// @param width 指定椭圆的宽 (单位 DOT)
/// @param height 指定椭圆的高 (单位 DOT)
/// @param thickness 椭圆的线条粗细 (单位 DOT)
- (XTSPLCommand *)ellipseAtX:(int)x andY:(int)y andWidth:(int)width andHeight:(int)height andThickness:(int)thickness;

/// 标签回退
///
/// 将标签纸向后回拉指定的长度
///
/// @param length 回拉长度，单位为点。范围【1，9999】
- (XTSPLCommand *)backFeed:(int)length;

/// 打印并向前走纸到下一张标签
///
/// 将标签纸向前推送一张标签纸的距离
- (XTSPLCommand *)formFeed;

/// 打印并向前走纸到标签起始位置
///
/// 对标签位置进行校准
- (XTSPLCommand *)home;

/// 打印标签
///
/// 此条指令用于将打印机中图像缓存印出，默认打印1张，不重打
- (XTSPLCommand *)print;

/// 打印标签
///
/// 此条指令用于将打印机中图像缓存印出
/// @param m 指定打印多少组标签
/// @param n 每一组标签打印多少份
- (XTSPLCommand *)print:(int)m n:(int)n;

#pragma mark - barcode Commands

/// 在指定位置打印条码
/// @param x 条码起始点横坐标，单位为点
/// @param y 条码起始点纵坐标，单位为点
/// @param codeType 条码类型，可选类型 参考XConstants.h中的 Barcode Code Types
/// @param height 条码高度，单位为点
/// @param readable 是否打印可识别字符， 默认 ReadableTypeLeft，显示在左边
/// @param narrow 窄条码比例因子,单位为点， 默认为 2
/// @param wide 宽条码比例因子,单位为点，默认为 2
/// @param content 条码内容
- (XTSPLCommand *)barcodeAtX:(int)x
              y:(int)y
       codeType:(NSString *)codeType
         height:(int)height
       readable:(ReadableType)readable
    andRotation:(TSPLRotation)rotation
         narrow:(int)narrow
           wide:(int)wide
        content:(NSString *)content;

/// 绘制 CODABLOCK F 类型条码
///
/// CODABLOCK条码的模块的高度 (默认为 8)，CODABLOCK 窄条码比例因子宽度 (单位 DOT，默认为 2)
///
/// @param x 指定 X 坐标
/// @param y 指定 Y 坐标
/// @param rotation 旋转角度
/// @param content CODABLOCK 条码内容
- (XTSPLCommand *)codaBlockFAtX:(int)x andY:(int)y andRotation:(TSPLRotation)rotation andContent:(NSString *)content;

#pragma mark - Sound and Code Page Commands

/// 设置打印机的国际代码页
///
/// @param code 代码页名称，参考XConstants.h中的codepage code
- (XTSPLCommand *)codePage:(NSString *)code;

/// 设置打印机蜂鸣器鸣叫次数和间隔
///
/// @param level 声音大小: 0~9
/// @param interval 声音间隔: 1~4095
- (XTSPLCommand *)sound:(int)level interval:(int)interval;

#pragma mark - Set Commands

/// 选择国际字符集
///
/// 可用的字符集，参考XConstants.h中的country code
- (XTSPLCommand *)country:(NSString *)code;

#pragma mark - Limit Feed Commands

/// 限制向前走纸
/// @param length 限定长度
- (XTSPLCommand *)limitFeedInch:(double)length;

/// 限制向前走纸
/// @param length 限定长度
- (XTSPLCommand *)limitFeedMm:(double)length;

#pragma mark - Bitmap Commands

/// 打印位图
/// @param x 位图左上角x坐标
/// @param y 位图左上角y坐标
/// @param mode 位图模式：仅支持这三种模式:BMPModeOverwrite，BMPModeOR，BMPModeXOR
/// @param image 位图对象
- (XTSPLCommand *)bitmapAtX:(int)x y:(int)y mode:(BMPMode)mode image:(UIImage *)image;

/// 通过压缩传送图片到打印机，仅适用部分机型
///
/// - Note:仅支持部分机型，使用该指令时，请确认当前打印机是否支持压缩图片发送
///
/// @param x 位图左上角x坐标
/// @param y 位图左上角y坐标
/// @param mode 位图模式：仅支持这三种模式:BMPModeOverwriteZlib,BMPModeORZlib,BMPModeXORZlib,其他模式下默认不压缩
/// @param image 位图对象
- (XTSPLCommand *)zlibBitmapAtX:(int)x y:(int)y mode:(BMPMode)mode image:(UIImage *)image;


/// 打印 BMP 格式的图像
///
/// @param x BMP 图片的 X 坐标
/// @param y BMP 图片的 Y 坐标
/// @param filename 所下载的 BMP 图片名称 (支持 ZPL *.GRF 档案)
- (XTSPLCommand *)putBmpAtX:(int)x andY:(int)y andFileName:(NSString *)filename;

/// 打印 BMP 格式的图像
///
/// @param x BMP 图片的 X 坐标
/// @param y BMP 图片的 Y 坐标
/// @param filename 所下载的 BMP 图片名称 (支持 ZPL *.GRF 档案)
/// @param contrast 灰度对比率 默认为 80 建议选择范围在 60 至 100 之间
- (XTSPLCommand *)putBmpAtX:(int)x andY:(int)y andFileName:(NSString *)filename contrast:(int)contrast;

/// 打印 PCX 格式的图像
///
/// @param x PCX 图片的 X 坐标
/// @param y PCX 图片的 Y 坐标
/// @param filename 所下载的 PCX 图片的名称(区分大小写)
- (XTSPLCommand *)putPcxAtX:(int)x andY:(int)y andFileName:(NSString *)filename;

#pragma mark - QR Code Commands

/// 在指定位置打印二维码
///
/// @param x 二维码左上角x坐标
/// @param y 二维码左上角y坐标
/// @param ecclevel 纠错级别：kECLevelL:7%，kECLevelM:15%，kECLevelQ:25%，kECLevelH:30%
/// @param cellwidth 二维码单元格大小，范围【1，10】
/// @param mode 二维码编码模式：kQRCodeModeAuto:自动生成编码,kQRCodeModeManual:手动生成编码
/// @param rotation 旋转角度【0，90，180，270】
/// @param content 二维码内容
- (XTSPLCommand *)qrCodeAtX:(int)x
          andY:(int)y
       ecLevel:(NSString *)ecclevel
     cellWidth:(int)cellwidth
          mode:(NSString *)mode
      rotation:(TSPLRotation)rotation
          content:(NSString *)content;

/// 绘制 DataMatrix 二维条码
///
/// @param x 指定 X 坐标 (单位 DOT)
/// @param y 指定 Y 坐标 (单位 DOT)
/// @param width 条码区域宽度 (单位 DOT)
/// @param height 条码区域高度 (单位 DOT)
/// @param content DataMatrix 数据内容
- (XTSPLCommand *)dataMatrixAtX:(int)x
           andY:(int)y
          width:(int)width
         height:(int)height
           content:(NSString *)content;

/// 绘制 PDF417 二维条码
///
/// @param x 指定 X 坐标 (单位 DOT)
/// @param y 指定 Y 坐标 (单位 DOT)
/// @param width 预计宽度 (单位 DOT)
/// @param height 预计高度 (单位 DOT)
/// @param rotate 逆时针方向旋转(0,90,180,270)
/// @param content PDF417 条码数据内容
- (XTSPLCommand *)pdf417AtX:(int)x
             y:(int)y
         width:(int)width
        height:(int)height
        rotate:(TSPLRotation)rotate
       content:(NSString *)content;


#pragma mark - Text Commands

/// 在指定位置打印文本
///
/// @param x 文本左上角x坐标
/// @param y 文本左上角y坐标
/// @param font 字体名称，可用的字体名称，参考XConstants.h的Font name
/// @param content 文本内容
- (XTSPLCommand *)textAtX:(int)x y:(int)y font:(NSString *)font content:(NSString *)content;

/// 在指定位置打印文本
///
/// @param x 文本左上角x坐标
/// @param y 文本左上角y坐标
/// @param font 字体名称，可用的字体名称，参考XConstants.h的Font name
/// @param xRatio 文字横向放大倍数，范围【1，10】
/// @param yRatio 字体纵向放大倍数，范围【1，10】
/// @param content 文本内容
- (XTSPLCommand *)textAtX:(int)x y:(int)y font:(NSString *)font xRatio:(int)xRatio yRatio:(int)yRatio content:(NSString *)content;

/// 在指定位置打印文本
/// 
/// @param x 文本左上角x坐标
/// @param y 文本左上角y坐标
/// @param font 字体名称，可用的字体名称，参考XConstants.h的Font name
/// @param rotation 旋转角度【0，90，180，270】
/// @param xRatio 文字横向放大倍数，范围【1，10】
/// @param yRatio 字体纵向放大倍数，范围【1，10】
/// @param content 文本内容
- (XTSPLCommand *)textAtX:(int)x y:(int)y font:(NSString *)font rotation:(TSPLRotation)rotation xRatio:(int)xRatio yRatio:(int)yRatio content:(NSString *)content;

/// 在指定位置打印文本段落
///
/// @param x 文本的 X 起始坐标
/// @param y 文本的 Y 起始坐标
/// @param width 文本的 Y 起始坐标
/// @param height 文本的 Y 起始坐标
/// @param font 字体名称,可选通用名称，参考XConstants.h中的Font name
/// @param rotaion 文本旋转方向(0,90,180,270)
/// @param x_mul 水平放大比率，最大放大 10 倍，范围【1，10】
/// @param y_mul 垂直放大比率,最大放大 10 倍，范围【1，10】
/// @param content 文本内容
- (XTSPLCommand *)textBlockAtX:(int)x
                 y:(int)y
               width:(int)width
              height:(int)height
                font:(NSString *)font
             rotaion:(TSPLRotation)rotaion
               x_mul:(int)x_mul
               y_mul:(int)y_mul
          content:(NSString *)content;

#pragma mark - Erase and Reverse Commands

/// 擦除指定区域内容
/// @param x 区域左上角x坐标
/// @param y 区域左上角y坐标
/// @param width 区域宽度
/// @param height 区域高度
- (XTSPLCommand *)eraseAtX:(int)x y:(int)y width:(int)width height:(int)height;

/// 反白打印指定区域内容
/// @param x 区域左上角x坐标
/// @param y 区域左上角y坐标
/// @param width 区域宽度
/// @param height 区域高度
- (XTSPLCommand *)reverseAtX:(int)x y:(int)y width:(int)width height:(int)height;

#pragma mark - Cut and Peel Commands

/// 执行切纸操作
- (XTSPLCommand *)cut;

/// 设置剥离模式
/// @param isOpen 是否打开剥离模式
- (XTSPLCommand *)setPeel:(BOOL)isOpen;

/// 设置撕纸模式
/// @param isOpen 是否打开撕纸模式
- (XTSPLCommand *)setTear:(BOOL)isOpen;

/// 设置切刀工作模式
///
/// ```objc
///  [self setCutter:0] // 关闭裁刀功能
///  [self setCutter:-1] // 设置打印机在整个打印任务全部结束后再裁切
///  [self setCutter:1] //设置一次裁切1张标签
/// ````
///
/// @param pieces 0:关闭裁刀功能,-1:设置打印机在整个打印任务全部结束后再裁切,pieces >= 1:设置一次裁切多少张标签 1<= pieces <=65535
- (XTSPLCommand *)setCutter:(int)pieces;
#pragma mark - Bline Commands

/// 设置黑标间距
///
/// 设定黑标高度及使用者定义标签印完后标签额外送出的长度，单位为英寸
///
/// @param m 黑标高度，范围：【0.1， 1】英尺 或【2.54，25.4】毫米
/// @param n 额外送出纸张长度。范围【0， lable length】
- (XTSPLCommand *)blineInch:(double)m n:(double)n;

/// 设置黑标间距
///
/// 设定黑标高度及使用者定义标签印完后标签额外送出的长度，单位为mm
///
/// @param m 黑标高度，范围：【0.1， 1】英尺 或【2.54，25.4】毫米
/// @param n 额外送出纸张长度。范围【0， lable length】
- (XTSPLCommand *)blineMm:(double)m n:(double)n;


#pragma mark - Other Commands

/// 间隙校准
///
/// 通过间隙传感器将纸张送出，以确定纸张和间隙的大小
- (XTSPLCommand *)gapDetect;

/// 黑标校准
///
/// 通过纸张及黑标通过黑标感测器时所侦测到的强度差异,来区分定义纸张及黑标的大小
- (XTSPLCommand *)blinedDetect;

/// 自动校准
///
/// 通过纸张及间隙/黑标通过间隙感测器/黑标感测器时所侦测到的强度差异,来区分定义纸张及黑标的大小
- (XTSPLCommand *)autoDetect;

/// 此条指令会将打印机恢复至出厂设置，注意使用
///
/// - Note:注意：请跟XESCCommand的initializePrinter方法做区别
- (XTSPLCommand *)initialPrinter;

/// 此命令可以将 DRAM 中的文件移动到 FLASH 中
- (XTSPLCommand *)move;

/// 此命令将会让打印机打印出当前的总记忆体容量及可用记忆体容量(包含 FLASH 及 DRAM)
- (XTSPLCommand *)files;

/// 删除 DRAM 中的文件
///
/// ```objc
///  [self killDRAM:@"FILENAME"] // 删除 DRAM 中的对应文件
///  [self killDRAM:@"*.PCX"] // 删除 DRAM 中的所有 PCX 文件
///  [self killDRAM:@"*"] // 删除 DRAM 中所有文件
/// ```
/// @param filename 文件名
- (XTSPLCommand *)killDRAM:(NSString *)filename;

/// 删除内置 FLASH 中的文件
///
/// ```objc
///  [self killFLASH:@"FILENAME"] // 删除 FLASH 中的对应文件
///  [self killFLASH:@"*.PCX"] // 删除 FLASH 中的所有 PCX 文件
///  [self killFLASH:@"*"] // 删除 FLASH 中所有文件
/// ````
/// @param filename 文件名
- (XTSPLCommand *)killFLASH:(NSString *)filename;

/// 设定打印机自动返回信息
///
/// @param mode 模式选项：ON/OFF/BATCH
- (XTSPLCommand *)autoResponse:(AutoResMode)mode;

@end

