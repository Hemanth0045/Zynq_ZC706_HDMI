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
 * @file HDMI_zc706.c
 *
 *****************************************************************************/

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "iic_utils.h"
#include "zc706_hw.h"
#include "xv_frmbufrd_l2.h"  // Frame buffer Read Driver
#include "xparameters.h"
#include "xvidc.h"

XIicPs IicPs_inst;
XV_FrmbufRd_l2 FrmbufRd;
XVidC_VideoStream VidStream;

// Define a test memory address in DDR for your frame buffer canvas
#define FRAME_BUFFER_ADDR  0x10000000
#define DISPLAY_WIDTH      1920
#define DISPLAY_HEIGHT     1080
#define IMAGE_SIZE_BYTES   (DISPLAY_WIDTH * DISPLAY_HEIGHT * 3)

void FillDDRWithColorPattern() {
    // Fill the DDR memory location with a solid color [ 24 -bit pixel data (RGB8) ]
	u8 *FramePtr = (u8*)FRAME_BUFFER_ADDR;
	    int pixel_index = 0;

	    for (int i = 0; i < (DISPLAY_WIDTH * DISPLAY_HEIGHT * 3); i++) {
	        // Mode dependent: Ensure this sequence matches the exact 24-bit
	        // mapping format chosen inside your Vivado V_FRMBUF_RD block (RGB8)
		// Below format creates a plain white colour 
	        FramePtr[pixel_index + 0] = 0xFF; // Red component
	        FramePtr[pixel_index + 1] = 0xFF; // Green component
	        FramePtr[pixel_index + 2] = 0xFF; // Blue component

	        pixel_index += 3; // Step exactly 3 bytes forward for the next pixel

    }
    print("DDR Frame buffer filled with color data.\n\r");
}

int main()
{
    init_platform();

    print("DDR Frame Test application on ZC706 using on-board HDMI\n\r");

    //Configure the PS IIC Controller
    ps_iic_init(XPAR_XIICPS_0_DEVICE_ID, &IicPs_inst);

    // Set the IIC Channel to the ADV7511
    set_iic_mux(&IicPs_inst, ZC706_I2C_SELECT_HDMI, ZC706_I2C_MUX_ADDR);

    //Wait for the monitor to be connected
    wait_for_monitor(&IicPs_inst, ZC706_HDMI_ADDR);

    // ADV7511 Basic Configuration
    configure_adv7511(&IicPs_inst,ZC706_HDMI_ADDR);

    // ADV7511 ZC706 Specific configuration
    configure_adv7511_zc706(&IicPs_inst,ZC706_HDMI_ADDR);

    // Filling DDR with One color pattern
    FillDDRWithColorPattern();

    Xil_DCacheInvalidateRange(FRAME_BUFFER_ADDR, IMAGE_SIZE_BYTES);
    // STARTING THE DMA FRAME BUFFER READER
    XVFrmbufRd_Initialize(&FrmbufRd, XPAR_V_FRMBUF_RD_0_DEVICE_ID);
    XVFrmbufRd_SetBufferAddr(&FrmbufRd, FRAME_BUFFER_ADDR);

    // Configure the Video Resolution and Timing Parameters for the output stream
    VidStream.PixPerClk      = XVIDC_PPC_1;                // 1 Pixel Per Clock standard
    VidStream.ColorFormatId  = XVIDC_CSF_RGB;              // Target output stream type (RGB/YUV)
    VidStream.ColorDepth     = XVIDC_BPC_8;                // 8 bits per component (24-bit True color)
    VidStream.Timing.HActive = DISPLAY_WIDTH;              // 1920
    VidStream.Timing.VActive = DISPLAY_HEIGHT;             // 1080
    VidStream.FrameRate      = 60;                         // 60 Hz baseline refresh

    XVFrmbufRd_SetMemFormat(&FrmbufRd,(DISPLAY_WIDTH*3),XVIDC_CSF_MEM_RGB8, &VidStream);
    XVFrmbufRd_Start(&FrmbufRd);

    print("Frame buffer Read IP active and fetching from DDR.\n\r");

    print("--- Verification App Running successfully! Check your display. ---\n\r");
    xil_printf("HDMI Setup Complete!\r\n");


	while(1);


    cleanup_platform();
    return 0;
}


