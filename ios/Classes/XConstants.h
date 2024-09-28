//
//  XConstants.h
//  PrinterSDK
//
//  Created by max on 2024/5/18.
//

#import <Foundation/Foundation.h>

#pragma mark - Common ENUM

/// 标签指令类型
typedef NS_ENUM(NSInteger, PrintCommandType) {
    PrintCommandTsplPrint = 0,   ///< TSPL 打印指令 (TSPL print command)
    PrintCommandZplPrint,        ///< ZPL 打印指令 (ZPL print command)
    PrintCommandCpclPrint,       ///< CPCL 打印指令 (CPCL print command)
};


/// 图像效果
typedef NS_ENUM (NSUInteger,BMPType) {
    BMPThreshold,  ///< 二值法
    BMPDithering,  ///< 抖动算法
};

#pragma mark - ESC&POS ENUM

/// 票据内容对齐方式
typedef NS_ENUM(NSInteger, POSAlignment) {
    POSAlignmentLeft = 0,       ///< 左对齐 (Left alignment)
    POSAlignmentCenter,         ///< 居中对齐 (Center alignment)
    POSAlignmentRight           ///< 右对齐 (Right alignment)
};


typedef NS_ENUM(NSInteger, POSFontType) {
    FntDefault = 0,   /// 标准字体
    FntFontB,         /// FontB 字体
    FntBold,          /// 粗字体
    FntReverse,       /// 反打印属性
    FntUnderline,     /// 下划线属性
    FntUnderline2     /// 粗下划线属性
};

typedef NS_ENUM(NSUInteger, FontSelection) {
    FontStandardASCII = 0, // n = 0, 48 选择标准ASCII码标准字体(12 x 24)
    FontCompressedASCII = 1 // n = 1, 49 选择压缩ASCII码字体(9 x 17)
};

typedef NS_ENUM(NSUInteger, PaperCutMode) {
    PaperCutModeFullCut = 0,          ///< 全切 (0, 48)
    PaperCutModeFullCutAlt = 48,      ///< 全切 (0, 48) 备用值
    PaperCutModePartialCut = 1,       ///< 半切 (1, 49)
    PaperCutModePartialCutAlt = 49,   ///< 半切 (1, 49) 备用值
};

typedef NS_ENUM(NSUInteger, CashDrawerPin) {
    CashDrawerPin2 = 0,   ///< 钱箱插座的引脚 2 (0, 48)
    CashDrawerPin2Alt = 48, ///< 钱箱插座的引脚 2 (0, 48) 备用值
    CashDrawerPin5 = 1,   ///< 钱箱插座的引脚 5 (1, 49)
    CashDrawerPin5Alt = 49  ///< 钱箱插座的引脚 5 (1, 49) 备用值
};


typedef NS_ENUM(NSUInteger, POSCharacterSet) {
    CharacterSetUSA = 0,            // 美国
    CharacterSetFrance = 1,         // 法国
    CharacterSetGermany = 2,        // 德国
    CharacterSetUK = 3,             // 英国
    CharacterSetDenmarkI = 4,       // 丹麦I
    CharacterSetSweden = 5,         // 瑞典
    CharacterSetItaly = 6,          // 意大利
    CharacterSetSpainI = 7,         // 西班牙I
    CharacterSetJapan = 8,          // 日本
    CharacterSetNorway = 9,         // 挪威
    CharacterSetDenmarkII = 10,     // 丹麦II
    CharacterSetSpainII = 11,       // 西班牙II
    CharacterSetLatinAmerica = 12,  // 拉丁美洲
    CharacterSetKorea = 13,         // 韩国
    CharacterSetSloveniaCroatia = 14, // 斯洛维尼亚/克罗地亚
    CharacterSetChina = 15          // 中国
};

typedef NS_ENUM(NSUInteger, CharacterCodePage) {
    CharacterCodePagePC437_StdEurope = 0,          ///< PC437(Std.Europe)
    CharacterCodePageKatakana = 1,                 ///< Katakana
    CharacterCodePagePC850_Multilingual = 2,       ///< PC850(Multilingual)
    CharacterCodePagePC860_Portugal = 3,           ///< PC860(Portugal)
    CharacterCodePagePC863_Canadian = 4,           ///< PC863(Canadian)
    CharacterCodePagePC865_Nordic = 5,             ///< PC865(Nordic)
    CharacterCodePageWestEurope = 6,               ///< West Europe
    CharacterCodePageGreek = 7,                    ///< Greek
    CharacterCodePageHebrew = 8,                   ///< Hebrew
    CharacterCodePageEastEurope = 9,               ///< East Europe
    CharacterCodePageIran = 10,                    ///< Iran
    CharacterCodePageWPC1252 = 16,                 ///< WPC1252
    CharacterCodePagePC866_Cyrillic2 = 17,         ///< PC866(Cyrillic#2)
    CharacterCodePagePC852_Latin2 = 18,            ///< PC852(Latin2)
    CharacterCodePagePC858 = 19,                   ///< PC858
    CharacterCodePageIranII = 20,                  ///< IranII
    CharacterCodePageLatvian = 21,                 ///< Latvian
    CharacterCodePageArabic = 22,                  ///< Arabic
    CharacterCodePagePT1511251 = 23,               ///< PT1511251
    CharacterCodePagePC747 = 24,                   ///< PC747
    CharacterCodePageWPC1257 = 25,                 ///< WPC1257
    CharacterCodePageVietnam = 27,                 ///< Vietnam
    CharacterCodePagePC864 = 28,                   ///< PC864
    CharacterCodePagePC1001 = 29,                  ///< PC1001
    CharacterCodePageUigur = 30,                   ///< Uigur
    CharacterCodePageHebrewAlt = 31,               ///< Hebrew
    CharacterCodePageWPC1255_Israel = 32,          ///< WPC1255(Israel)
    CharacterCodePageWPC1256 = 33,                 ///< WPC1256
    CharacterCodePagePC437_StdEurope_50 = 50,      ///< PC437(Std.Europe)
    CharacterCodePageKatakana_51 = 51,             ///< Katakana
    CharacterCodePagePC437_StdEurope_52 = 52,      ///< PC437(Std.Europe)
    CharacterCodePagePC858_Multilingual = 53,      ///< PC858(Multilingual)
    CharacterCodePagePC861_Icelandic = 56,         ///< PC861(Icelandic)
    CharacterCodePagePC863_CanadianAlt = 57,       ///< PC863(Canadian)
    CharacterCodePagePC865_NordicAlt = 58,         ///< PC865(Nordic)
    CharacterCodePagePC866_Russian = 59,           ///< PC866(Russian)
    CharacterCodePagePC855_Bulgarian = 60,         ///< PC855(Bulgarian)
    CharacterCodePagePC857_Turkey = 61,            ///< PC857(Turkey)
    CharacterCodePagePC862_Hebrew = 62,            ///< PC862(Hebrew)
    CharacterCodePagePC864_Arabic = 63,            ///< PC864(Arabic)
    CharacterCodePagePC737_Greek = 64,             ///< PC737(Greek)
    CharacterCodePagePC851_Greek = 65,             ///< PC851(Greek)
    CharacterCodePagePC869_Greek = 66,             ///< PC869(Greek)
    CharacterCodePagePC928_Greek = 67,             ///< PC928(Greek)
    CharacterCodePagePC772_Lithuanian = 68,        ///< PC772(Lithuanian)
    CharacterCodePagePC774_Lithuanian = 69,        ///< PC774(Lithuanian)
    CharacterCodePagePC874_Thai = 70,              ///< PC874(Thai)
    CharacterCodePageWPC1252_Latin1 = 71,          ///< WPC1252(Latin-1)
    CharacterCodePageWPC1250_Latin2 = 72,          ///< WPC1250(Latin-2)
    CharacterCodePageWPC1251_Cyrillic = 73,        ///< WPC1251(Cyrillic)
    CharacterCodePagePC3840_IBMRussian = 74,       ///< PC3840(IBM-Russian)
    CharacterCodePagePC3841_Gost = 75,             ///< PC3841(Gost)
    CharacterCodePagePC3843_Polish = 76,           ///< PC3843(Polish)
    CharacterCodePagePC3844_CS2 = 77,              ///< PC3844(CS2)
    CharacterCodePagePC3845_Hungarian = 78,        ///< PC3845(Hungarian)
    CharacterCodePagePC3846_Turkish = 79,          ///< PC3846(Turkish)
    CharacterCodePagePC3847_BrazilABNT = 80,       ///< PC3847(Brazil-ABNT)
    CharacterCodePagePC3848_Brazil = 81,           ///< PC3848(Brazil)
    CharacterCodePagePC1001_ArabicAlt = 82,        ///< PC1001(Arabic)
    CharacterCodePagePC2001_Lithuanian = 83,       ///< PC2001(Lithuanian)
    CharacterCodePagePC3001_Estonian1 = 84,        ///< PC3001(Estonian-1)
    CharacterCodePagePC3002_Eston2 = 85,           ///< PC3002(Eston-2)
    CharacterCodePagePC3011_Latvian1 = 86,         ///< PC3011(Latvian-1)
    CharacterCodePagePC3012_Tatv2 = 87,            ///< PC3012(Tatv-2)
    CharacterCodePagePC3021_Bulgarian = 88,        ///< PC3021(Bulgarian)
    CharacterCodePageThai = 255                    ///< Thai
};


typedef NS_ENUM(NSInteger, TextWidth) {
    TextWidth1 = 0, ///< 将宽度比设置为 x1
    TextWidth2 = 16, ///< 将宽度比设置为 x2
    TextWidth3 = 32, ///< 将宽度比设置为 x3
    TextWidth4 = 48, ///< 将宽度比设置为 x4
    TextWidth5 = 64, ///< 将宽度比设置为 x5
    TextWidth6 = 80, ///< 将宽度比设置为 x6
    TextWidth7 = 96, ///< 将宽度比设置为 x7
    TextWidth8 = 112  ///< 将宽度比设置为 x8
};

typedef NS_ENUM(NSInteger, TextHeight) {
    TextHeight1 = 0, ///< 将高度比设置为 x1
    TextHeight2 = 1, ///< 将高度比设置为 x2
    TextHeight3 = 2, ///< 将高度比设置为 x3
    TextHeight4 = 3, ///< 将高度比设置为 x4
    TextHeight5 = 4, ///< 将高度比设置为 x5
    TextHeight6 = 5, ///< 将高度比设置为 x6
    TextHeight7 = 6, ///< 将高度比设置为 x7
    TextHeight8 = 7  ///< 将高度比设置为 x8
};

typedef NS_ENUM(NSInteger, BarcodeType) {
    BarcodeTypeUPCA = 65, ///< UPC A 类型
    BarcodeTypeUPCE = 66, ///< UPCE 类型
    BarcodeTypeJAN13_EAN13 = 67, ///< JAN-13 类型|EAN-13 类型
    BarcodeTypeJAN8_EAN8 = 68, ///< JAN-8 类型
    BarcodeTypeCode39 = 69, ///< Code 39 类型
    BarcodeTypeITF = 70, ///< ITF 类型
    BarcodeTypeCodabar = 71, ///< Codabar 类型
    BarcodeTypeCode93 = 72, ///< Code 93 类型
    BarcodeTypeCode128 = 73 ///< Code 128 类型 (如果选择 Code 128 类型，data 必须加上 {A, {B, {C 等
};

typedef NS_ENUM(NSInteger, HRITextPosition) {
    HRITextPositionNone,    ///< 不打印 HRI 文本
    HRITextPositionAbove,   ///< 条码上方打印 HRI 文本
    HRITextPositionBelow,   ///< 条码下方打印 HRI 文本
    HRITextPositionBoth     ///< 条码上、下方都打印 HRI 文本
};

typedef NS_ENUM(NSInteger, QRErrorCorrectionLevel) {
    QRErrorCorrectionLevelL = 48,    ///< 错误纠正等级 L (7%)
    QRErrorCorrectionLevelM = 49,    ///< 错误纠正等级 M (15%)
    QRErrorCorrectionLevelQ = 50,    ///< 错误纠正等级 Q (25%)
    QRErrorCorrectionLevelH = 51     ///< 错误纠正等级 H (30%)
};

typedef NS_ENUM(NSInteger, QRCodeAlignment) {
    QRCodeAlignmentLeft = 0,       ///< 左对齐 (Left alignment)
    QRCodeAlignmentCenter,         ///< 居中对齐 (Center alignment)
    QRCodeAlignmentRight           ///< 右对齐 (Right alignment)
};

typedef NS_ENUM(NSInteger, PaperCutType) {
    PaperCutTypeFull,      ///< 全切
    PaperCutTypePartial    ///< 半切
};

typedef NS_ENUM(NSInteger, PinNumber) {
    PinNumberTwo = 2,      ///< 引脚 2
    PinNumberFive = 5      ///< 引脚 5
};
 
/// 实时传送打印机状态
typedef NS_ENUM(NSInteger, PrinterAllStatusType) {
    PrinterStatusTypePrint = 1,     ///< 打印状态
    PrinterStatusTypeOffline = 2,    ///< 脱机状态
    PrinterStatusTypeError = 3,      ///< 错误状态
    PrinterStatusTypePaper = 4       ///< 传送纸状态
};

typedef NS_ENUM(NSInteger, PrinterCommStatusType) {
    PrinterStatusTypeNormal = 0,                    ///< 打印机正常
    PrinterStatusTypeCoverOpen = -1,                ///< 上盖开
    PrinterStatusTypePaperEmpty = -2,               ///< 打印机缺纸
    PrinterStatusTypeOtherError = -3,               ///< 其他错误
    PrinterStatusTypeConnectionLost = -4,           ///< 连接断开
    PrinterStatusTypeReceiveTimeout = -5,           ///< 接收数据超时
    PrinterStatusTypePressFeed = -6,                ///< 按下走纸键
    PrinterStatusTypePrinterError = -7              ///< 打印机错误
};

typedef NS_ENUM(NSInteger, PrintCharacterSet) {
    PrintCharacterSetPC437StdEurope = 0,         ///< PC437(Std.Europe)
    PrintCharacterSetPC861Icelandic = 56,        ///< PC861(Icelandic)
    PrintCharacterSetKatakana = 1,               ///< Katakana
    PrintCharacterSetPC863Canadian = 57,         ///< PC863(Canadian)
    PrintCharacterSetPC850Multilingual = 2,      ///< PC850(Multilingual)
    PrintCharacterSetPC865Nordic = 59,           ///< PC865(Nordic)
    PrintCharacterSetPC860Portugal = 3,          ///< PC860(Portugal)
    PrintCharacterSetPC866Russian = 60,          ///< PC866(Russian)
    PrintCharacterSetPC865Nordic2 = 5,           ///< PC865(Nordic)
    PrintCharacterSetPC857Turkey = 61,           ///< PC857(Turkey)
    PrintCharacterSetWestEurope = 6,              ///< West Europe
    PrintCharacterSetPC862Hebrew = 62,            ///< PC862(Hebrew)
    PrintCharacterSetGreek = 7,                   ///< Greek
    PrintCharacterSetPC864Arabic = 63,            ///< PC864(Arabic)
    PrintCharacterSetHebrew = 8,                  ///< Hebrew
    PrintCharacterSetPC737Greek = 64,             ///< PC737(Greek)
    PrintCharacterSetEastEurope = 9,              ///< East Europe
    PrintCharacterSetPC851Greek = 65,             ///< PC851(Greek)
    PrintCharacterSetIran = 10,                   ///< Iran
    PrintCharacterSetPC869Greek = 66,             ///< PC869(Greek)
    PrintCharacterSetWPC1252 = 16,                ///< WPC1252
    PrintCharacterSetPC866Cyrillic2 = 67,         ///< PC866(Cyrillic#2)
    PrintCharacterSetPC852Latin2 = 18,            ///< PC852(Latin2)
    PrintCharacterSetPC858 = 19,                  ///< PC858
    PrintCharacterSetPC874Thai = 70,              ///< PC874(Thai)
    PrintCharacterSetWPC1252Latin1 = 71,          ///< WPC1252(Latin-1)
    PrintCharacterSetWPC1250Latin2 = 72,          ///< WPC1250(Latin-2)
    PrintCharacterSetWPC1251Cyrillic = 73,        ///< WPC1251(Cyrillic)
    PrintCharacterSetPC3840IBMRussian = 74,       ///< PC3840(IBM-Russian)
    PrintCharacterSetPC774Lithuanian = 69,        ///< PC774(Lithuanian)
    PrintCharacterSetPC1001Arabic = 82,           ///< PC1001(Arabic)
    PrintCharacterSetThai = 255,                  ///< Thai
    PrintCharacterSetPC2001Lithuan = 83,          ///< PC2001(Lithuanian)
    PrintCharacterSetWPC1251Estonian1 = 84,       ///< WPC1251(Estonian-1)
    PrintCharacterSetWPC1252Estonian2 = 85,       ///< WPC1252(Estonian-2)
    PrintCharacterSetPC3011Latvian1 = 86,         ///< PC3011(Latvian-1)
    PrintCharacterSetPC3012Tatv2 = 87,            ///< PC3012(Tatv-2)
    PrintCharacterSetPC3021Bulgarian = 88,        ///< PC3021(Bulgarian)
    PrintCharacterSetPC3041Maltese = 89           ///< PC3041(Maltese)
};


typedef NS_ENUM(NSInteger, DotMatrixDensity) {
    SingleDensity8 = 0,       ///< 8 点单密度
    DoubleDensity8 = 1,       ///< 8 点双密度
    SingleDensity24 = 2,      ///< 24 点单密度 (76 针式打印机不支持)
    DoubleDensity24 = 3       ///< 24 点双密度 (76 针式打印机不支持)
};

typedef NS_ENUM(NSInteger, BmpScaleType) {
    BmpNormal = 0,                ///< 图片原始尺寸
    BmpWidthDouble = 1,           ///< 图片宽度双倍
    BmpHeightDouble = 2,          ///< 图片高度双倍
    BmpWidthHeightDouble = 3      ///< 图片宽高都双倍
};

typedef NS_ENUM(NSInteger, DirectionType) {
    DirectionLeftTop = 0,         ///< 从左上角开始往右
    DirectionLeftBottom = 1,      ///< 从左下角开始往上
    DirectionRightBottom = 2,     ///< 从右下角开始往左
    DirectionRightTop = 3         ///< 从右上角开始往下
};

typedef NS_ENUM(NSInteger, FontType) {
    FontStandard = 0,          ///< 标准 ASCII 码字体 (12 × 24)
    FontCompress = 1           ///< 压缩 ASCII 码字体 (9 × 17)
};

typedef NS_ENUM(NSInteger, AlarmState) {
    AlarmStateNone = 0,     ///< 蜂鸣器不鸣叫，同时报警灯不闪烁
    AlarmStateBuzzer = 1,   ///< 蜂鸣器鸣叫
    AlarmStateLight = 2,    ///< 报警灯闪烁
    AlarmStateBoth = 3      ///< 蜂鸣器鸣叫，同时报警灯闪烁
};


#pragma mark - TSPL ENUM

typedef NS_ENUM(NSInteger, DirectionTSPL) {
    TSPLForward, ///< 向前
    TSPLReverse ///< 反向
};

// Rotation
typedef NS_ENUM(NSInteger, TSPLRotation) {
    TSPLRotation0 = 0,      ///< 不旋转
    TSPLRotation90 = 90,    ///< 顺时针旋转 90 度
    TSPLRotation180 = 180,  ///< 顺时针旋转 180 度
    TSPLRotation270 = 270   ///< 顺时针旋转 270 度
};

typedef NS_ENUM(NSInteger, ReadableType) {
    ReadableTypeNone,   /// 不显示可识别字符
    ReadableTypeLeft,   /// 显示在左边
    ReadableTypeCenter, /// 显示再中间
    ReadableTypeRight   /// 显示再右边
};

/// BMP processing modes
typedef NS_ENUM(NSInteger, BMPMode) {
    BMPModeOverwrite,       ///< OVERWRITE
    BMPModeOR,              ///< OR
    BMPModeXOR,             ///< XOR
    BMPModeOverwriteZlib,   ///< OVERWRITE + zlib
    BMPModeORZlib,          ///< OR + zlib
    BMPModeXORZlib,         ///< XOR + zlib
};

typedef NS_ENUM (NSUInteger,AutoResMode){
    ModeOFF     = 0, ///< 关闭自动返回状态功能
    ModeON      = 1, ///< 打开自动返回状态功能，每打印完一张返回一次
    ModeBATCH   = 2, ///< 打开自动返回状态功能，打印完毕后返回一次
};


#pragma mark - ZPL ENUM

/// Rotation
typedef NS_ENUM(NSInteger, RotationZPL) {
    ZPLRotation0 = 0,      ///< 不旋转
    ZPLRotation90 = 90,    ///< 顺时针旋转 90 度
    ZPLRotation180 = 180,  ///< 顺时针旋转 180 度
    ZPLRotation270 = 270   ///< 顺时针旋转 270 度
};

/// 基础字体尺寸，文字字符有效高度 x 文字字符有效宽度
typedef NS_ENUM(NSInteger, ZPLFontName) {
    ZPLFont9_5 = 0,   ///< 9 点高 x 5 点宽
    ZPLFont11_7,      ///< 11 点高 x 7 点宽
    ZPLFont18_10,     ///< 18 点高 x 10 点宽
    ZPLFont42_20,     ///< 42 点高 x 20 点宽
    ZPLFont26_13,     ///< 26 点高 x 13 点宽
    ZPLFont60_40,     ///< 60 点高 x 40 点宽
    ZPLFont34_22,     ///< 34 点高 x 22 点宽
    ZPLFont24_24,     ///< 24 点高 x 24 点宽
    ZPLFont20_18,     ///< 20 点高 x 18 点宽
    ZPLFont28_24,     ///< 28 点高 x 24 点宽
    ZPLFont35_31,     ///< 35 点高 x 31 点宽
    ZPLFont40_35,     ///< 40 点高 x 35 点宽
    ZPLFont48_42,     ///< 48 点高 x 42 点宽
    ZPLFont59_53,     ///< 59 点高 x 53 点宽
    ZPLFont80_71,     ///< 80 点高 x 71 点宽
    ZPLFont15_12      ///< 15 点高 x 12 点宽
};

/// CodeType for ZPL barcodes.
typedef NS_ENUM(NSInteger, ZPLBarCodeType) {
    ZPLBarCode11 = 0,       ///< Code 11
    ZPLBarCode25,           ///< Code 25
    ZPLBarCode39,           ///< Code 39
    ZPLBarCodeEAN8,         ///< EAN-8
    ZPLBarCodeUPCE,         ///< UPC-E
    ZPLBarCode93,           ///< Code 93
    ZPLBarCode128,          ///< Code 128
    ZPLBarCodeEAN13,        ///< EAN-13
    ZPLBarCodeCODA,         ///< CODA (not standard, perhaps intended as CODABAR)
    ZPLBarCodeMSI,          ///< MSI
    ZPLBarCodePLESSEY,      ///< PLESSEY
    ZPLBarCodeUPCEAN,       ///< UPC-EAN (combination of UPC-A and EAN-13)
    ZPLBarCodeUPCA          ///< UPC-A
};

/// HriText position for ZPL barcodes.
typedef NS_ENUM(NSInteger, HriTextZPL) {
    ZPLHriTextNone = 0,     ///< No human readable text
    ZPLHriTextBelow,        ///< Human readable text below the barcode
    ZPLHriTextAbove         ///< Human readable text above the barcode
};

/// CodePage for ZPL printing.
typedef NS_ENUM(NSInteger, CodePageZPL) {
    ZPLCodePageUSA1 = 0,            ///< USA 1 (Code Page 850)
    ZPLCodePageUSA2 = 1,            ///< USA 2 (Code Page 437)
    ZPLCodePageUK = 2,              ///< United Kingdom (Code Page 850)
    ZPLCodePageNL = 3,              ///< Netherlands (Code Page 850)
    ZPLCodePageDK = 4,              ///< Denmark (Code Page 850)
    ZPLCodePageSwede = 5,           ///< Sweden (Code Page 850)
    ZPLCodePageGER = 6,             ///< Germany (Code Page 850)
    ZPLCodePageFR1 = 7,             ///< France 1 (Code Page 850)
    ZPLCodePageFR2 = 8,             ///< France 2 (Code Page 850)
    ZPLCodePageITA = 9,             ///< Italy (Code Page 850)
    ZPLCodePageES = 10,             ///< Spain (Code Page 850)
    ZPLCodePageJA = 12,             ///< Japan (Code Page 932)
    ZPLCodePageUTF8 = 28,           ///< UTF-8
    ZPLCodePageUTF16Big = 29,       ///< UTF-16 Big Endian
    ZPLCodePageUTF16Little = 30     ///< UTF-16 Little Endian
};

// 存储图像的设备
typedef NS_ENUM(NSInteger, ZPLDeviceType) {
    DeviceTypeR = 0,   ///< 默认值：R:
    DeviceTypeE,       ///< E:
    DeviceTypeB,       ///< B:
    DeviceTypeA        ///< A:
};


typedef NS_ENUM(NSInteger, DiagonalDirection) {
    DiagonalDirectionRight = 0, ///< 右倾斜的对角线
    DiagonalDirectionLeft       ///< 左倾斜的对角线
};


#pragma mark - CPCL ENUM

// Rotation
typedef NS_ENUM(NSInteger, RotationCPCL) {
    CPCLRotation0 = 0,       ///< 不旋转
    CPCLRotation90 = 90,     ///< 顺时针旋转 90 度
    CPCLRotation180 = 180,   ///< 顺时针旋转 180 度
    CPCLRotation270 = 270    ///< 顺时针旋转 270 度
};

// Font
typedef NS_ENUM(NSInteger, FontCPCL) {
    CPCLFont0 = 0,     ///< Font 0
    CPCLFont1 = 1,     ///< Font 1
    CPCLFont2 = 2,     ///< Font 2
    CPCLFont3 = 3,     ///< Font 3
    CPCLFont4 = 4,     ///< Font 4
    CPCLFont5 = 5,     ///< Font 5
    CPCLFont6 = 6,     ///< Font 6
    CPCLFont7 = 7,     ///< Font 7
    CPCLFont24 = 24,   ///< Font 24
    CPCLFont55 = 55    ///< Font 55
};

/// BarCode
typedef NS_ENUM(NSInteger, CPCLBarCodeType) {
    CPCLBarCode128 = 0,    ///< Code 128
    CPCLBarCodeUPCA,       ///< UPC-A
    CPCLBarCodeUPCE,       ///< UPC-E
    CPCLBarCodeEAN13,      ///< EAN-13
    CPCLBarCodeEAN8,       ///< EAN-8
    CPCLBarCode39,         ///< Code 39
    CPCLBarCode93,         ///< Code 93
    CPCLBarCodeCODABAR     ///< CODABAR
};


// BarCode Ratio
typedef NS_ENUM(NSInteger, BarCodeRatioCPCL) {
    CPCLBarCodeRatio0 = 0, ///< 宽条:窄条 = 1.5 :1
    CPCLBarCodeRatio1 = 1, ///< 宽条:窄条 = 2.0 :1
    CPCLBarCodeRatio2 = 2, ///< 宽条:窄条 = 2.5 :1
    CPCLBarCodeRatio3 = 3, ///< 宽条:窄条 = 3.0 :1
    CPCLBarCodeRatio4 = 4, ///< 宽条:窄条 = 3.5 :1
    CPCLBarCodeRatio20 = 20, ///< 宽条:窄条 = 2.0 :1
    CPCLBarCodeRatio21 = 21, ///< 宽条:窄条 = 2.1 :1
    CPCLBarCodeRatio22 = 22, ///< 宽条:窄条 = 2.2 :1
    CPCLBarCodeRatio23 = 23, ///< 宽条:窄条 = 2.3 :1
    CPCLBarCodeRatio24 = 24, ///< 宽条:窄条 = 2.4 :1
    CPCLBarCodeRatio25 = 25, ///< 宽条:窄条 = 2.5 :1
    CPCLBarCodeRatio26 = 26, ///< 宽条:窄条 = 2.6 :1
    CPCLBarCodeRatio27 = 27, ///< 宽条:窄条 = 2.7 :1
    CPCLBarCodeRatio28 = 28, ///< 宽条:窄条 = 2.8 :1
    CPCLBarCodeRatio29 = 29, ///< 宽条:窄条 = 2.9 :1
    CPCLBarCodeRatio30 = 30 ///< 宽条:窄条 = 3.0 :1
};

// QR Code Mode
typedef NS_ENUM(NSInteger, QRCodeModesCPCL) {
    CPCLQRCodeModeORG = 1,     ///< 原始规范
    CPCLQRCodeModeEnhance = 2  ///< 增强后的规范
};

// Alignment
typedef NS_ENUM(NSInteger, AlignmentsCPCL) {
    CPCLAlignmentLeft = 0, ///< 左对齐所有后续字段
    CPCLAlignmentCenter, ///< 居中对齐所有后续字段
    CPCLAlignmentRight  ///< 右对齐所有后续字段
};

#pragma mark - TSPL Constants
// Country code
extern NSString * const kCountryUSA;                     ///< USA
extern NSString * const kCountryCanadianFrench;          ///< Canadian French
extern NSString * const kCountrySpanishLatinAmerica;     ///< Spanish Latin America
extern NSString * const kCountryDutch;                   ///< Dutch
extern NSString * const kCountryBelgian;                 ///< Belgian
extern NSString * const kCountryFranceFrench;            ///< France French
extern NSString * const kCountrySpainSpanish;            ///< Spain Spanish
extern NSString * const kCountryHungarian;               ///< Hungarian
extern NSString * const kCountryYugoslavian;             ///< Yugoslavian
extern NSString * const kCountryItalian;                 ///< Italian
extern NSString * const kCountrySwitzerland;             ///< Switzerland
extern NSString * const kCountrySlovak;                  ///< Slovak
extern NSString * const kCountryUnitedKingdom;           ///< United Kingdom
extern NSString * const kCountryDanish;                  ///< Danish
extern NSString * const kCountrySwedish;                 ///< Swedish
extern NSString * const kCountryNorwegian;               ///< Norwegian
extern NSString * const kCountryPolish;                  ///< Polish
extern NSString * const kCountryGerman;                  ///< German
extern NSString * const kCountryBrazil;                  ///< Brazil
extern NSString * const kCountryEnglishInternational;    ///< English International
extern NSString * const kCountryPortuguese;              ///< Portuguese
extern NSString * const kCountryFinnish;                 ///< Finnish

// CodePage code

// Font name
extern NSString * const kFNT_8_12; /// 8 x 12 英数字体
extern NSString * const kFNT_12_20; /// 12 x 20 英数字体
extern NSString * const kFNT_16_24; /// 16 x 24 英数字体
extern NSString * const kFNT_24_32; /// 24 x 32 英数字体
extern NSString * const kFNT_32_48; /// 32 x 48 英数字体
extern NSString * const kFNT_14_19; /// 14 x 19 英数字体 OCR-B
extern NSString * const kFNT_14_25; /// 14 x 25 英数字体 OCR-A
extern NSString * const kFNT_21_27; /// 21 x 27 英数字体 OCR-B
extern NSString * const kFNT_SIMPLIFIED_CHINESE; /// 简体中文 24x24 字体(GB 码)
extern NSString * const kFNT_TRADITIONAL_CHINESE; /// 繁体中文 24x24 字体(大五码)
extern NSString * const kFNT_KOREAN; /// 韩文 24x24 字体(KS 码)

// Qrcode 生成编码模式
extern NSString * const kQRCodeModeAuto;   /// 自动生成编码
extern NSString * const kQRCodeModeManual; /// 手动生成编码

// Qrcode 错误纠正能力等级
extern NSString * const kECLevelL; /// 错误纠正能力等级 L (7%)
extern NSString * const kECLevelM; /// 错误纠正能力等级 M (15%)
extern NSString * const kECLevelQ; /// 错误纠正能力等级 Q (25%)
extern NSString * const kECLevelH; /// 错误纠正能力等级 H (30%)

// Barcode Code Types
extern NSString * const kBarcodeTypeCode128;        /// Code 128, switching code subset automatically
extern NSString * const kBarcodeTypeCode128Manual;  /// Code 128, switching code subset manually
extern NSString * const kBarcodeTypeEAN128;         /// EAN128, switching code subset automatically
extern NSString * const kBarcodeTypeInterleaved25;  /// Interleaved 2 of 5
extern NSString * const kBarcodeTypeInterleaved25C; /// Interleaved 2 of 5 with check digit
extern NSString * const kBarcodeTypeCode39;        /// Code 39, switching standard and full ASCII mode automatically
extern NSString * const kBarcodeTypeCode39C;       /// Code 39 with check digit
extern NSString * const kBarcodeTypeCode93;        /// Code 93
extern NSString * const kBarcodeTypeEAN13;         /// EAN 13
extern NSString * const kBarcodeTypeEAN13_2;       /// EAN 13 with 2 digits add-on
extern NSString * const kBarcodeTypeEAN13_5;       /// EAN 13 with 5 digits add-on
extern NSString * const kBarcodeTypeEAN8;          /// EAN 8
extern NSString * const kBarcodeTypeEAN8_2;        /// EAN 8 with 2 digits add-on
extern NSString * const kBarcodeTypeEAN8_5;        /// EAN 8 with 5 digits add-on
extern NSString * const kBarcodeTypeCodabar;       /// Codabar
extern NSString * const kBarcodeTypePostnet;       /// Postnet
extern NSString * const kBarcodeTypeUPCA;          /// UPC-A
extern NSString * const kBarcodeTypeUPCA_2;        /// UPC-A with 2 digits add-on
extern NSString * const kBarcodeTypeUPCA_5;        /// UPC-A with 5 digits add-on
extern NSString * const kBarcodeTypeUPCE;          /// UPC-E
extern NSString * const kBarcodeTypeUPCE_2;        /// UPC-E with 2 digits add-on
extern NSString * const kBarcodeTypeUPCE_5;        /// UPC-E with 5 digits add-on
extern NSString * const kBarcodeTypeCpost;         /// China post
extern NSString * const kBarcodeTypeMSI;           /// MSI
extern NSString * const kBarcodeTypeMSIC;          /// MSI with check digit
extern NSString * const kBarcodeTypePlessey;       /// PLESSEY
extern NSString * const kBarcodeTypeITF14;         /// ITF14
extern NSString * const kBarcodeTypeEAN14;         /// EAN14
extern NSString * const kBarcodeTypeCode11;        /// Code 11
extern NSString * const kBarcodeTypeTelepen;       /// Telepen
extern NSString * const kBarcodeTypeTelepenN;      /// Telepen number
extern NSString * const kBarcodeTypePlanet;        /// Planet
extern NSString * const kBarcodeTypeCode49;        /// Code 49
extern NSString * const kBarcodeTypeDPIIdentcode;  /// Deutsche Post Identcode
extern NSString * const kBarcodeTypeDPILeitcode;   /// Deutsche Post Leitcode


#pragma mark - ZPL Constants
// Font name
extern NSString * const kFNT_A;
extern NSString * const kFNT_B;
extern NSString * const kFNT_C;
extern NSString * const kFNT_D;
extern NSString * const kFNT_E;
extern NSString * const kFNT_F;
extern NSString * const kFNT_G;
extern NSString * const kFNT_0;
