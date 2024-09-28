//
//  LogicM.m
//  flutter_printer_sdk
//
//  Created by Apple Mac mini intel on 2024/6/20.
//

#import "LogicM.h"
#import "XSDKPrinter.h"
#import <Flutter/Flutter.h>
@interface LogicM ()

@end

@implementation LogicM

+ (NSData *)sendESC:(NSArray *)data {
    XPOSCommand *commnad = [[XPOSCommand alloc] init];
    
    for (NSDictionary *command in data) {
        NSString *method = command[@"method"];
        NSDictionary *params = command[@"params"];
        
        if ([method isEqualToString:@"printString"]) {
            NSString *text = params[@"text"];
            [commnad addText:text ?: @""];
        } else if ([method isEqualToString:@"printText"]) {
            NSString *text = params[@"text"];
            int alignment = [params[@"alignment"] intValue] ?: POSAlignmentLeft;
            int attribute = [params[@"attribute"] intValue] ?: FntDefault;
            int textSize = [params[@"textSize"] intValue] ?: (TextWidth1 | TextHeight1);
            if (text != nil) {
                [commnad addText:text alignment:alignment attribute:attribute textSize:textSize];
            }
        } else if ([method isEqualToString:@"printBase64Bitmap"]) {
            NSString *bitmapBase64 = params[@"bitmap"];
            int alignment = [params[@"alignment"] intValue] ?: POSAlignmentCenter;
            int mode = [params[@"mode"] intValue] ?: BmpNormal;
            int width = [params[@"width"] intValue] ?: 384;
            if (bitmapBase64 != nil) {
                NSData *bytes = [[NSData alloc] initWithBase64EncodedString:bitmapBase64 options:NSDataBase64DecodingIgnoreUnknownCharacters];
                UIImage *bitmap = [UIImage imageWithData:bytes];
                bitmap = [self scaleImageToWidth:width image:bitmap];
                [commnad selectAlignment:alignment];
                [commnad printImage:bitmap type:BMPThreshold mode:mode];
            }
        } else if ([method isEqualToString:@"printBitmap"]) {
            int alignment = [params[@"alignment"] intValue] ?: POSAlignmentCenter;
            int mode = [params[@"mode"] intValue] ?: BmpNormal;
            int width = [params[@"width"] intValue] ?: 384;
            
            FlutterStandardTypedData *uintInt8List = params[@"bitmap"];
            NSData *bytes = uintInt8List.data;
            UIImage *bitmap = [UIImage imageWithData:bytes];
            bitmap = [self scaleImageToWidth:width image:bitmap];
            [commnad selectAlignment:alignment];
            [commnad printImage:bitmap type:BMPThreshold mode:mode];
        } else if ([method isEqualToString:@"printBarCode"]) {
            NSString *data = params[@"data"];
            int codeType = [params[@"codeType"] intValue];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            int alignment = [params[@"alignment"] intValue];
            int textPosition = [params[@"textPosition"] intValue];
            
            [commnad printBarcodeWithType:codeType andContent:data ?: @""];
            [commnad setBarcodeWidth:width];
            [commnad selectBarcodeHeight:height];
            [commnad selectHRICharacterPrintPosition:textPosition];
            [commnad selectAlignment:alignment];
        } else if ([method isEqualToString:@"feedLine"]) {
            int lineCount = [params[@"lineCount"] intValue] ?: 1;
            [commnad printAndFeedLines:lineCount];
        } else if ([method isEqualToString:@"printQRCode"]) {
            NSString *content = params[@"content"];
            int moduleSize = [params[@"moduleSize"] intValue] ?: 8;
            int ecLevel = [params[@"ecLevel"] intValue] ?: QRErrorCorrectionLevelL;
            int alignment = [params[@"alignment"] intValue] ?: POSAlignmentCenter;
            if (content != nil) {
                [commnad selectAlignment:alignment];
                [commnad printQRCodeWithContent:content moduleSize:moduleSize ecLevel:ecLevel];
            }
        } else if ([method isEqualToString:@"cutHalfAndFeed"]) {
            int lines = [params[@"lines"] intValue];
            [commnad cutPaperWithDistance:lines];
        } else if ([method isEqualToString:@"cutPaper"]) {
            int model = [params[@"model"] intValue] ?: PaperCutTypePartial;
            [commnad cutPaperWithMode:model];
        } else if ([method isEqualToString:@"openCashBox"]) {
            int pinNum = [params[@"pinNum"] intValue];
            int onTime = [params[@"onTime"] intValue] ?: 30;
            int offTime = [params[@"offTime"] intValue] ?: 255;
            if (pinNum != 0) {
                [commnad openCashBoxWithPinNumber:pinNum onTime:onTime offTime:offTime];
            }
        } else if ([method isEqualToString:@"setCharSet"]) {
            NSString *charSet = params[@"charSet"];
            if ([charSet isEqualToString:@"UTF8"]) {
                [commnad setCharEncoding:NSUTF8StringEncoding];
            } else if ([charSet isEqualToString:@"GB18030"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
            } else if ([charSet isEqualToString:@"GB2312"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_2312_80)];
            } else if ([charSet isEqualToString:@"Arabic"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingWindowsArabic)];
            }
        } else if ([method isEqualToString:@"setTextStyle"]) {

        } else if ([method isEqualToString:@"setAlignment"]) {
            int alignment = [params[@"alignment"] intValue] ?: POSAlignmentLeft;
            [commnad selectAlignment:alignment];
        } else if ([method isEqualToString:@"setPrintArea"]) {
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            int x = [params[@"x"] intValue] ?: 0;
            int y = [params[@"y"] intValue] ?: 0;
            if (width != 0 && height != 0) {
                [commnad setPrintArea:x y:y width:width height:height];
            }
        } else if ([method isEqualToString:@"setPageModel"]) {
            BOOL isOpen = [params[@"isOpen"] boolValue] ?: NO;
            if (isOpen) {
                [commnad selectPageMode];
            } else {
                [commnad selectStandardMode];
            }
        } else if ([method isEqualToString:@"printPageModelData"]) {
            [commnad pageModePrint];
        } else if ([method isEqualToString:@"setPrintDirection"]) {
            int direction = [params[@"direction"] intValue];
            if (direction != 0) {
                [commnad selectPrintDirection:direction];
            }
        } else if ([method isEqualToString:@"setAbsoluteHorizontal"]) {
            int position = [params[@"position"] intValue];
            if (position != 0) {
                //[commnad seta:position];
            }
        } else if ([method isEqualToString:@"setRelativeHorizontal"]) {
            int position = [params[@"position"] intValue];
            if (position != 0) {
                [commnad setRelativeHorizontal:position];
            }
        } else if ([method isEqualToString:@"setAbsoluteVertical"]) {
            int position = [params[@"position"] intValue];
            if (position != 0) {
                [commnad setAbsoluteVertical:position];
            }
        } else if ([method isEqualToString:@"setRelativeVertical"]) {
            int position = [params[@"position"] intValue];
            if (position != 0) {
                [commnad setRelativeVertical:position];
            }
        } else if ([method isEqualToString:@"downloadNVImage"]) {
            NSArray<FlutterStandardTypedData *> *bitmaps = params[@"bitmaps"];
            int imageWidth = [params[@"imageWidth"] intValue];
            if (bitmaps != nil && imageWidth != 0) {
                NSMutableArray *bitmapList = [NSMutableArray array];
                for (FlutterStandardTypedData *bitmapData in bitmaps) {
                    NSData *bytes = bitmapData.data;
                    UIImage *bmp = [[UIImage alloc] initWithData:bytes];
                    bmp = [self scaleImageToWidth:imageWidth image:bmp];
                    if (bmp) {
                        [bitmapList addObject:bmp];
                    }
                }
                [commnad definedFlashBmpWithImage:bitmapList];
            }
            
        } else if ([method isEqualToString:@"printNVImage"]) {
            int index = [params[@"index"] intValue];
            int model = [params[@"model"] intValue];
            if (index != 0) {
                [commnad printBitmapToFlashWithN:index andM:model];
            }
        } else if ([method isEqualToString:@"initializePrinter"]) {
            [commnad initializePrinter];
        } else if ([method isEqualToString:@"selectBitmapModel"]) {
            int model = [params[@"model"] intValue];
            int width = [params[@"width"] intValue];
            FlutterStandardTypedData *uintInt8List = params[@"bitmap"];
            NSData *bytes = uintInt8List.data;
            UIImage *bitmap = [[UIImage alloc] initWithData:bytes];
            bitmap = [self scaleImageToWidth:width image:bitmap];
            if (width != 0 && bitmap != nil) {
                [commnad selectBitmapMode:model width:width image:bitmap];
            }
        } else if ([method isEqualToString:@"feedDot"]) {
            int n = [params[@"n"] intValue];
            if (n != 0) {
                [commnad printAndFeedPaper:n];
            }
        } else if ([method isEqualToString:@"setLineSpacing"]) {
            NSNumber *space = params[@"space"];
            if (space != nil) {
                [commnad setLineSpacing:[space intValue]];
            }
        } else if ([method isEqualToString:@"setTurnUpsideDownMode"]) {
            NSNumber *on = params[@"on"];
            BOOL mode = (on != nil) ? [on boolValue] : NO;
            [commnad selectOrCancelInvertedPrint:mode];
        } else if ([method isEqualToString:@"selectCodePage"]) {
            NSNumber *page = params[@"page"];
            if (page != nil) {
                [commnad selectCodePage:[page intValue]];
            }
        } else if ([method isEqualToString:@"selectCharacterFont"]) {
            NSNumber *font = params[@"font"];
            if (font != nil) {
                [commnad selectFont:font.intValue];
            }
        } else if ([method isEqualToString:@"printPDF417"]) {

        } else if ([method isEqualToString:@"sendData"]) {
            FlutterStandardTypedData *uintInt8List = params[@"data"];
            if (uintInt8List.data) {
                [commnad addData:uintInt8List.data];
            }
        }
    }
    
    return  [commnad getCommand];
}

+ (NSData *)sendTSPL:(NSArray *)data {
    
    XTSPLCommand *commnad = [[XTSPLCommand alloc] init];
    
    [data enumerateObjectsUsingBlock:^(NSDictionary<NSString *, id> * _Nonnull command, NSUInteger idx, BOOL * _Nonnull stop) {
        NSString *method = command[@"method"];
        NSDictionary<NSString *, id> *params = command[@"params"];
        
        if ([method isEqualToString:@"sizeInch"]) {
            NSInteger width = [params[@"width"] integerValue];
            NSInteger height = [params[@"height"] integerValue];
            [commnad sizeInch:width height:height];
        } else if ([method isEqualToString:@"sizeMm"]) {
            double width = [params[@"width"] doubleValue];
            double height = [params[@"height"] doubleValue];
            [commnad sizeMm:width height:height];
        } else if ([method isEqualToString:@"gapInch"]) {
            double m = [params[@"m"] doubleValue];
            double n = [params[@"n"] doubleValue];
            [commnad gapInch:m n:n];
        } else if ([method isEqualToString:@"gapMm"]) {
            double m = [params[@"m"] doubleValue];
            double n = [params[@"n"] doubleValue];
            [commnad gapMm:m n:n];
        } else if ([method isEqualToString:@"speed"]) {
            double speed = [params[@"speed"] doubleValue];
            [commnad speed:speed];
        } else if ([method isEqualToString:@"density"]) {
            int density = [params[@"density"] intValue];
            [commnad density:density];
        } else if ([method isEqualToString:@"cls"]) {
            [commnad cls];
        } else if ([method isEqualToString:@"offsetInch"]) {
            double offset = [params[@"offset"] doubleValue];
            [commnad offsetInch:offset];
        } else if ([method isEqualToString:@"offsetMm"]) {
            double offset = [params[@"offset"] doubleValue];
            [commnad offsetMm:offset];
        } else if ([method isEqualToString:@"direction"]) {
            NSInteger direction = [params[@"direction"] integerValue];
            BOOL isMirror = [params[@"isMirror"] boolValue];
            [commnad direction:direction isMirror:isMirror];
        } else if ([method isEqualToString:@"feed"]) {
            int length = [params[@"length"] intValue];
            [commnad feed:length];
        } else if ([method isEqualToString:@"reference"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            [commnad referenceAtX:x y:y];
        } else if ([method isEqualToString:@"bar"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            [commnad barAtX:x andY:y width:width height:height];
        } else if ([method isEqualToString:@"box"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            int thickness = [params[@"thickness"] intValue];
            [commnad boxAtX:x y:y width:width height:height thickness:thickness];
        } else if ([method isEqualToString:@"backFeed"]) {
            int length = [params[@"length"] intValue];
            [commnad backFeed:length];
        } else if ([method isEqualToString:@"formFeed"]) {
            [commnad formFeed];
        } else if ([method isEqualToString:@"home"]) {
            [commnad home];
        } else if ([method isEqualToString:@"print"]) {
            int count = [params[@"count"] intValue];
            [commnad print:count n:1];
        } else if ([method isEqualToString:@"codePage"]) {
            NSString *page = params[@"page"];
            [commnad codePage:page];
        } else if ([method isEqualToString:@"sound"]) {
            int count = [params[@"count"] intValue];
            int interval = [params[@"interval"] intValue];
            [commnad sound:count interval:interval];
        } else if ([method isEqualToString:@"limitFeedInch"]) {
            int length = [params[@"length"] intValue];
            [commnad limitFeedInch:length];
        } else if ([method isEqualToString:@"limitFeedMm"]) {
            int length = [params[@"length"] intValue];
            [commnad limitFeedMm:length];
        } else if ([method isEqualToString:@"barcode"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSString *codeType = params[@"codeType"];
            int height = [params[@"height"] intValue];
            NSInteger readable = [params[@"readable"] integerValue];
            NSInteger rotation = [params[@"rotation"] integerValue];
            int narrow = [params[@"narrow"] intValue];
            int wide = [params[@"wide"] intValue];
            NSString *content = params[@"content"];
            [commnad barcodeAtX:x y:y codeType:codeType height:height readable:readable andRotation:rotation narrow:narrow wide:wide content:content];
        } else if ([method isEqualToString:@"base64bitmap"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSInteger mode = [params[@"mode"] integerValue];
            NSInteger width = [params[@"width"] integerValue];
            NSString *bitmapBase64 = params[@"bitmap"];
            if (bitmapBase64) {
                NSData *imageData = [[NSData alloc] initWithBase64EncodedString:bitmapBase64 options:NSDataBase64DecodingIgnoreUnknownCharacters];
                UIImage *bitmap = [UIImage imageWithData:imageData];
                bitmap = [self scaleImageToWidth:width image:bitmap];
                if (bitmap) {
                    [commnad bitmapAtX:x y:y mode:mode image:bitmap];
                }
            }
        } else if ([method isEqualToString:@"bitmap"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSInteger mode = [params[@"mode"] integerValue];
            NSInteger width = [params[@"width"] integerValue];
            FlutterStandardTypedData *bitmapData = params[@"bitmap"];
            NSData *bytes = bitmapData.data;
            UIImage *bitmap = [UIImage imageWithData:bytes];
            bitmap = [self scaleImageToWidth:width image:bitmap];
            if (bitmap) {
                [commnad bitmapAtX:x y:y mode:mode image:bitmap];
            }
        } else if ([method isEqualToString:@"bitmapCompression"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSInteger mode = [params[@"mode"] integerValue];
            NSInteger width = [params[@"width"] integerValue];
            FlutterStandardTypedData *bitmapData = params[@"bitmap"];
            NSData *bytes = bitmapData.data;
            UIImage *bitmap = [UIImage imageWithData:bytes];
            bitmap = [self scaleImageToWidth:width image:bitmap];
            if (bitmap) {
                [commnad zlibBitmapAtX:x y:y mode:mode image:bitmap];
            }
        } else if ([method isEqualToString:@"qrcode"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            int cellWidth = [params[@"cellWidth"] intValue];
            NSInteger rotation = [params[@"rotation"] integerValue];
            NSString *data = params[@"data"];
            NSString *ecLevel = params[@"ecLevel"] ?: kECLevelL;
            NSString *mode = params[@"mode"] ?: kQRCodeModeAuto;
            [commnad qrCodeAtX:x andY:y ecLevel:ecLevel cellWidth:cellWidth mode:mode rotation:rotation content:data];
        } else if ([method isEqualToString:@"text"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSString *font = params[@"font"];
            NSString *content = params[@"content"];
            NSInteger rotation = [params[@"rotation"] integerValue] ?: TSPLRotation0;
            int xRatio = [params[@"xRatio"] intValue] ?: 1;
            int yRatio = [params[@"yRatio"] intValue] ?: 1;
            [commnad textAtX:x y:y font:font rotation:rotation xRatio:xRatio yRatio:yRatio content:content];
        } else if ([method isEqualToString:@"erase"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            [commnad eraseAtX:x y:y width:width height:height];
        } else if ([method isEqualToString:@"reverse"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            [commnad referenceAtX:x y:y];
        } else if ([method isEqualToString:@"cut"]) {
            [commnad cut];
        } else if ([method isEqualToString:@"setPeel"]) {
            BOOL isOpen = [params[@"isOpen"] boolValue];
            [commnad setPeel:isOpen];
        } else if ([method isEqualToString:@"setTear"]) {
            BOOL isOpen = [params[@"isOpen"] boolValue];
            [commnad setTear:isOpen];
        } else if ([method isEqualToString:@"blineInch"]) {
            double m = [params[@"m"] doubleValue];
            double n = [params[@"n"] doubleValue];
            [commnad blineInch:m n:n];
        } else if ([method isEqualToString:@"blineMm"]) {
            double m = [params[@"m"] doubleValue];
            double n = [params[@"n"] doubleValue];
            [commnad blineMm:m n:n];
        } else if ([method isEqualToString:@"setCharSet"]) {
            NSString *charSet = params[@"charSet"];
            if ([charSet isEqualToString:@"UTF8"]) {
                [commnad setCharEncoding:NSUTF8StringEncoding];
            } else if ([charSet isEqualToString:@"GB18030"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
            } else if ([charSet isEqualToString:@"GB2312"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_2312_80)];
            } else if ([charSet isEqualToString:@"Arabic"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingWindowsArabic)];
            }
        } else if ([method isEqualToString:@"sendData"]) {
            FlutterStandardTypedData *uintInt8List = params[@"data"];
            if (uintInt8List.data) {
                [commnad addData:uintInt8List.data];
            }
        }
    }];
    
    return  [commnad getCommand];
}

+ (NSData *)sendZPL:(NSArray *)data {
    
    XZPLCommand *commnad = [[XZPLCommand alloc] init];
    
    for (NSDictionary *command in data) {
        NSString *method = command[@"method"];
        NSDictionary *params = command[@"params"];
        
        if ([method isEqualToString:@"addStart"]) {
            [commnad start];
        } else if ([method isEqualToString:@"addEnd"]) {
            [commnad end];
        } else if ([method isEqualToString:@"addText"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSString *content = params[@"content"];
            NSString *fontName = params[@"fontName"];
            NSString *rotation = params[@"rotation"];
            int sizeW = [params[@"sizeW"] intValue];
            int sizeH = [params[@"sizeH"] intValue];
            [commnad addTextAtX:x y:y fontName:fontName rotation:[self retrunZPLRotation:rotation] sizeW:sizeW sizeH:sizeH content:content];
        } else if ([method isEqualToString:@"setCustomFont"]) {
            NSString *font = params[@"font"];
            NSString *alias = params[@"alias"];
            int codePage = [params[@"codePage"] intValue];
            [commnad setCustomFont:font extension:font alias:alias codePage:codePage];
        } else if ([method isEqualToString:@"setPrinterWidth"]) {
            int width = [params[@"width"] intValue];
            [commnad setPrinterWidth:width];
        } else if ([method isEqualToString:@"setLabelLength"]) {
            int length = [params[@"length"] intValue];
            [commnad setLabelLength:length];
        } else if ([method isEqualToString:@"addReverse"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            int radius = [params[@"radius"] intValue];
            [commnad addReverseAtX:x y:y width:width height:height radius:radius];
        } else if ([method isEqualToString:@"addBox"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            int thickness = [params[@"thickness"] intValue];
            int radius = [params[@"radius"] intValue];
            [commnad addBoxAtX:x y:y width:width height:height thickness:thickness radius:radius];
        } else if ([method isEqualToString:@"addGraphicDiagonalLine"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSString *orientation = params[@"orientation"];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            int thickness = [params[@"thickness"] intValue];
            [commnad addGraphicDiagonalLineAtX:x y:y orientation:([orientation isEqualToString:@"L"])?DiagonalDirectionLeft:DiagonalDirectionRight width:width height:height thickness:thickness];
        } else if ([method isEqualToString:@"addGraphicEllipse"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            int thickness = [params[@"thickness"] intValue];
            [commnad addGraphicEllipseAtX:x y:y width:width height:height thickness:thickness];
        } else if ([method isEqualToString:@"addGraphicCircle"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            int diameter = [params[@"diameter"] intValue];
            int thickness = [params[@"thickness"] intValue];
            [commnad addGraphicCircleAtX:x y:y diameter:diameter thickness:thickness];
        } else if ([method isEqualToString:@"addBarcode"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSString *codeType = params[@"codeType"];
            NSString *ratio = params[@"ratio"];
            Byte textPosition = (Byte)[params[@"textPosition"] intValue];
            NSString *data = params[@"data"];
            int width = [params[@"width"] intValue];
            int height = [params[@"height"] intValue];
            
            int postition = ZPLHriTextNone;
            if (textPosition == 0x01) postition = ZPLHriTextAbove;
            if (textPosition == 0x02) postition = ZPLHriTextBelow;
            
            if ([self retrunZPLBarCodeType:codeType] >= 0) {
                [commnad addBarcodeAtX:x y:y codeType:[LogicM retrunZPLBarCodeType:codeType] ratio:[self retrunZPLRotation:ratio] textPosition:postition content:data width:width height:height];
            }
            
        } else if ([method isEqualToString:@"addQRCode"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSString *data = params[@"data"];
            int size = [params[@"size"] intValue];
            [commnad addQRCodeAtX:x y:y factor:size text:data];
        } else if ([method isEqualToString:@"printBitmap"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            FlutterStandardTypedData *bitmapData = params[@"bitmap"];
            NSData *bytes = bitmapData.data;
            int width = [params[@"width"] intValue];
            UIImage *bitmap = [UIImage imageWithData:bytes];
            bitmap = [LogicM scaleImageToWidth:width image:bitmap];
            [commnad printImageAtX:x y:y wRatio:1 hRatio:1 image:bitmap];
        } else if ([method isEqualToString:@"printBmpCompress"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            FlutterStandardTypedData *bitmapData = params[@"bitmap"];
            NSData *bytes = bitmapData.data;
            int width = [params[@"width"] intValue];
            UIImage *bitmap = [UIImage imageWithData:bytes];
            bitmap = [LogicM scaleImageToWidth:width image:bitmap];
            [commnad printImageAtX:x y:y wRatio:1 hRatio:1 image:bitmap];
        } else if ([method isEqualToString:@"downloadBitmap"]) {
            int width = [params[@"width"] intValue];
            NSString *bmpName = params[@"bmpName"];
            FlutterStandardTypedData *bitmapData = params[@"bitmap"];
            UIImage *bmp = [UIImage imageWithData:bitmapData.data];
            bmp = [LogicM scaleImageToWidth:width image:bmp];
            [commnad downloadGraphic:DeviceTypeR name:bmpName image:bmp];
        } else if ([method isEqualToString:@"useDownloadBitmap"]) {
            int x = [params[@"x"] intValue];
            int y = [params[@"y"] intValue];
            NSString *bmpName = params[@"bmpName"];
            int mx = [params[@"mx"] intValue];
            int my = [params[@"my"] intValue];
            [commnad printGraphicAtX:x y:y source:DeviceTypeR name:bmpName mx:mx my:my];
        } else if ([method isEqualToString:@"addPrintCount"]) {
            int count = [params[@"count"] intValue];
            [commnad addPrintCount:count];
        } else if ([method isEqualToString:@"setPrintSpeed"]) {
            int speed = [params[@"speed"] intValue];
            [commnad setPrintSpeed:speed];
        } else if ([method isEqualToString:@"setPrintOrientation"]) {
            NSString *orientation = params[@"orientation"];
            [commnad direction:([orientation isEqualToString:@"I"])?NO:YES];
        } else if ([method isEqualToString:@"setPrintDensity"]) {
            int density = [params[@"density"] intValue];
            [commnad setPrintDensity:density];
        } else if ([method isEqualToString:@"setCharSet"]) {
            NSString *charSet = params[@"charSet"];
            if ([charSet isEqualToString:@"UTF8"]) {
                [commnad setCharEncoding:NSUTF8StringEncoding];
            } else if ([charSet isEqualToString:@"GB18030"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000)];
            } else if ([charSet isEqualToString:@"GB2312"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_2312_80)];
            } else if ([charSet isEqualToString:@"Arabic"]) {
                [commnad setCharEncoding:CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingWindowsArabic)];
            }
        } else if ([method isEqualToString:@"sendData"]) {
            FlutterStandardTypedData *data = params[@"data"];
            [commnad addData:data.data];
        }
    }
    
    return [commnad getCommand];
}

+ (UIImage *)scaleImageToWidth:(CGFloat)width image:(UIImage *)image {
    width = (int)((width + 7) / 8 * 8);
    int height = image.size.height * width / image.size.width;
    if(height < 0) {
        height = 1;
    }
    CGSize size = CGSizeMake(width, height);
    UIGraphicsBeginImageContextWithOptions(size, NO, 1.0f);
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *resultImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return resultImage;
}

+ (int)posStatus:(NSData *)data {
    
    unsigned status = 0;
    if (data.length == 1) {
        const Byte *byte = (Byte *)[data bytes];
        status = byte[0];
    } else if (data.length == 2) {
        const Byte *byte = (Byte *)[data bytes];
        status = byte[1];
    }
    
    if (status == 0x12) {
        return 0;//Normal
    } else if (status == 0x16) {
        return 16;//Cover opened
    } else if (status == 0x32) {
        return 32;//Paper end
    } else if (status == 0x36) {
        return 36;//Cover opened & Paper end
    } else if (status == 0x1A) {
        return 8;//Feeding
    } else {
        return 64;//Other error
    }
    
    return -1;
}

+ (int)cashBoxStatus:(NSData *)data {
    /// test Casher status
    if (data.length == 0) return -1;
    
    if (data.length == 1) {
        const Byte *byte = (Byte *)[data bytes];
        unsigned status = byte[0];
        
        if (status == 0x00) {
            return 0;
        } else if (status == 0x01) {
            return 1;
        }
    }
    return -1;
}

+ (int)labelStatus:(NSData *)data {
    
    unsigned status = 0;
    if (data.length == 1) {
        const Byte *byte = (Byte *)[data bytes];
        status = byte[0];
    } else if (data.length == 2) {
        const Byte *byte = (Byte *)[data bytes];
        status = byte[1];
    }
    
    if (status == 0x00) {
        return 0;//Normal
    } else if (status == 0x01) {
        return 1;//Cover opened
    } else if (status == 0x02) {
        return 2;//Paper jam
    } else if (status == 0x03) {
        return 3;//Cover opened and paper jam
    } else if (status == 0x04) {
        return 4;//Paper end
    } else if (status == 0x05) {
        return 5;//Cover opened and Paper end
    } else if (status == 0x08) {
        return 8;//No Ribbon
    } else if (status == 0x09) {
        return 9;//Cover opened and no Ribbon
    } else if (status == 0x10) {
        return 16;//Pause
    } else if (status == 0x20) {
        return 32;//Printing
    }
    
    return -1;
}

+ (int)retrunZPLBarCodeType:(NSString *)code {
    if ([code isEqualToString: @"^B1"]) {
        return ZPLBarCode11;
    } else if ([code isEqualToString: @"^B2"]) {
        return ZPLBarCode25;
    } else if ([code isEqualToString: @"^B3"]) {
        return ZPLBarCode39;
    } else if ([code isEqualToString: @"^B8"]) {
        return ZPLBarCodeEAN8;
    } else if ([code isEqualToString: @"^B9"]) {
        return ZPLBarCodeUPCE;
    } else if ([code isEqualToString: @"^BA"]) {
        return ZPLBarCode93;
    } else if ([code isEqualToString: @"^BC"]) {
        return ZPLBarCode128;
    } else if ([code isEqualToString: @"^BE"]) {
        return ZPLBarCodeEAN13;
    } else if ([code isEqualToString: @"^BK"]) {
        return ZPLBarCodeCODA;
    } else if ([code isEqualToString: @"^BM"]) {
        return ZPLBarCodeMSI;
    } else if ([code isEqualToString: @"^BP"]) {
        return ZPLBarCodePLESSEY;
    } else if ([code isEqualToString: @"^BS"]) {
        return ZPLBarCodeUPCEAN;
    } else if ([code isEqualToString: @"^BU"]) {
        return ZPLBarCodeUPCA;
    }
    return -1;
}

+ (int)retrunZPLRotation:(NSString *)code {
    if ([code isEqualToString: @"N"]) {
        return ZPLRotation0;
    } else if ([code isEqualToString: @"R"]) {
        return ZPLRotation90;
    } else if ([code isEqualToString: @"I"]) {
        return ZPLRotation180;
    } else if ([code isEqualToString: @"B"]) {
        return ZPLRotation270;
    }
    return ZPLRotation0;
}

+ (int)retrunZPLFontName:(NSString *)code {
    if ([code isEqualToString: @"A"]) {
        return ZPLFont9_5;
    } else if ([code isEqualToString: @"B"]) {
        return ZPLFont11_7;
    } else if ([code isEqualToString: @"C"]) {
        return ZPLFont18_10;
    } else if ([code isEqualToString: @"D"]) {
        return ZPLFont28_24;
    } else if ([code isEqualToString: @"E"]) {
        return ZPLFont42_20;
    } else if ([code isEqualToString: @"F"]) {
        return ZPLFont26_13;
    } else if ([code isEqualToString: @"G"]) {
        return ZPLFont60_40;
    } else if ([code isEqualToString: @"0"]) {
        return ZPLFont15_12;
    }
    return ZPLFont9_5;
}

@end
