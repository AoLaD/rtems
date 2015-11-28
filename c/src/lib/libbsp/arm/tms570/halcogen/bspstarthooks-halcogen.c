#include <bsp.h>
#include <bsp/start.h>

#include "sys_common.h"
#include "system.h"
#include "sys_vim.h"
#include "sys_core.h"
#include "sys_selftest.h"
#include "esm.h"
#include "mibspi.h"

BSP_START_TEXT_SECTION void bsp_start_hook_0( void )
{
    /* Work Around for Errata DEVICE#140: ( Only on Rev A silicon)
     *
     * Errata Description:
     *            The Core Compare Module(CCM-R4) may cause nERROR to be asserted after a cold power-on
     * Workaround:
     *            Clear ESM Group2 Channel 2 error in ESMSR2 and Compare error in CCMSR register */
    if (DEVICE_ID_REV == 0x802AAD05U)
    {
        _esmCcmErrorsClear_();
    }

    /* Enable CPU Event Export */
    /* This allows the CPU to signal any single-bit or double-bit errors detected
     * by its ECC logic for accesses to program flash or data RAM.
     */
    _coreEnableEventBusExport_();

    /* Workaround for Errata CORTEXR4 66 */
    _errata_CORTEXR4_66_();

    /* Workaround for Errata CORTEXR4 57 */
    _errata_CORTEXR4_57_();

    /* check for power-on reset condition */
    /*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if ((SYS_EXCEPTION & POWERON_RESET) != 0U)
    {
        /* clear all reset status flags */
        SYS_EXCEPTION = 0xFFFFU;

      /* continue with normal start-up sequence */
    }
    /*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    else if ((SYS_EXCEPTION & OSC_FAILURE_RESET) != 0U)
    {
        /* Reset caused due to oscillator failure.
        Add user code here to handle oscillator failure */
    }
    /*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    else if ((SYS_EXCEPTION & WATCHDOG_RESET) !=0U)
    {
        /* Reset caused due
         *  1) windowed watchdog violation - Add user code here to handle watchdog violation.
         *  2) ICEPICK Reset - After loading code via CCS / System Reset through CCS
         */
        /* Check the WatchDog Status register */
        if(WATCHDOG_STATUS != 0U)
        {
            /* Add user code here to handle watchdog violation. */
            /* Clear the Watchdog reset flag in Exception Status register */
            SYS_EXCEPTION = WATCHDOG_RESET;
        }
        else
        {
            /* Clear the ICEPICK reset flag in Exception Status register */
            SYS_EXCEPTION = ICEPICK_RESET;
        }
    }
    /*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    else if ((SYS_EXCEPTION & CPU_RESET) !=0U)
    {
        /* Reset caused due to CPU reset.
        CPU reset can be caused by CPU self-test completion, or
        by toggling the "CPU RESET" bit of the CPU Reset Control Register. */

        /* clear all reset status flags */
        SYS_EXCEPTION = CPU_RESET;

    }
    /*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    else if ((SYS_EXCEPTION & SW_RESET) != 0U)
    {
        /* Reset caused due to software reset.
        Add user code to handle software reset. */
    }
    else
    {
        /* Reset caused by nRST being driven low externally.
        Add user code to handle external reset. */
    }

    /* Check if there were ESM group3 errors during power-up.
     * These could occur during eFuse auto-load or during reads from flash OTP
     * during power-up. Device operation is not reliable and not recommended
     * in this case.
     * An ESM group3 error only drives the nERROR pin low. An external circuit
     * that monitors the nERROR pin must take the appropriate action to ensure that
     * the system is placed in a safe state, as determined by the application.
     */
    if ((esmREG->SR1[2]) != 0U)
    {
    /*SAFETYMCUSW 5 C MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
    /*SAFETYMCUSW 26 S MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
        for(;;)
        {
        }/* Wait */
    }

    /* Initialize System - Clock, Flash settings with Efuse self check */
    systemInit();

    /* Workaround for Errata PBIST#4 */
    errata_PBIST_4();

    /* Run a diagnostic check on the memory self-test controller.
     * This function chooses a RAM test algorithm and runs it on an on-chip ROM.
     * The memory self-test is expected to fail. The function ensures that the PBIST controller
     * is capable of detecting and indicating a memory self-test failure.
     */
    pbistSelfCheck();

    /* Run PBIST on STC ROM */
    pbistRun((uint32)STC_ROM_PBIST_RAM_GROUP,
             ((uint32)PBIST_TripleReadSlow | (uint32)PBIST_TripleReadFast));

    /* Wait for PBIST for STC ROM to be completed */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while(pbistIsTestCompleted() != TRUE)
    {
    }/* Wait */

    /* Check if PBIST on STC ROM passed the self-test */
    if( pbistIsTestPassed() != TRUE)
    {
        /* PBIST and STC ROM failed the self-test.
         * Need custom handler to check the memory failure
         * and to take the appropriate next step.
         */

        pbistFail();

    }

    /* Disable PBIST clocks and disable memory self-test mode */
    pbistStop();

	/* Run PBIST on PBIST ROM */
    pbistRun((uint32)PBIST_ROM_PBIST_RAM_GROUP,
             ((uint32)PBIST_TripleReadSlow | (uint32)PBIST_TripleReadFast));

    /* Wait for PBIST for PBIST ROM to be completed */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while(pbistIsTestCompleted() != TRUE)
    {
    }/* Wait */

    /* Check if PBIST ROM passed the self-test */
    if( pbistIsTestPassed() != TRUE)
    {
        /* PBIST and STC ROM failed the self-test.
         * Need custom handler to check the memory failure
         * and to take the appropriate next step.
         */

        pbistFail();

    }

    /* Disable PBIST clocks and disable memory self-test mode */
    pbistStop();

#if 0

    /* Disable RAM ECC before doing PBIST for Main RAM */
    _coreDisableRamEcc_();

    /* Run PBIST on CPU RAM.
     * The PBIST controller needs to be configured separately for single-port and dual-port SRAMs.
     * The CPU RAM is a single-port memory. The actual "RAM Group" for all on-chip SRAMs is defined in the
     * device datasheet.
     */
    pbistRun(0x08300020U, /* ESRAM Single Port PBIST */
             (uint32)PBIST_March13N_SP);

    /* Wait for PBIST for CPU RAM to be completed */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while(pbistIsTestCompleted() != TRUE)
    {
    }/* Wait */

    /* Check if CPU RAM passed the self-test */
    if( pbistIsTestPassed() != TRUE)
    {
        /* CPU RAM failed the self-test.
         * Need custom handler to check the memory failure
         * and to take the appropriate next step.
         */

        pbistFail();
    }

    /* Disable PBIST clocks and disable memory self-test mode */
    pbistStop();


    /* Initialize CPU RAM.
     * This function uses the system module's hardware for auto-initialization of memories and their
     * associated protection schemes. The CPU RAM is initialized by setting bit 0 of the MSIENA register.
     * Hence the value 0x1 passed to the function.
     * This function will initialize the entire CPU RAM and the corresponding ECC locations.
     */
    memoryInit(0x1U);

    /* Enable ECC checking for TCRAM accesses.
     * This function enables the CPU's ECC logic for accesses to B0TCM and B1TCM.
     */
    _coreEnableRamEcc_();

#endif

    /* Start PBIST on all dual-port memories */
    /* NOTE : Please Refer DEVICE DATASHEET for the list of Supported Dual port Memories.
       PBIST test performed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
     */
    pbistRun(  (uint32)0x00000000U    /* EMAC RAM */
             | (uint32)0x00000000U    /* USB RAM */
             | (uint32)0x00000800U    /* DMA RAM */
             | (uint32)0x00000200U    /* VIM RAM */
             | (uint32)0x00000040U    /* MIBSPI1 RAM */
             | (uint32)0x00000080U    /* MIBSPI3 RAM */
             | (uint32)0x00000100U    /* MIBSPI5 RAM */
             | (uint32)0x00000004U    /* CAN1 RAM */
             | (uint32)0x00000008U    /* CAN2 RAM */
             | (uint32)0x00000010U    /* CAN3 RAM */
             | (uint32)0x00000400U    /* ADC1 RAM */
             | (uint32)0x00020000U    /* ADC2 RAM */
             | (uint32)0x00001000U    /* HET1 RAM */
             | (uint32)0x00040000U    /* HET2 RAM */
             | (uint32)0x00002000U    /* HTU1 RAM */
             | (uint32)0x00080000U    /* HTU2 RAM */
             | (uint32)0x00004000U    /* RTP RAM */
             | (uint32)0x00008000U    /* FRAY RAM */
             ,(uint32) PBIST_March13N_DP);

#if 0

    /* Test the CPU ECC mechanism for RAM accesses.
     * The checkBxRAMECC functions cause deliberate single-bit and double-bit errors in TCRAM accesses
     * by corrupting 1 or 2 bits in the ECC. Reading from the TCRAM location with a 2-bit error
     * in the ECC causes a data abort exception. The data abort handler is written to look for
     * deliberately caused exception and to return the code execution to the instruction
     * following the one that caused the abort.
     */
    checkRAMECC();

    /* Wait for PBIST for CPU RAM to be completed */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while(pbistIsTestCompleted() != TRUE)
    {
    }/* Wait */


    /* Check if CPU RAM passed the self-test */
    if( pbistIsTestPassed() != TRUE)
    {

        /* CPU RAM failed the self-test.
         * Need custom handler to check the memory failure
         * and to take the appropriate next step.
         */
        pbistFail();
    }

#endif

    /* Disable PBIST clocks and disable memory self-test mode */
    pbistStop();

    /* Release the MibSPI1 modules from local reset.
     * This will cause the MibSPI1 RAMs to get initialized along with the parity memory.
     */
     mibspiREG1->GCR0 = 0x1U;

    /* Release the MibSPI3 modules from local reset.
     * This will cause the MibSPI3 RAMs to get initialized along with the parity memory.
     */
    mibspiREG3->GCR0 = 0x1U;

    /* Release the MibSPI5 modules from local reset.
     * This will cause the MibSPI5 RAMs to get initialized along with the parity memory.
     */
    mibspiREG5->GCR0 = 0x1U;

    /* Enable parity on selected RAMs */
    enableParity();

    /* Initialize all on-chip SRAMs except for MibSPIx RAMs
     * The MibSPIx modules have their own auto-initialization mechanism which is triggered
     * as soon as the modules are brought out of local reset.
     */
    /* The system module auto-init will hang on the MibSPI RAM if the module is still in local reset.
     */
    /* NOTE : Please Refer DEVICE DATASHEET for the list of Supported Memories and their channel numbers.
              Memory Initialization is perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
     */
    memoryInit( (uint32)((uint32)1U << 1U)    /* DMA RAM */
              | (uint32)((uint32)1U << 2U)    /* VIM RAM */
              | (uint32)((uint32)1U << 5U)    /* CAN1 RAM */
              | (uint32)((uint32)1U << 6U)    /* CAN2 RAM */
              | (uint32)((uint32)1U << 10U)   /* CAN3 RAM */
              | (uint32)((uint32)1U << 8U)    /* ADC1 RAM */
              | (uint32)((uint32)1U << 14U)   /* ADC2 RAM */
              | (uint32)((uint32)1U << 3U)    /* HET1 RAM */
              | (uint32)((uint32)1U << 4U)    /* HTU1 RAM */
              | (uint32)((uint32)1U << 15U)   /* HET2 RAM */
              | (uint32)((uint32)1U << 16U)   /* HTU2 RAM */
              );

    /* Disable parity */
    disableParity();

    /* Test the parity protection mechanism for peripheral RAMs
       NOTE : Please Refer DEVICE DATASHEET for the list of Supported Memories with parity.
                 Parity Self check is perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
    */

    het1ParityCheck();
    htu1ParityCheck();
    het2ParityCheck();
    htu2ParityCheck();
    adc1ParityCheck();
    adc2ParityCheck();
    can1ParityCheck();
    can2ParityCheck();
    can3ParityCheck();
    vimParityCheck();
    dmaParityCheck();

/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((mibspiREG1->FLG & 0x01000000U) == 0x01000000U)
    {
    }/* Wait */
    /* wait for MibSPI1 RAM to complete initialization */
/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((mibspiREG3->FLG & 0x01000000U) == 0x01000000U)
    {
    }/* Wait */
    /* wait for MibSPI3 RAM to complete initialization */
/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((mibspiREG5->FLG & 0x01000000U) == 0x01000000U)
    {
    }/* Wait */
    /* wait for MibSPI5 RAM to complete initialization */

    mibspi1ParityCheck();
    mibspi3ParityCheck();
    mibspi5ParityCheck();

    /* Enable IRQ offset via Vic controller */
    _coreEnableIrqVicOffset_();

    /* Initialize VIM table */
    vimInit();

    /* Configure system response to error conditions signaled to the ESM group1 */
    /* This function can be configured from the ESM tab of HALCoGen */
    esmInit();

}

BSP_START_TEXT_SECTION void bsp_start_hook_1( void )
{
  bsp_start_copy_sections();
  bsp_start_clear_bss();

  /* At this point we can use objects outside the .start section  */

  _mpuInit_();
  emif_SDRAMInit();
  sciInit();
}
