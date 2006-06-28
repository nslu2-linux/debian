/**
 * @file IxNpeDl.h
 *
 * @date 14 December 2001

 * @brief This file contains the public API of the IXP400 NPE Downloader
 *        component.
 *
 * 
 * @par
 * IXP400 SW Release version 2.1
 * 
 * -- Copyright Notice --
 * 
 * @par
 * Copyright (c) 2001-2005, Intel Corporation.
 * All rights reserved.
 * 
 * @par
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * 
 * @par
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * 
 * @par
 * -- End of Copyright Notice --
*/

/**
 * @defgroup IxNpeDl Intel (R) IXP400 Software NPE-Downloader (IxNpeDl) API
 *
 * @brief The Public API for the IXP400 NPE Downloader
 *
 * @{
 */

#ifndef IXNPEDL_H
#define IXNPEDL_H

/*
 * Put the user defined include files required
 */
#include "IxOsalTypes.h"
#include "IxNpeMicrocode.h"

/*
 * #defines for function return types, etc.
 */

/**
 * @def IX_NPEDL_PARAM_ERR
 *
 * @brief NpeDl function return value for a parameter error
 */
#define IX_NPEDL_PARAM_ERR               2

/**
 * @def IX_NPEDL_RESOURCE_ERR
 *
 * @brief NpeDl function return value for a resource error
 */
#define IX_NPEDL_RESOURCE_ERR            3

/**
 * @def IX_NPEDL_CRITICAL_NPE_ERR
 *
 * @brief NpeDl function return value for a Critical NPE error occuring during
          download. Assume NPE is left in unstable condition if this value is
          returned or NPE is hang / halt.
 */
#define IX_NPEDL_CRITICAL_NPE_ERR        4

/**
 * @def IX_NPEDL_CRITICAL_MICROCODE_ERR
 *
 * @brief NpeDl function return value for a Critical Microcode error
 *        discovered during download. Assume NPE is left in unstable condition
 *        if this value is returned.
 */
#define IX_NPEDL_CRITICAL_MICROCODE_ERR  5

/**
 * @def IX_NPEDL_DEVICE_ERR
 *
 * @brief NpeDl function return value when image being downloaded
 *        is not meant for the device in use
 */
#define IX_NPEDL_DEVICE_ERR 6 

/**
 * @defgroup NPEImageID Intel (R) IXP400 Software NPE Image ID Definition
 *
 * @ingroup IxNpeDl
 *
 * @brief Definition of NPE Image ID to be passed to ixNpeDlNpeInitAndStart()
 *        as input of type UINT32 which has the following fields format:
 *
 *               Field [Bit Location] <BR>
 *               -------------------- <BR>
 *               Device ID [31 - 28] <BR>
 *               NPE ID [27 - 24] <BR>
 *               NPE Functionality ID [23 - 16] <BR>
 *               Major Release Number [15 -  8] <BR>
 *               Minor Release Number [7 - 0] <BR>
 *
 *
 * @{
 */

/**
 * @def IX_NPEDL_NPEIMAGE_FIELD_MASK
 *
 * @brief Mask for NPE Image ID's Field
 *
 * @warning <b>THIS #define HAS BEEN DEPRECATED AND SHOULD NOT BE USED.</b>
 *       It will be removed in a future release.
 *       See @ref ixNpeDlNpeInitAndStart for more information.
 */
#define IX_NPEDL_NPEIMAGE_FIELD_MASK  0xff

/**
 * @def IX_NPEDL_NPEIMAGE_NPEID_MASK
 *
 * @brief Mask for NPE Image NPE ID's Field
 *
 */
#define IX_NPEDL_NPEIMAGE_NPEID_MASK  0xf

/**
 * @def IX_NPEDL_NPEIMAGE_DEVICEID_MASK
 *
 * @brief Mask for NPE Image Device ID's Field
 *
 */
#define IX_NPEDL_NPEIMAGE_DEVICEID_MASK  0xf

/*
 * Typedefs
 */

/*
 * Enums
 */

/**
 * @brief NpeId numbers to identify NPE A, B or C
 * @note In this context, for B0 Silicon of the Intel (R) IXP42X Product Line:<br>
 *      - NPE-A has HDLC, HSS, AAL and UTOPIA Coprocessors.<br>
 *      - NPE-B has Ethernet Coprocessor.<br>
 *      - NPE-C has Ethernet, AES, DES and HASH Coprocessors.<br>
 *      - Intel (R) IXP4XX Product Line of Network Processors
 *        have different combinations of coprocessors.
 */
typedef enum
{
  IX_NPEDL_NPEID_NPEA = 0,    /**< Identifies NPE A */
  IX_NPEDL_NPEID_NPEB,        /**< Identifies NPE B */
  IX_NPEDL_NPEID_NPEC,        /**< Identifies NPE C */
  IX_NPEDL_NPEID_MAX          /**< Total Number of NPEs */
} IxNpeDlNpeId;

/**
 * @brief NPE Port ID numbers to identify NPE A, B or C
 */
typedef enum
{
  IX_NPEB_PORT = 0,  /**< Identifies NPE B */
  IX_NPEC_PORT,      /**< Identifies NPE C */
  IX_NPEA_PORT       /**< Identifies NPE A */
} IxNpePortId;

/*
 * Structs
 */

/*
 * Prototypes for interface functions
 */

/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC IX_STATUS ixNpeDlNpeInitAndStart (UINT32 imageId)
 *
 * @brief Stop, reset, download microcode (firmware) and finally start NPE.
 *
 * @param imageId UINT32 [in] - Id of the microcode image to download.
 *
 * This function locates the image specified by the <i>imageId</i> parameter
 * from the default microcode image library which is included internally by
 * this component.
 * It then stops and resets the NPE, loads the firmware image onto the NPE,
 * and then restarts the NPE.
 *
 * @note A list of valid image IDs is included in this header file.
 *       See #defines with prefix IX_NPEDL_NPEIMAGE_...
 *
 * @note This function, along with @ref ixNpeDlCustomImageNpeInitAndStart
 *       and @ref ixNpeDlLoadedImageFunctionalityGet, supercedes the following
 *       functions which are deprecated and will be removed completely in a
 *       future release:
 *       - @ref ixNpeDlNpeExecutionStop
 *       - @ref ixNpeDlNpeStopAndReset
 *       - @ref ixNpeDlNpeExecutionStart
 *
 * @pre
 *         - The Client is responsible for ensuring mutual access to the NPE.
 * @post
 *         - The NPE Instruction Pipeline will be cleared if State Information
 *           has been downloaded.
 *         - If the download fails with a critical error, the NPE may
 *           be left in an ususable state.
 * @return
 *         - IX_SUCCESS if the download was successful;
 *         - IX_NPEDL_PARAM_ERR if a parameter error occured
 *         - IX_NPEDL_CRITICAL_NPE_ERR if a critical NPE error occured during
 *           download
 *         - IX_NPEDL_CRITICAL_MICROCODE_ERR if a critical microcode error
 *           occured during download
 *         - IX_NPEDL_DEVICE_ERR if the image being loaded is not meant for 
 *           the device currently running.
 *         - IX_FAIL if NPE is not available or image is failed to be located.
 *           A warning is issued if the NPE is not present.
 */
PUBLIC IX_STATUS
ixNpeDlNpeInitAndStart (UINT32 npeImageId);

/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC IX_STATUS ixNpeDlCustomImageNpeInitAndStart (UINT32 *imageLibrary,
                                                           UINT32 imageId)
 *
 * @brief Stop, reset, download microcode (firmware) and finally start NPE
 *
 * @param imageId UINT32 [in] - Id of the microcode image to download.
 *
 * This function locates the image specified by the <i>imageId</i> parameter
 * from the specified microcode image library which is pointed to by the
 * <i>imageLibrary</i> parameter.
 * It then stops and resets the NPE, loads the firmware image onto the NPE,
 * and then restarts the NPE.
 *
 * This is a facility for users who wish to use an image from an external
 * library of NPE firmware images.  To use a standard image from the
 * built-in library, see @ref ixNpeDlNpeInitAndStart instead.
 *
 * @note A list of valid image IDs is included in this header file.
 *       See #defines with prefix IX_NPEDL_NPEIMAGE_...
 *
 * @note This function, along with @ref ixNpeDlNpeInitAndStart
 *       and @ref ixNpeDlLoadedImageFunctionalityGet, supercedes the following
 *       functions which are deprecated and will be removed completely in a
 *       future release:
 *       - @ref ixNpeDlNpeExecutionStop
 *       - @ref ixNpeDlNpeStopAndReset
 *       - @ref ixNpeDlNpeExecutionStart
 *
 * @pre
 *         - The Client is responsible for ensuring mutual access to the NPE.
 *         - The image library supplied must be in the correct format for use
 *           by the NPE Downloader (IxNpeDl) component.  Details of the library
 *           format are contained in the Functional Specification document for
 *           IxNpeDl.
 * @post
 *         - The NPE Instruction Pipeline will be cleared if State Information
 *           has been downloaded.
 *         - If the download fails with a critical error, the NPE may
 *           be left in an ususable state.
 * @return
 *         - IX_SUCCESS if the download was successful;
 *         - IX_NPEDL_PARAM_ERR if a parameter error occured
 *         - IX_NPEDL_CRITICAL_NPE_ERR if a critical NPE error occured during
 *           download
 *         - IX_NPEDL_CRITICAL_MICROCODE_ERR if a critical microcode error
 *           occured during download
 *         - IX_NPEDL_DEVICE_ERR if the image being loaded is not meant for 
 *           the device currently running.
 *         - IX_FAIL if NPE is not available or image is failed to be located.
 *           A warning is issued if the NPE is not present.
 */
PUBLIC IX_STATUS
ixNpeDlCustomImageNpeInitAndStart (UINT32 *imageLibrary,
                    UINT32 npeImageId);


/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC IX_STATUS ixNpeDlLoadedImageFunctionalityGet (IxNpeDlNpeId npeId,
                                                        UINT8 *functionalityId)
 *
 * @brief Gets the functionality of the image last loaded on a particular NPE
 *
 * @param npeId  @ref IxNpeDlNpeId [in]      - Id of the target NPE.
 * @param functionalityId UINT8* [out] - the functionality ID of the image
 *                                       last loaded on the NPE.
 *
 * This function retrieves the functionality ID of the image most recently
 * downloaded successfully to the specified NPE.  If the NPE does not contain
 * a valid image, this function returns a FAIL status.
 *
 * @warning This function is not intended for general use, as a knowledge of
 * how to interpret the functionality ID is required.  As such, this function
 * should only be used by other Access Layer components of the IXP400 Software
 * Release.
 *
 * @pre
 *
 * @post
 *
 * @return
 *     -  IX_SUCCESS if the operation was successful
 *     -  IX_NPEDL_PARAM_ERR if a parameter error occured
 *     -  IX_FAIL if the NPE does not have a valid image loaded
 */
PUBLIC IX_STATUS
ixNpeDlLoadedImageFunctionalityGet (IxNpeDlNpeId npeId,
                                    UINT8 *functionalityId);

/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC IX_STATUS ixNpeDlNpeStopAndReset (IxNpeDlNpeId npeId)
 *
 * @brief Stops and Resets an NPE
 *
 * @param npeId @ref IxNpeDlNpeId [in] - Id of the target NPE.
 *
 * This function performs a soft NPE reset by writing reset values to
 * particular NPE registers. Note that this does not reset NPE co-processors.
 * This implicitly stops NPE code execution before resetting the NPE.
 *
 * @note It is no longer necessary to call this function before downloading
 * a new image to the NPE.  It is left on the API only to allow greater control
 * of NPE execution if required.  Where appropriate, use @ref ixNpeDlNpeInitAndStart
 * or @ref ixNpeDlCustomImageNpeInitAndStart instead.
 *
 * @warning <b>THIS FUNCTION HAS BEEN DEPRECATED AND SHOULD NOT BE USED.</b>
 *       It will be removed in a future release.
 *       See @ref ixNpeDlNpeInitAndStart and @ref ixNpeDlCustomImageNpeInitAndStart.
 *
 * @pre
 *     - The Client is responsible for ensuring mutual access to the NPE.
 *
 * @post
 *
 * @return
 *      - IX_SUCCESS if the operation was successful
 *      - IX_NPEDL_PARAM_ERR if a parameter error occured
 *      - IX_FAIL otherwise
 *      - IX_NPEDL_CRITICAL_NPE_ERR failed to reset NPE due to timeout error. 
 *        Timeout error could happen if NPE hang
 */
PUBLIC IX_STATUS
ixNpeDlNpeStopAndReset (IxNpeDlNpeId npeId);

/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC IX_STATUS ixNpeDlNpeExecutionStart (IxNpeDlNpeId npeId)
 *
 * @brief Starts code execution on a NPE
 *
 * @param npeId @ref IxNpeDlNpeId [in] - Id of the target NPE
 *
 * Starts execution of code on a particular NPE.  A client would typically use
 * this after a download to NPE is performed, to start/restart code execution
 * on the NPE.
 *
 * @note It is no longer necessary to call this function after downloading
 * a new image to the NPE.  It is left on the API only to allow greater control
 * of NPE execution if required.  Where appropriate, use @ref ixNpeDlNpeInitAndStart
 * or @ref ixNpeDlCustomImageNpeInitAndStart instead.
 *
 * @warning <b>THIS FUNCTION HAS BEEN DEPRECATED AND SHOULD NOT BE USED.</b>
 *       It will be removed in a future release.
 *       See @ref ixNpeDlNpeInitAndStart and @ref ixNpeDlCustomImageNpeInitAndStart.
 *
 * @pre
 *     - The Client is responsible for ensuring mutual access to the NPE.
 *     - Note that this function does not set the NPE Next Program Counter
 *       (NextPC), so it should be set beforehand if required by downloading
 *       appropriate State Information (using ixNpeDlVersionDownload()).
 *
 * @post
 *
 * @return
 *      - IX_SUCCESS if the operation was successful
 *      - IX_NPEDL_PARAM_ERR if a parameter error occured
 *      - IX_FAIL otherwise
 */
PUBLIC IX_STATUS
ixNpeDlNpeExecutionStart (IxNpeDlNpeId npeId);

/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC IX_STATUS ixNpeDlNpeExecutionStop (IxNpeDlNpeId npeId)
 *
 * @brief Stops code execution on a NPE
 *
 * @param npeId @ref IxNpeDlNpeId [in] - Id of the target NPE
 *
 * Stops execution of code on a particular NPE.  This would typically be used
 * by a client before a download to NPE is performed, to stop code execution on
 * an NPE, unless ixNpeDlNpeStopAndReset() is used instead.  Unlike
 * ixNpeDlNpeStopAndReset(), this function only halts the NPE and leaves
 * all registers and settings intact. This is useful, for example, between
 * stages of a multi-stage download, to stop the NPE prior to downloading the
 * next image while leaving the current state of the NPE intact..
 *
 * @warning <b>THIS FUNCTION HAS BEEN DEPRECATED AND SHOULD NOT BE USED.</b>
 *       It will be removed in a future release.
 *       See @ref ixNpeDlNpeInitAndStart and @ref ixNpeDlCustomImageNpeInitAndStart.
 *
 * @pre
 *     - The Client is responsible for ensuring mutual access to the NPE.
 *
 * @post
 *
 * @return
 *      - IX_SUCCESS if the operation was successful
 *      - IX_NPEDL_PARAM_ERR if a parameter error occured
 *      - IX_FAIL otherwise
 */
PUBLIC IX_STATUS
ixNpeDlNpeExecutionStop (IxNpeDlNpeId npeId);

/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC IX_STATUS ixNpeDlUnload (void)
 *
 * @brief This function will uninitialise the IxNpeDl component.
 *
 * This function will uninitialise the IxNpeDl component.  It should only be
 * called once, and only if the IxNpeDl component has already been initialised by
 * calling any of the following functions:
 * - @ref ixNpeDlNpeInitAndStart
 * - @ref ixNpeDlCustomImageNpeInitAndStart
 *
 * If possible, this function should be called before a soft reboot or unloading
 * a kernel module to perform any clean up operations required for IxNpeDl.
 *
 * The following actions will be performed by this function:
 * - Unmapping of any kernel memory mapped by IxNpeDl
 *
 * @return
 *      - IX_SUCCESS if the operation was successful
 *      - IX_FAIL otherwise
 */
PUBLIC IX_STATUS 
ixNpeDlUnload (void);

/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC void ixNpeDlStatsShow (void)
 *
 * @brief This function will display run-time statistics from the IxNpeDl
 *        component
 *
 * @return none
 */
PUBLIC void
ixNpeDlStatsShow (void);

/**
 * @ingroup IxNpeDl
 *
 * @fn PUBLIC void ixNpeDlStatsReset (void)
 *
 * @brief This function will reset the statistics of the IxNpeDl component
 *
 * @return none
 */
PUBLIC void
ixNpeDlStatsReset (void);

#endif /* IXNPEDL_H */

/**
 * @} defgroup IxNpeDl
 */


