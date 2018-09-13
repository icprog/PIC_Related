/*
 * File:   font.h
 * Author: http://pic18fxx.blogspot.com 
 *
 * To create personalized fonts, symbols and icons for Graphic TFT, you can use:
 * --------------- GLCD Font Creator
 * --------------- Microchip Graphics Resource Converter
 */
#ifndef __FONT_H
#define __FONT_H

#include <xc.h>

const unsigned char Courier_New_Bold_20[] = {
/****************************************
 * Font header
 ****************************************/
    0x00,           // Information
    0x00,           // ID
    0x20, 0x00,     // First Character
    0x7E, 0x00,     // Last Character
    0x17,           // Height
    0x00,           // Reserved
/****************************************
 * Font Glyph Table
 ****************************************/
    0x0C, 0x84, 0x01, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xB2, 0x01, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xE0, 0x01, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x0E, 0x02, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x3C, 0x02, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x6A, 0x02, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x98, 0x02, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xC6, 0x02, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xF4, 0x02, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x22, 0x03, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x50, 0x03, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x7E, 0x03, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xAC, 0x03, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xDA, 0x03, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x08, 0x04, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x36, 0x04, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x64, 0x04, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x92, 0x04, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xC0, 0x04, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xEE, 0x04, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x1C, 0x05, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x4A, 0x05, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x78, 0x05, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xA6, 0x05, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xD4, 0x05, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x02, 0x06, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x30, 0x06, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x5E, 0x06, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x8C, 0x06, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xBA, 0x06, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xE8, 0x06, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x16, 0x07, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x44, 0x07, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x72, 0x07, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xA0, 0x07, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xCE, 0x07, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xFC, 0x07, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x2A, 0x08, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x58, 0x08, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x86, 0x08, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xB4, 0x08, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xE2, 0x08, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x10, 0x09, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x3E, 0x09, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x6C, 0x09, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x9A, 0x09, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xC8, 0x09, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xF6, 0x09, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x24, 0x0A, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x52, 0x0A, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x80, 0x0A, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xAE, 0x0A, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xDC, 0x0A, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x0A, 0x0B, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x38, 0x0B, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x66, 0x0B, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x94, 0x0B, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xC2, 0x0B, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xF0, 0x0B, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x1E, 0x0C, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x4C, 0x0C, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x7A, 0x0C, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xA8, 0x0C, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xD6, 0x0C, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x04, 0x0D, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x32, 0x0D, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x60, 0x0D, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x8E, 0x0D, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xBC, 0x0D, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xEA, 0x0D, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x18, 0x0E, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x46, 0x0E, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x74, 0x0E, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xA2, 0x0E, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xD0, 0x0E, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xFE, 0x0E, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x2C, 0x0F, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x5A, 0x0F, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x88, 0x0F, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xB6, 0x0F, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xE4, 0x0F, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x12, 0x10, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x40, 0x10, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x6E, 0x10, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x9C, 0x10, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xCA, 0x10, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xF8, 0x10, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x26, 0x11, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x54, 0x11, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x82, 0x11, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xB0, 0x11, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0xDE, 0x11, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x0C, 0x12, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x3A, 0x12, 0x00,           // width, MSB Offset, LSB offset
    0x0C, 0x68, 0x12, 0x00,           // width, MSB Offset, LSB offset
/***********************************
 * Font Characters
 ***********************************/
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x20, 0x00,         //      *          
    0x20, 0x00,         //      *          
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x9C, 0x03,         //   ***  ***      
    0x9C, 0x03,         //   ***  ***      
    0x9C, 0x03,         //   ***  ***      
    0x08, 0x01,         //    *    *       
    0x08, 0x01,         //    *    *       
    0x08, 0x01,         //    *    *       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xF0, 0x03,         //     ******      
    0xF8, 0x03,         //    *******      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x00,         //   **            
    0x7C, 0x00,         //   *****         
    0xF8, 0x01,         //    ******       
    0x80, 0x03,         //        ***      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0xFC, 0x01,         //   *******       
    0xFC, 0x00,         //   ******        
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x1C, 0x00,         //   ***           
    0x22, 0x00,         //  *   *          
    0x22, 0x00,         //  *   *          
    0x22, 0x00,         //  *   *          
    0x1C, 0x03,         //   ***   **      
    0xC0, 0x03,         //       ****      
    0xF8, 0x00,         //    *****        
    0x1E, 0x00,         //  ****           
    0xC6, 0x01,         //  **   ***       
    0x20, 0x02,         //      *   *      
    0x20, 0x02,         //      *   *      
    0x20, 0x02,         //      *   *      
    0xC0, 0x01,         //       ***       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x03,         //      *****      
    0xF8, 0x03,         //    *******      
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x30, 0x00,         //     **          
    0x78, 0x06,         //    ****  **     
    0xFC, 0x07,         //   *********     
    0xCC, 0x03,         //   **  ****      
    0x8C, 0x01,         //   **   **       
    0xFC, 0x07,         //   *********     
    0xF0, 0x06,         //     **** **     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x00,         //      ***        
    0xE0, 0x00,         //      ***        
    0xE0, 0x00,         //      ***        
    0x40, 0x00,         //       *         
    0x40, 0x00,         //       *         
    0x40, 0x00,         //       *         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0xC0, 0x00,         //       **        
    0xC0, 0x00,         //       **        
    0xC0, 0x00,         //       **        
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xC0, 0x00,         //       **        
    0xC0, 0x00,         //       **        
    0xC0, 0x00,         //       **        
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x6C, 0x03,         //   ** ** **      
    0xFC, 0x03,         //   ********      
    0xF0, 0x00,         //     ****        
    0xF0, 0x00,         //     ****        
    0xF8, 0x01,         //    ******       
    0x98, 0x01,         //    **  **       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x00,         //      ***        
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x10, 0x00,         //     *           
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFE, 0x03,         //  *********      
    0xFE, 0x03,         //  *********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x03,         //         **      
    0x00, 0x03,         //         **      
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0xC0, 0x00,         //       **        
    0xC0, 0x00,         //       **        
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x0C, 0x00,         //   **            
    0x0C, 0x00,         //   **            
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF8, 0x00,         //    *****        
    0xFC, 0x01,         //   *******       
    0x8C, 0x01,         //   **   **       
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x8C, 0x01,         //   **   **       
    0xFC, 0x01,         //   *******       
    0xF8, 0x00,         //    *****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x60, 0x00,         //      **         
    0x7C, 0x00,         //   *****         
    0x7C, 0x00,         //   *****         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF8, 0x00,         //    *****        
    0xFC, 0x01,         //   *******       
    0x8E, 0x03,         //  ***   ***      
    0x06, 0x03,         //  **     **      
    0x00, 0x03,         //         **      
    0x80, 0x01,         //        **       
    0xC0, 0x00,         //       **        
    0x60, 0x00,         //      **         
    0x30, 0x00,         //     **          
    0x18, 0x00,         //    **           
    0x0C, 0x00,         //   **            
    0xFE, 0x03,         //  *********      
    0xFE, 0x03,         //  *********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF8, 0x00,         //    *****        
    0xFE, 0x01,         //  ********       
    0x86, 0x03,         //  **    ***      
    0x00, 0x03,         //         **      
    0x80, 0x03,         //        ***      
    0xF0, 0x01,         //     *****       
    0xF0, 0x01,         //     *****       
    0x80, 0x03,         //        ***      
    0x00, 0x03,         //         **      
    0x00, 0x03,         //         **      
    0x83, 0x03,         // **     ***      
    0xFF, 0x01,         // *********       
    0xFE, 0x00,         //  *******        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xC0, 0x01,         //       ***       
    0xE0, 0x01,         //      ****       
    0xE0, 0x01,         //      ****       
    0xB0, 0x01,         //     ** **       
    0x98, 0x01,         //    **  **       
    0x98, 0x01,         //    **  **       
    0x8C, 0x01,         //   **   **       
    0x86, 0x01,         //  **    **       
    0xFE, 0x03,         //  *********      
    0xFE, 0x03,         //  *********      
    0x80, 0x01,         //        **       
    0xE0, 0x03,         //      *****      
    0xE0, 0x03,         //      *****      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFC, 0x01,         //   *******       
    0xFC, 0x01,         //   *******       
    0x0C, 0x00,         //   **            
    0x0C, 0x00,         //   **            
    0xFC, 0x00,         //   ******        
    0xFC, 0x01,         //   *******       
    0x8C, 0x03,         //   **   ***      
    0x00, 0x03,         //         **      
    0x00, 0x03,         //         **      
    0x00, 0x03,         //         **      
    0x86, 0x03,         //  **    ***      
    0xFE, 0x01,         //  ********       
    0xFC, 0x00,         //   ******        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x03,         //      *****      
    0xF8, 0x03,         //    *******      
    0x3C, 0x00,         //   ****          
    0x0C, 0x00,         //   **            
    0x0E, 0x00,         //  ***            
    0xF6, 0x00,         //  ** ****        
    0xFE, 0x01,         //  ********       
    0x8E, 0x03,         //  ***   ***      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x8C, 0x03,         //   **   ***      
    0xFC, 0x01,         //   *******       
    0xF0, 0x00,         //     ****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFE, 0x03,         //  *********      
    0xFE, 0x03,         //  *********      
    0x06, 0x03,         //  **     **      
    0x00, 0x03,         //         **      
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0xC0, 0x00,         //       **        
    0xC0, 0x00,         //       **        
    0xC0, 0x00,         //       **        
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF8, 0x00,         //    *****        
    0xFC, 0x01,         //   *******       
    0x8E, 0x03,         //  ***   ***      
    0x06, 0x03,         //  **     **      
    0x8E, 0x03,         //  ***   ***      
    0xFC, 0x01,         //   *******       
    0xFC, 0x01,         //   *******       
    0x8E, 0x03,         //  ***   ***      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x8E, 0x03,         //  ***   ***      
    0xFC, 0x01,         //   *******       
    0xF8, 0x00,         //    *****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x78, 0x00,         //    ****         
    0xFC, 0x01,         //   *******       
    0x8E, 0x01,         //  ***   **       
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x8E, 0x03,         //  ***   ***      
    0xFC, 0x03,         //   ********      
    0x78, 0x03,         //    **** **      
    0x80, 0x03,         //        ***      
    0x80, 0x01,         //        **       
    0xE0, 0x01,         //      ****       
    0xFE, 0x00,         //  *******        
    0x3E, 0x00,         //  *****          
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xC0, 0x01,         //       ***       
    0xC0, 0x01,         //       ***       
    0xC0, 0x01,         //       ***       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x00,         //      ***        
    0x60, 0x00,         //      **         
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x10, 0x00,         //     *           
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x06,         //          **     
    0x80, 0x07,         //        ****     
    0xE0, 0x01,         //      ****       
    0x70, 0x00,         //     ***         
    0x1C, 0x00,         //   ***           
    0x0F, 0x00,         // ****            
    0x1C, 0x00,         //   ***           
    0x70, 0x00,         //     ***         
    0xE0, 0x01,         //      ****       
    0x80, 0x07,         //        ****     
    0x00, 0x06,         //          **     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFF, 0x07,         // ***********     
    0xFF, 0x07,         // ***********     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFF, 0x07,         // ***********     
    0xFF, 0x07,         // ***********     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x06, 0x00,         //  **             
    0x1E, 0x00,         //  ****           
    0x78, 0x00,         //    ****         
    0xE0, 0x00,         //      ***        
    0x80, 0x03,         //        ***      
    0x00, 0x0F,         //         ****    
    0x80, 0x03,         //        ***      
    0xE0, 0x00,         //      ***        
    0x78, 0x00,         //    ****         
    0x1E, 0x00,         //  ****           
    0x06, 0x00,         //  **             
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF8, 0x00,         //    *****        
    0xFC, 0x01,         //   *******       
    0x8C, 0x03,         //   **   ***      
    0x0C, 0x03,         //   **    **      
    0x00, 0x03,         //         **      
    0xC0, 0x01,         //       ***       
    0xE0, 0x00,         //      ***        
    0x60, 0x00,         //      **         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x00,         //      ***        
    0x98, 0x00,         //    **  *        
    0x08, 0x01,         //    *    *       
    0x04, 0x01,         //   *     *       
    0x04, 0x01,         //   *     *       
    0xC4, 0x01,         //   *   ***       
    0x24, 0x01,         //   *  *  *       
    0x24, 0x01,         //   *  *  *       
    0x24, 0x01,         //   *  *  *       
    0xC4, 0x01,         //   *   ***       
    0x04, 0x00,         //   *             
    0x08, 0x00,         //    *            
    0x08, 0x01,         //    *    *       
    0xF0, 0x00,         //     ****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFC, 0x00,         //   ******        
    0xFC, 0x00,         //   ******        
    0xE0, 0x00,         //      ***        
    0xB0, 0x01,         //     ** **       
    0xB0, 0x01,         //     ** **       
    0x98, 0x01,         //    **  **       
    0x18, 0x03,         //    **   **      
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x06, 0x06,         //  **      **     
    0x0F, 0x0F,         // ****    ****    
    0x0F, 0x0F,         // ****    ****    
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFE, 0x00,         //  *******        
    0xFE, 0x01,         //  ********       
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x8C, 0x03,         //   **   ***      
    0xFC, 0x01,         //   *******       
    0xFC, 0x03,         //   ********      
    0x0C, 0x07,         //   **    ***     
    0x0C, 0x06,         //   **     **     
    0x0C, 0x06,         //   **     **     
    0xFE, 0x07,         //  **********     
    0xFE, 0x01,         //  ********       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x06,         //     **** **     
    0xF8, 0x07,         //    ********     
    0x1C, 0x07,         //   ***   ***     
    0x0E, 0x06,         //  ***     **     
    0x06, 0x00,         //  **             
    0x06, 0x00,         //  **             
    0x06, 0x00,         //  **             
    0x06, 0x00,         //  **             
    0x0E, 0x06,         //  ***     **     
    0x1C, 0x07,         //   ***   ***     
    0xF8, 0x03,         //    *******      
    0xF0, 0x01,         //     *****       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFF, 0x00,         // ********        
    0xFF, 0x01,         // *********       
    0x86, 0x03,         //  **    ***      
    0x06, 0x07,         //  **     ***     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x07,         //  **     ***     
    0x86, 0x03,         //  **    ***      
    0xFF, 0x01,         // *********       
    0xFF, 0x00,         // ********        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x0C, 0x06,         //   **     **     
    0x0C, 0x06,         //   **     **     
    0xCC, 0x00,         //   **  **        
    0xFC, 0x00,         //   ******        
    0xFC, 0x00,         //   ******        
    0xCC, 0x00,         //   **  **        
    0x0C, 0x06,         //   **     **     
    0x0C, 0x06,         //   **     **     
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x0C, 0x06,         //   **     **     
    0x0C, 0x06,         //   **     **     
    0xCC, 0x00,         //   **  **        
    0xFC, 0x00,         //   ******        
    0xFC, 0x00,         //   ******        
    0xCC, 0x00,         //   **  **        
    0x0C, 0x00,         //   **            
    0x0C, 0x00,         //   **            
    0x7E, 0x00,         //  ******         
    0x7E, 0x00,         //  ******         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x06,         //     **** **     
    0xFC, 0x07,         //   *********     
    0x0C, 0x07,         //   **    ***     
    0x06, 0x06,         //  **      **     
    0x06, 0x00,         //  **             
    0x06, 0x00,         //  **             
    0xC6, 0x0F,         //  **   ******    
    0xC6, 0x0F,         //  **   ******    
    0x06, 0x06,         //  **      **     
    0x0C, 0x06,         //   **     **     
    0xFC, 0x07,         //   *********     
    0xF0, 0x01,         //     *****       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x9E, 0x07,         //  ****  ****     
    0x9E, 0x07,         //  ****  ****     
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x9E, 0x07,         //  ****  ****     
    0x9E, 0x07,         //  ****  ****     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x0F,         //      *******    
    0xE0, 0x0F,         //      *******    
    0x00, 0x03,         //         **      
    0x00, 0x03,         //         **      
    0x00, 0x03,         //         **      
    0x00, 0x03,         //         **      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x86, 0x03,         //  **    ***      
    0xFE, 0x01,         //  ********       
    0xF8, 0x00,         //    *****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xBE, 0x0F,         //  ***** *****    
    0xBE, 0x0F,         //  ***** *****    
    0x8C, 0x03,         //   **   ***      
    0xCC, 0x00,         //   **  **        
    0x6C, 0x00,         //   ** **         
    0x7C, 0x00,         //   *****         
    0xDC, 0x00,         //   *** **        
    0x8C, 0x01,         //   **   **       
    0x8C, 0x01,         //   **   **       
    0x0C, 0x03,         //   **    **      
    0x3E, 0x0F,         //  *****  ****    
    0x3E, 0x0E,         //  *****   ***    
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x7E, 0x00,         //  ******         
    0x7E, 0x00,         //  ******         
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x06,         //    **    **     
    0x18, 0x06,         //    **    **     
    0x18, 0x06,         //    **    **     
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x0F, 0x0F,         // ****    ****    
    0x0F, 0x0F,         // ****    ****    
    0x0E, 0x07,         //  ***    ***     
    0x9E, 0x07,         //  ****  ****     
    0x96, 0x06,         //  ** *  * **     
    0xF6, 0x06,         //  ** **** **     
    0xF6, 0x06,         //  ** **** **     
    0x66, 0x06,         //  **  **  **     
    0x66, 0x06,         //  **  **  **     
    0x06, 0x06,         //  **      **     
    0x9F, 0x0F,         // *****  *****    
    0x9F, 0x0F,         // *****  *****    
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xCE, 0x07,         //  ***  *****     
    0xDE, 0x07,         //  **** *****     
    0x1C, 0x03,         //   ***   **      
    0x3C, 0x03,         //   ****  **      
    0x3C, 0x03,         //   ****  **      
    0x6C, 0x03,         //   ** ** **      
    0x6C, 0x03,         //   ** ** **      
    0xCC, 0x03,         //   **  ****      
    0xCC, 0x03,         //   **  ****      
    0x8C, 0x03,         //   **   ***      
    0xBE, 0x03,         //  ***** ***      
    0x3E, 0x03,         //  *****  **      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x00,         //     ****        
    0xF8, 0x01,         //    ******       
    0x9C, 0x03,         //   ***  ***      
    0x0E, 0x07,         //  ***    ***     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x0E, 0x07,         //  ***    ***     
    0x9C, 0x03,         //   ***  ***      
    0xF8, 0x01,         //    ******       
    0xF0, 0x00,         //     ****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFE, 0x01,         //  ********       
    0xFE, 0x03,         //  *********      
    0x0C, 0x07,         //   **    ***     
    0x0C, 0x06,         //   **     **     
    0x0C, 0x06,         //   **     **     
    0x0C, 0x07,         //   **    ***     
    0xFC, 0x03,         //   ********      
    0xFC, 0x01,         //   *******       
    0x0C, 0x00,         //   **            
    0x0C, 0x00,         //   **            
    0x7E, 0x00,         //  ******         
    0x7E, 0x00,         //  ******         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x00,         //     ****        
    0xF8, 0x01,         //    ******       
    0x9C, 0x03,         //   ***  ***      
    0x0E, 0x07,         //  ***    ***     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x0E, 0x07,         //  ***    ***     
    0x9C, 0x03,         //   ***  ***      
    0xF8, 0x01,         //    ******       
    0xF0, 0x00,         //     ****        
    0xF0, 0x06,         //     **** **     
    0xF8, 0x07,         //    ********     
    0x98, 0x03,         //    **  ***      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFE, 0x01,         //  ********       
    0xFE, 0x03,         //  *********      
    0x0C, 0x07,         //   **    ***     
    0x0C, 0x06,         //   **     **     
    0x0C, 0x07,         //   **    ***     
    0xFC, 0x03,         //   ********      
    0xFC, 0x01,         //   *******       
    0x8C, 0x03,         //   **   ***      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x07,         //   **    ***     
    0x3E, 0x0E,         //  *****   ***    
    0x3E, 0x0C,         //  *****    **    
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF8, 0x06,         //    ***** **     
    0xFC, 0x07,         //   *********     
    0x0E, 0x07,         //  ***    ***     
    0x06, 0x06,         //  **      **     
    0x0E, 0x00,         //  ***            
    0xFC, 0x00,         //   ******        
    0xF0, 0x03,         //     ******      
    0x00, 0x07,         //         ***     
    0x06, 0x06,         //  **      **     
    0x0E, 0x07,         //  ***    ***     
    0xFE, 0x03,         //  *********      
    0xF6, 0x01,         //  ** *****       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x66, 0x06,         //  **  **  **     
    0x66, 0x06,         //  **  **  **     
    0x66, 0x06,         //  **  **  **     
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xF8, 0x01,         //    ******       
    0xF8, 0x01,         //    ******       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x9E, 0x07,         //  ****  ****     
    0x9E, 0x07,         //  ****  ****     
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x9C, 0x03,         //   ***  ***      
    0xF8, 0x01,         //    ******       
    0xF0, 0x00,         //     ****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x8F, 0x07,         // ****   ****     
    0x8F, 0x07,         // ****   ****     
    0x06, 0x03,         //  **     **      
    0x06, 0x03,         //  **     **      
    0x8C, 0x01,         //   **   **       
    0x8C, 0x01,         //   **   **       
    0xD8, 0x00,         //    ** **        
    0xD8, 0x00,         //    ** **        
    0xD8, 0x00,         //    ** **        
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x1F, 0x0F,         // *****   ****    
    0x1F, 0x0F,         // *****   ****    
    0x06, 0x0C,         //  **       **    
    0xE6, 0x0C,         //  **  ***  **    
    0xE6, 0x0C,         //  **  ***  **    
    0xE6, 0x0C,         //  **  ***  **    
    0xB6, 0x0D,         //  ** ** ** **    
    0xB4, 0x05,         //   * ** ** *     
    0x1C, 0x07,         //   ***   ***     
    0x1C, 0x07,         //   ***   ***     
    0x1C, 0x07,         //   ***   ***     
    0x0C, 0x06,         //   **     **     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x8F, 0x07,         // ****   ****     
    0x8F, 0x07,         // ****   ****     
    0x06, 0x03,         //  **     **      
    0x8C, 0x01,         //   **   **       
    0xD8, 0x00,         //    ** **        
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0xD8, 0x00,         //    ** **        
    0x8C, 0x01,         //   **   **       
    0x06, 0x03,         //  **     **      
    0x8F, 0x07,         // ****   ****     
    0x8F, 0x07,         // ****   ****     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x9E, 0x07,         //  ****  ****     
    0x9E, 0x07,         //  ****  ****     
    0x0C, 0x03,         //   **    **      
    0x98, 0x01,         //    **  **       
    0xF0, 0x00,         //     ****        
    0xF0, 0x00,         //     ****        
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xF8, 0x01,         //    ******       
    0xF8, 0x01,         //    ******       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x0C, 0x03,         //   **    **      
    0x8C, 0x01,         //   **   **       
    0xC0, 0x00,         //       **        
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x30, 0x00,         //     **          
    0x18, 0x03,         //    **   **      
    0x0C, 0x03,         //   **    **      
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x01,         //      ****       
    0xE0, 0x01,         //      ****       
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xE0, 0x01,         //      ****       
    0xE0, 0x01,         //      ****       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x0C, 0x00,         //   **            
    0x0C, 0x00,         //   **            
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xC0, 0x00,         //       **        
    0xC0, 0x00,         //       **        
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x00, 0x03,         //         **      
    0x00, 0x03,         //         **      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x78, 0x00,         //    ****         
    0x78, 0x00,         //    ****         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x78, 0x00,         //    ****         
    0x78, 0x00,         //    ****         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x20, 0x00,         //      *          
    0x70, 0x00,         //     ***         
    0xD8, 0x00,         //    ** **        
    0x8C, 0x01,         //   **   **       
    0x06, 0x03,         //  **     **      
    0x02, 0x02,         //  *       *      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFF, 0x0F,         // ************    
    0xFF, 0x0F,         // ************    

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x10, 0x00,         //     *           
    0x60, 0x00,         //      **         
    0x80, 0x00,         //        *        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF8, 0x00,         //    *****        
    0xFC, 0x03,         //   ********      
    0x00, 0x03,         //         **      
    0xF8, 0x03,         //    *******      
    0xFC, 0x03,         //   ********      
    0x0E, 0x03,         //  ***    **      
    0x86, 0x03,         //  **    ***      
    0xFE, 0x07,         //  **********     
    0x78, 0x07,         //    **** ***     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x07, 0x00,         // ***             
    0x07, 0x00,         // ***             
    0x06, 0x00,         //  **             
    0x06, 0x00,         //  **             
    0xF6, 0x00,         //  ** ****        
    0xFE, 0x03,         //  *********      
    0x0E, 0x03,         //  ***    **      
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x0E, 0x03,         //  ***    **      
    0xFF, 0x03,         // **********      
    0xF7, 0x00,         // *** ****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x06,         //     **** **     
    0xFC, 0x07,         //   *********     
    0x0C, 0x06,         //   **     **     
    0x06, 0x06,         //  **      **     
    0x06, 0x00,         //  **             
    0x06, 0x00,         //  **             
    0x0E, 0x06,         //  ***     **     
    0xFC, 0x07,         //   *********     
    0xF8, 0x01,         //    ******       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x07,         //         ***     
    0x00, 0x07,         //         ***     
    0x00, 0x06,         //          **     
    0x00, 0x06,         //          **     
    0xF0, 0x06,         //     **** **     
    0xFC, 0x07,         //   *********     
    0x0C, 0x07,         //   **    ***     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x0E, 0x07,         //  ***    ***     
    0xFC, 0x0F,         //   **********    
    0xF0, 0x0E,         //     **** ***    
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x00,         //     ****        
    0xFC, 0x03,         //   ********      
    0x0C, 0x03,         //   **    **      
    0xFE, 0x07,         //  **********     
    0xFE, 0x07,         //  **********     
    0x06, 0x00,         //  **             
    0x0C, 0x06,         //   **     **     
    0xFC, 0x07,         //   *********     
    0xF0, 0x01,         //     *****       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xE0, 0x07,         //      ******     
    0xF0, 0x07,         //     *******     
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x0E,         //     **** ***    
    0xFC, 0x0F,         //   **********    
    0x0C, 0x07,         //   **    ***     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x0C, 0x07,         //   **    ***     
    0xFC, 0x07,         //   *********     
    0xF0, 0x06,         //     **** **     
    0x00, 0x06,         //          **     
    0x00, 0x07,         //         ***     
    0xF8, 0x03,         //    *******      
    0xF8, 0x01,         //    ******       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x0E, 0x00,         //  ***            
    0x0E, 0x00,         //  ***            
    0x0C, 0x00,         //   **            
    0x0C, 0x00,         //   **            
    0xEC, 0x01,         //   ** ****       
    0xFC, 0x03,         //   ********      
    0x1C, 0x03,         //   ***   **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x9E, 0x07,         //  ****  ****     
    0x9E, 0x07,         //  ****  ****     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x7C, 0x00,         //   *****         
    0x7C, 0x00,         //   *****         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFC, 0x01,         //   *******       
    0xFC, 0x01,         //   *******       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0x80, 0x01,         //        **       
    0xC0, 0x01,         //       ***       
    0xFE, 0x00,         //  *******        
    0x7E, 0x00,         //  ******         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x0E, 0x00,         //  ***            
    0x0E, 0x00,         //  ***            
    0x0C, 0x00,         //   **            
    0x0C, 0x00,         //   **            
    0xEC, 0x03,         //   ** *****      
    0xEC, 0x03,         //   ** *****      
    0x6C, 0x00,         //   ** **         
    0x3C, 0x00,         //   ****          
    0x3C, 0x00,         //   ****          
    0x6C, 0x00,         //   ** **         
    0xCC, 0x00,         //   **  **        
    0xCE, 0x07,         //  ***  *****     
    0xCE, 0x07,         //  ***  *****     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x7C, 0x00,         //   *****         
    0x7C, 0x00,         //   *****         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xBF, 0x03,         // ****** ***      
    0xFF, 0x07,         // ***********     
    0x66, 0x06,         //  **  **  **     
    0x66, 0x06,         //  **  **  **     
    0x66, 0x06,         //  **  **  **     
    0x66, 0x06,         //  **  **  **     
    0x66, 0x06,         //  **  **  **     
    0xEF, 0x0E,         // **** *** ***    
    0xEF, 0x0E,         // **** *** ***    
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xEE, 0x00,         //  *** ***        
    0xFE, 0x03,         //  *********      
    0x1C, 0x03,         //   ***   **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x9E, 0x07,         //  ****  ****     
    0x9E, 0x07,         //  ****  ****     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x00,         //     ****        
    0xFC, 0x03,         //   ********      
    0x0C, 0x03,         //   **    **      
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x0C, 0x03,         //   **    **      
    0xFC, 0x03,         //   ********      
    0xF0, 0x00,         //     ****        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF7, 0x00,         // *** ****        
    0xFF, 0x03,         // **********      
    0x0E, 0x03,         //  ***    **      
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x0E, 0x03,         //  ***    **      
    0xFE, 0x03,         //  *********      
    0xF6, 0x00,         //  ** ****        
    0x06, 0x00,         //  **             
    0x06, 0x00,         //  **             
    0x1F, 0x00,         // *****           
    0x1F, 0x00,         // *****           
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x0E,         //     **** ***    
    0xFC, 0x0F,         //   **********    
    0x0C, 0x07,         //   **    ***     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x06, 0x06,         //  **      **     
    0x0C, 0x07,         //   **    ***     
    0xFC, 0x07,         //   *********     
    0xF0, 0x06,         //     **** **     
    0x00, 0x06,         //          **     
    0x00, 0x06,         //          **     
    0x80, 0x0F,         //        *****    
    0x80, 0x0F,         //        *****    
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x9E, 0x03,         //  ****  ***      
    0xDE, 0x07,         //  **** *****     
    0x78, 0x06,         //    ****  **     
    0x38, 0x00,         //    ***          
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0xFE, 0x01,         //  ********       
    0xFE, 0x01,         //  ********       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xF0, 0x03,         //     ******      
    0xFC, 0x03,         //   ********      
    0x0C, 0x03,         //   **    **      
    0x3C, 0x00,         //   ****          
    0xF8, 0x01,         //    ******       
    0xC0, 0x03,         //       ****      
    0x0C, 0x03,         //   **    **      
    0xFC, 0x03,         //   ********      
    0xFC, 0x00,         //   ******        
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0xFE, 0x03,         //  *********      
    0xFE, 0x03,         //  *********      
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x00,         //    **           
    0x18, 0x06,         //    **    **     
    0xF8, 0x07,         //    ********     
    0xF0, 0x01,         //     *****       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x8E, 0x03,         //  ***   ***      
    0x8E, 0x03,         //  ***   ***      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x0C, 0x03,         //   **    **      
    0x8C, 0x03,         //   **   ***      
    0xFC, 0x07,         //   *********     
    0x78, 0x07,         //    **** ***     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x8F, 0x07,         // ****   ****     
    0x8F, 0x07,         // ****   ****     
    0x06, 0x03,         //  **     **      
    0x8C, 0x01,         //   **   **       
    0x8C, 0x01,         //   **   **       
    0xD8, 0x00,         //    ** **        
    0xD8, 0x00,         //    ** **        
    0x70, 0x00,         //     ***         
    0x70, 0x00,         //     ***         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x8F, 0x07,         // ****   ****     
    0x8F, 0x07,         // ****   ****     
    0x26, 0x03,         //  **  *  **      
    0x26, 0x03,         //  **  *  **      
    0xF6, 0x03,         //  ** ******      
    0xDC, 0x01,         //   *** ***       
    0xDC, 0x01,         //   *** ***       
    0x8C, 0x01,         //   **   **       
    0x8C, 0x01,         //   **   **       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x9E, 0x07,         //  ****  ****     
    0x9E, 0x07,         //  ****  ****     
    0x98, 0x01,         //    **  **       
    0xF0, 0x00,         //     ****        
    0x60, 0x00,         //      **         
    0xF0, 0x00,         //     ****        
    0x98, 0x01,         //    **  **       
    0x9E, 0x07,         //  ****  ****     
    0x9E, 0x07,         //  ****  ****     
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x8F, 0x07,         // ****   ****     
    0x8F, 0x07,         // ****   ****     
    0x06, 0x03,         //  **     **      
    0x8C, 0x01,         //   **   **       
    0x8C, 0x01,         //   **   **       
    0xD8, 0x00,         //    ** **        
    0xF8, 0x00,         //    *****        
    0x70, 0x00,         //     ***         
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x18, 0x00,         //    **           
    0x7F, 0x00,         // *******         
    0x7F, 0x00,         // *******         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x8C, 0x01,         //   **   **       
    0xC0, 0x00,         //       **        
    0x60, 0x00,         //      **         
    0x30, 0x00,         //     **          
    0x18, 0x03,         //    **   **      
    0xFC, 0x03,         //   ********      
    0xFC, 0x03,         //   ********      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0xC0, 0x01,         //       ***       
    0xE0, 0x01,         //      ****       
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x70, 0x00,         //     ***         
    0x38, 0x00,         //    ***          
    0x70, 0x00,         //     ***         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0xE0, 0x01,         //      ****       
    0xC0, 0x01,         //       ***       
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x60, 0x00,         //      **         
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x1C, 0x00,         //   ***           
    0x3C, 0x00,         //   ****          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x70, 0x00,         //     ***         
    0xE0, 0x00,         //      ***        
    0x70, 0x00,         //     ***         
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x30, 0x00,         //     **          
    0x3C, 0x00,         //   ****          
    0x1C, 0x00,         //   ***           
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 

    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x38, 0x00,         //    ***          
    0x7E, 0x06,         //  ******  **     
    0xE6, 0x07,         //  **  ******     
    0xC0, 0x03,         //       ****      
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //                 
    0x00, 0x00,         //
};

#endif