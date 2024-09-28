//
//  XPOSCommand.h
//  PrinterSDK
//
//  Created by max on 2024/5/18.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "XConstants.h"

NS_ASSUME_NONNULL_BEGIN

@interface XPOSCommand : NSObject

#pragma mark - Basic related APIs

/// 获得打印命令
///
/// 将获取当前esc对象的打印数据
- (NSData*)getCommand;

/// 添加自定义数据
///
/// @param customData 自定义的数据内容
- (XPOSCommand *)addData:(NSData *)customData;

/// 设置字符编码
///
/// @param encoding 编码格式，默认使用GB_18030_2000
- (XPOSCommand *)setCharEncoding:(NSStringEncoding)encoding;

/// 初始化打印机
///
/// 清除打印缓冲区数据，打印模式被设为上电时的默认值模式
///
- (XPOSCommand *)initializePrinter;

/// 打印并换行
///
/// 将打印缓冲区中的数据打印出来，并且按照当前行间距，把打印纸向前推进一行
///
- (XPOSCommand *)lineFeed;

/// 打印并向前走纸n行
///
/// 打印缓冲区里的数据并向前走纸 n行（字符行）
///
/// @param lines 行数
///
- (XPOSCommand *)printAndFeedLines:(int)lines;

/// 水平定位
///
/// 移动打印位置到下一个水平定位点的位置
///
- (XPOSCommand *)setHorizontalTab;

/// 选择对齐方式
/// @param alignment 对齐方式
- (XPOSCommand *)selectAlignment:(POSAlignment)alignment;

#pragma mark - Text related APIs

/// 添加文字
///
/// 默认使用字符串编码格式为 GB_18030_2000
///
/// @param text 文本内容
- (XPOSCommand *)addText:(NSString *)text;

/// 设置文字大小
///
/// 将打印文本的字符宽高进行倍数放大
///
/// @param textSize 打印的文本字体大小 TextWidth1 | TextHeight1
- (XPOSCommand *)selectTextSize:(int)textSize;

#pragma mark - 复合添加文字（支持对齐/文本属性/字符宽度/字符高度）

/// 添加文字
///
/// 默认使用字符串编码格式为 GB_18030_2000
///
/// @param text 字符宽度比
/// @param align 文本的对齐方式，默认为 POSAlignmentLeft
/// @param attribute 文本的属性，默认为 FntDefault
/// @param textSize TextWidth1 | TextHeight1
- (XPOSCommand *)addText:(NSString *)text alignment:(POSAlignment)align attribute:(POSFontType)attribute textSize:(int)textSize;

/// 添加文字
///
/// 默认使用字符串编码格式为 GB_18030_2000
///
/// @param text 字符宽度比
/// @param textSize TextWidth1 | TextHeight1
- (XPOSCommand *)addTextSize:(NSString *)text textSize:(int)textSize;

/// 添加文字
///
/// 默认使用字符串编码格式为 GB_18030_2000
///
/// @param text 字符宽度比
/// @param attribute 文本的属性，默认为 FntDefault
- (XPOSCommand *)addTextAttribute:(NSString *)text attribute:(POSFontType)attribute;

/// 添加文字
///
/// 默认使用字符串编码格式为 GB_18030_2000
///
/// @param text 字符宽度比
/// @param align 文本的对齐方式，默认为 POSAlignmentLeft
- (XPOSCommand *)addTextAlignment:(NSString *)text alignment:(POSAlignment)align;

/// 选择字体
/// @param font FontStandardASCII:选择标准ASCII码标准字体(12 x 24),FontCompressedASCII:选择压缩ASCII码字体(9 x 17)
///
- (XPOSCommand *)selectFont:(FontSelection)font;

/// 选择国际字符集
/// @param charset 字符集编号(0~15)，详细参考POSCharacterSet对应国家字符集
///
- (XPOSCommand *)selectCharacter:(POSCharacterSet)charset;

/// 选择/取消下划线模式
///
/// 根据 n的值选择或取消下划线模式
///
/// @param mode 模式
///
- (XPOSCommand *)selectOrCancelUnderlineMode:(int)mode;

/// 设置默认行间距
///
/// 选择约  3.75mm  行间距
///
- (XPOSCommand *)setDefaultLineSpacing;

/// 设置行间距
///
/// 设置行间距为  [ n × 纵向或横向移动单位 ] 英寸
///
/// @param spacing 间距
///
- (XPOSCommand *)setLineSpacing:(int)spacing;

/// 选择/取消加粗模式
///
/// @param mode 模式
///
- (XPOSCommand *)selectOrCancelBoldMode:(int)mode;

/// 设置字符右间距
///
/// 设置字符的右间距为 [n×横向移动单位或纵向移动单位 ]英寸
///
/// @param spacing 间距
///
- (XPOSCommand *)setCharacterRightSpacing:(int)spacing;

#pragma mark - Image related APIs

/// 打印图片
///
/// @param image 图像源
/// @param type 图片效果:二值化，抖动算法
/// @param mode 图片缩放模式：正常/宽双倍/搞双倍/宽高双倍
- (XPOSCommand *)printImage:(UIImage *)image type:(BMPType)type mode:(BmpScaleType)mode;

/// 通过压缩算法打印图片
///
/// 仅部分支持压缩算法的机型支持该方法，否则可能出现打印乱码
///
/// @param image 图像源
/// @param type 图片效果:二值化，抖动算法
/// @param mode 图片缩放模式：正常/宽双倍/搞双倍/宽高双倍
- (XPOSCommand *)compressionPrintImage:(UIImage *)image type:(BMPType)type mode:(BmpScaleType)mode;

/// 选择位图模式
///
/// 选择由  m 指定的一种位图模式，位图点数由 nL和nH确定
///
/// @param mode 位图模式
/// @param width 宽度
/// @param image 位图
///
- (XPOSCommand *)selectBitmapMode:(int)mode width:(int)width image:(UIImage *)image;

/// 定义 Flash 位图
///
/// - Note:1.在打印机里，flash下载空间最大为 8k bytes，该命令可以定义下载多幅Flash位图，但不能定义一幅大小超过8k bytes的位图 \
/// 2.注意不同的打印机下载空间也不相同，以上仅是参考，具体参照打印机配置信息 \
/// 3.频繁执行该命令可能会损坏Flash存储器，推荐每天最多些Flash 10次 \
///
/// @param images 包含位图的数组
- (XPOSCommand *)definedFlashBmpWithImage:(NSArray <UIImage *> *)images;

/// 打印下载到 FLASH 中的位图
///
/// 以m指定的模式打印下载到 FLASH中的位图
///
/// @param n 模式
/// @param m 模式
- (XPOSCommand *)printBitmapToFlashWithN:(int)n andM:(int)m;

/// 清除 Flash 存储的bmp
///
/// 该指令会清除所有存储在Flash上的bmp
- (XPOSCommand *)clearFlashBmp;

/// 定义下载到 RAM 的位图
///
/// - Note: 下载的位图在打印机复位或者关闭电源下会被清除
///
/// @param image 位图图像
/// @param type 图片效果
- (XPOSCommand *)defineDownloadedRAMBmp:(UIImage *)image bmpType:(BMPType)type;

/// 打印下载到 RAM 的位图
///
/// 打印一幅下载位图，打印模式：正常/倍宽/倍高/倍宽和倍高
///
/// @param mode 模式参数
- (XPOSCommand *)printDownloadRAMBmp:(BmpScaleType)mode;

#pragma mark - Barcode related APIs

/// 打印条码
/// @param type 条码类型
/// @param content 条码内容
- (XPOSCommand *)printBarcodeWithType:(BarcodeType)type andContent:(NSString *)content;

/// 选择 HRI 字符的打印位置
/// @param position 位置参数
- (XPOSCommand *)selectHRICharacterPrintPosition:(NSInteger)position;

/// 选择 HRI 使用字体
/// @param font 字体参数
- (XPOSCommand *)selectHRIFont:(NSInteger)font;

/// 选择条码高度
/// @param height 条码高度
- (XPOSCommand *)selectBarcodeHeight:(NSInteger)height;

/// 设置条码宽度
/// @param width 条码宽度
- (XPOSCommand *)setBarcodeWidth:(NSInteger)width;

#pragma mark - Qrcode related APIs

/// 打印二维码
///
/// @param content 二维码内容
- (XPOSCommand *)printQRCodeWithContent:(NSString *)content;

/// 打印二维码
///
/// @param content 二维码内容
/// @param moduleSize 单元大小，范围【1，16】,默认值 8
- (XPOSCommand *)printQRCodeWithContent:(NSString *)content moduleSize:(NSInteger)moduleSize;

/// 打印二维码
///
/// @param content 二维码内容
/// @param moduleSize 单元大小，范围【1，16】,默认值 8
/// @param ecLevel 错误纠正等级, 默认值为 QRErrorCorrectionLevelL
- (XPOSCommand *)printQRCodeWithContent:(NSString *)content moduleSize:(NSInteger)moduleSize ecLevel:(QRErrorCorrectionLevel)ecLevel;


#pragma mark -  模式相关 related APIs

/// 打印并回到标准模式（在页模式下）
///
/// 在页模式下将打印缓冲区中的数据全部打印出来并返回标准模式
///
- (XPOSCommand *)formFeed;

/// 页模式下取消打印数据
///
/// 在页模式下，删除当前打印区域中的所有打印数据
///
- (XPOSCommand *)cancelPrintData;

/// 页模式下打印
///
/// 页模式下，打印缓冲区的所有所有内容
///
- (XPOSCommand *)pageModePrint;

/// 选择页模式
///
/// 从标准模式转换到页模式
///
- (XPOSCommand *)selectPageMode;

/// 选择标准模式
///
/// 设置标准模式
///
- (XPOSCommand *)selectStandardMode;

/// 在页模式下选择打印区域方向
///
/// @param direction 方向
///
///
- (XPOSCommand *)selectPrintDirection:(int)direction;

/// 设置绝对打印位置
///
/// 将当前位置设置到距离行首（ nL + nH×2 56）× ( 横向或纵向移动单位 )处
///
/// @param nL 低位
/// @param nH 高位
- (XPOSCommand *)setAbsolutePrintPositionWithLow:(int)nL high:(int)nH;

/// 打印并走纸
///
/// 打印缓冲区数据并走纸   [ n × 纵向或横向移动单位] 英寸
///
/// @param lines 行数
///
- (XPOSCommand *)printAndFeedPaper:(int)lines;

/// 选择/取消顺时针旋转90度
///
/// rotation:0，48表示取消顺时针旋转90度，rotation：1，49表示选择顺时针旋转90度
///
/// @param rotation 旋转标志
///
///
- (XPOSCommand *)selectOrCancelRotation:(int)rotation;

/// 页模式下设置打印区域
///
/// @param x 横向起始位置，默认为 0
/// @param y 纵向起始位置，默认为 0
/// @param width 区域宽度
/// @param height 区域高度
- (XPOSCommand *)setPrintArea:(int)x y:(int)y width:(int)width height:(int)height;

/// 允许/禁止按键
/// @param flag 标志
- (XPOSCommand *)enableOrDisableKeys:(int)flag;

/// 选择字符代码表
///
/// 从字符代码表中选择页
///
/// @param charset 代码页编号，详见CharacterCodePage
- (XPOSCommand *)selectCodePage:(CharacterCodePage)charset;

/// 选择/取消倒置打印模式
/// @param mode 模式
- (XPOSCommand *)selectOrCancelInvertedPrint:(int)mode;

/// 设置相对横向打印位置
///
/// 打印起始位置从当前位置移动到【x * 横向移动单位或者纵向移动单位】
///
/// @param xPosition 横向相对位移
- (XPOSCommand *)setRelativeHorizontal:(int)xPosition;

/// 页模式下设置纵向绝对位置
///
/// @param yPosition 纵向绝对位置
- (XPOSCommand *)setAbsoluteVertical:(NSInteger)yPosition;

/// 页模式下设置纵向相对位置
///
/// @param yPosition 纵向相对位置
- (XPOSCommand *)setRelativeVertical:(NSInteger)yPosition;

/// 设置横向和纵向移动单位
/// @param x 横向移动单位
/// @param y 纵向移动单位
- (XPOSCommand *)setMotionUnitsWithHorizontal:(NSInteger)x vertical:(NSInteger)y;

/// 选择/取消黑白反显打印模式
/// @param mode 模式参数
- (XPOSCommand *)selectCancelBWReversePrintMode:(NSInteger)mode;

/// 设置左边距
/// @param left 左边距
- (XPOSCommand *)setLeftMargin:(NSInteger)left;

/// 选择切纸模式并切纸
///
/// 切纸模式:默认半切
- (XPOSCommand *)cutPaper;

/// 选择切纸模式并切纸
///
/// @param mode 切纸模式:默认半切
- (XPOSCommand *)cutPaperWithMode:(PaperCutMode)mode;

/// 选择切纸模式并切纸
///
/// @param distance 走纸距离，进纸 distance ×（纵向移动单位）英寸 并且半切纸
- (XPOSCommand *)cutPaperWithDistance:(NSInteger)distance;

/// 设置打印区域宽度
///
/// @param width 打印区域宽度
- (XPOSCommand *)setPrintAreaWidth:(int)width;


#pragma mark -  状态 related APIs

/// 实时状态传送
///
/// 实时传送打印机状态，status 用来指定所要传送的打印机状态
///
/// @param status 状态
///
- (XPOSCommand *)realTimeStatus:(PrinterAllStatusType)status;

/// 返回状态
/// @param statusType 状态类型
- (XPOSCommand *)returnStatus:(NSInteger)statusType;

#pragma mark -  蜂鸣器/警报 related APIs

/// 打印机来单打印蜂鸣提示
///
/// @param count 蜂鸣器鸣叫次数，范围(1~9)
/// @param time 每次鸣叫的时间，范围(1~9)，每次鸣叫时间为 time *50ms
- (XPOSCommand *)printerBeep:(NSInteger)count time:(NSInteger)time;

/// 打印机来单打印蜂鸣提示及报警灯闪烁
///
/// @param count 范围1～20,指报警灯闪烁次数或蜂鸣器鸣叫次数
/// @param interval 范围1～20 ，指报警灯闪烁间隔时间为 interval *50ms，或者蜂鸣器鸣叫时间为 interval *50ms
/// @param mode mode 模式
- (XPOSCommand *)printerBeepAndFlashAlarm:(NSInteger)count count:(NSInteger)interval time:(AlarmState)mode;

/// 这个方法用于打开钱箱抽屉
///
/// @param pinNum 连接的引脚值，详细参见CashDrawerPin
- (XPOSCommand *)openCashBoxWithPinNumber:(CashDrawerPin)pinNum;

/// 这个方法用于打开钱箱抽屉
///
/// @param pinNum 连接的引脚值，详细参见CashDrawerPin
/// @param onTime 钱箱产生脉冲开始时间 onTime*2ms，范围【0，255】。默认值为 30
/// @param offTime 钱箱产生脉冲结束时间 offTime*2ms，范围【0，255】，默认值为 255 如果 onTime>offTime，结束时间为 onTime*2ms
- (XPOSCommand *)openCashBoxWithPinNumber:(CashDrawerPin)pinNum onTime:(int)onTime offTime:(int)offTime;

@end

NS_ASSUME_NONNULL_END
