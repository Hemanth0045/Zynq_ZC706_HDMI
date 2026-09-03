/******************************************************************************
 *  Copyright (c) 2022, Xilinx, Inc.
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1.  Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *
 *  2.  Redistributions in binary form must reproduce the above copyright 
 *      notice, this list of conditions and the following disclaimer in the 
 *      documentation and/or other materials provided with the distribution.
 *
 *  3.  Neither the name of the copyright holder nor the names of its 
 *      contributors may be used to endorse or promote products derived from 
 *      this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION). HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

/******************************************************************************
 * @file zc706_hw.h
 *
 * Library files for IIC control on ZC706
 *
 *****************************************************************************/

#ifndef SRC_ZC706_HDMI_H_
#define SRC_ZC706_HDMI_H_

// ZC706 I2C Addresses
#define ZC706_I2C_MUX_ADDR	0x74 // (PCA9458)
#define ZC706_USRCLK_ADDR	0x5D // (SI570)
#define ZC706_HDMI_ADDR		0x39 // (ADV7511)
#define ZC706_PMBUS0_ADDR	0x34 // (UCD9248)
#define ZC706_PMBUS1_ADDR	0x35 // (UCD9248)
#define ZC706_PMBUS2_ADDR	0x36 // (UCD9248)
#define ZC706_FMC_IPMI_ADDR	0x50 // (24LC02)

// ZC706 Mux Selections
#define ZC706_I2C_SELECT_USRCLK		0x01
#define ZC706_I2C_SELECT_HDMI      	0x02
#define ZC706_I2C_SELECT_EEPROM    	0x04
#define ZC706_I2C_SELECT_EXPANDER  	0x08
#define ZC706_I2C_SELECT_RTC       	0x10
#define ZC706_I2C_SELECT_FMC1      	0x20
#define ZC706_I2C_SELECT_FMC2      	0x40
#define ZC706_I2C_SELECT_PMBUS     	0x80

// ADV7511 ZC706 Configuration
#define ADV7511_FORMAT_ID_ZC706		0x01  //


#endif /* SRC_ZC706_HDMI_H_ */
