/******************************************************************************
*
* Copyright (C) 2019 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
*******************************************************************************/
/******************************************************************************/
/**
* @file xpciepsu_ep.h
*
* This file contains the software API definition of the Xilinx PSU PCI IP
* (psu_pcie). This driver provides "C" function interface to application/upper
* layer to access the hardware.
*
* <b>Features</b>
* The driver provides its user with entry points
*   - To initialize and configure itself and the hardware
*   - To access PCIe configuration space locally
*
* <b>Driver Initialization & Configuration</b>
*
* The XPciePsu_Config structure is used by the driver to configure itself. This
* configuration structure is typically created by the tool-chain based on HW
* build properties.
*
* To support multiple runtime loading and initialization strategies employed
* by various operating systems, the driver instance can be initialized in the
* following way:
*
*   - XPciePsu_LookupConfig(DeviceId) - Use the device identifier to find the
*   static configuration structure defined in xpciepsu_g.c. This is setup by
*   the tools.
*
*   - XPciePsu_EP_CfgInitialize(InstancePtr, CfgPtr, EffectiveAddress) -
*   Uses a configuration structure provided by the caller. If running in a
*   system with address translation, the provided virtual memory base address
*   replaces the physical address present in the configuration structure.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------
* 1.0	tk	02/13/2019	First release
* </pre>
*
*******************************************************************************/
#ifndef XPCIEPSU_EP_H_
#define XPCIEPSU_EP_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************** Include Files *******************************/

#include "xpciepsu.h"

/**************************** Constant Definitions ****************************/

/******************** Macros (Inline Functions) Definitions *******************/

/****************************** Type Definitions ******************************/
#define INGRESS_SIZE				0x20

#define COMMAND_REG					(0x4U)
#define BAR0_OFFSET_LO				(0x10U)
#define BAR0_OFFSET_HI				(0x14U)

#define PCIE_ENUMERATED_STATUS		0x00000002U

#define DREG_CONTROL				(0x288U)
#define DREG_BASE_LO				(0x290U)
#define DREG_BASE_HI				(0x294U)

#define INGRESS0_CONTROL			(0x808U)
#define INGRESS0_SRC_BASE_LO		(0x810U)
#define INGRESS0_SRC_BASE_HI		(0x814U)
#define INGRESS0_DST_BASE_LO		(0x818U)
#define INGRESS0_DST_BASE_HI		(0x81CU)

#define MSGF_DMA_MASK               (0x464)

#define PCIE_LINK_UP				0x000000001U
#define ECAM_ENABLE					0x000000001U
#define INGRESS_ENABLE				0x000000001U
#define INGRESS_SECURITY_ENABLE		0x000000004U
#define DMA_ENABLE					0x000000001U
#define BREG_SIZE					0x000000004U


#define DMA0_CHAN_AXI_INTR              (0x68)
#define AXI_INTR_ENABLE                 0x00000001U
#define MSGF_DMA_INTR_ENABLE            0x00000001U

#define BREG_SIZE_SHIFT					16
#define INGRESS_SIZE_SHIFT				16

#define BREG_SIZE_MASK					0x00030000U
#define INGRESS_SIZE_MASK				0x001F0000U

#define INGRESS_SIZE_ENCODING			0x00000008U /* 2^(12+8) = 1MB */

#define INGRESS_RD_WR_ATTR				0xFF800000U

#define ENUMERATION_WAIT_TIME			10

/***************************** Function Prototypes ****************************/
void XPciePsu_EP_BridgeInitialize(XPciePsu *PciePsuPtr);
void XPciePsu_EP_CfgInitialize(XPciePsu *PciePsuPtr,
		XPciePsu_Config *ConfigPtr);
void XPciePsu_EP_WaitForLinkup(XPciePsu *PciePsuPtr);
void XPciePsu_EP_WaitForEnumeration(XPciePsu *PciePsuPtr);
int XPciePsu_EP_SetupIngress(XPciePsu *PciePsuPtr, u32 IngressNum,
		u32 BarNum, u32 DstLo);


#ifdef __cplusplus
}
#endif

#endif /* XPCIEPSU_EP_H_ */