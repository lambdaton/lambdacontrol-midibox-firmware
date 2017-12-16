/*
 * Local MIOS32 configuration file
 *
 * this file allows to disable (or re-configure) default functions of MIOS32
 * available switches are listed in $MIOS32_PATH/modules/mios32/MIOS32_CONFIG.txt
 *
 */

#ifndef _MIOS32_CONFIG_H
#define _MIOS32_CONFIG_H

// The boot message which is print during startup and returned on a SysEx query
#define MIOS32_LCD_BOOT_MSG_LINE1 "LambdaControl v1.0"
#define MIOS32_LCD_BOOT_MSG_LINE2 "by LambdaTon"

// USB settings
#define MIOS32_USB_PRODUCT_STR  "LambdaControl"

#endif /* _MIOS32_CONFIG_H */
