//
//  XAdvProtocol.h
//  PrinterSDK
//
//  Created by max on 2024/5/19.
//

#import <Foundation/Foundation.h>

typedef void (^XTestBlock)(NSString *code);

@protocol XAdvProtocol <NSObject>

- (void)printerTest:(XTestBlock)codeBlock;

@end
