/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Finite State Machine class for HDMI Cable Status.
*
*/



#ifndef C_HDMICABLESTATUSFSM_H
#define C_HDMICABLESTATUSFSM_H



#include "pdefsm.h"


class CTVOutConfigForHDMI;
class CEDIDHandler;
class CAccessoryControlIf;
class CPDEngine;



/**
 *  Finite State Machine class for HDMI Cable Status.
 *
 *  @code
 *   ?good_class_usage_example(s)
 *  @endcode
 *
 *  @lib none.
 *  @since TB 9.2
 */
NONSHARABLE_CLASS( CHDMICableStatusFSM ): public CBase, public MPdeFSM, public MFSMForState
    {

public:

    /**
     * Two-phased constructor.
     * @param aAccessoryServer Accessory Server.
     */
    static CHDMICableStatusFSM* NewL(
            RAccessoryServer& aAccessoryServer, CPDEngine *aPdEngine );
    

    /**
    * Destructor.
    */
    virtual ~CHDMICableStatusFSM();

public: // New methods


    /**
     * This called after copy protection status change is done/tried
     * in TV Out Configuration interface.
     *
     * @since TB 9.2
     * @param aError Symbian error code. 
     * @param aCurrentStatus Current status after setting (trial). 
     * @return void.
     */
    void CopyProtectionSettingDone(
            TInt aError = KErrNone,
            TBool aCurrentStatus = EFalse );

    /**
     * This called after copy protection status change is notified
     * from TV Out Configuration interface.
     *
     * @since TB 9.2
     * @param aNewStatus New Copy Protection status. 
     * @return void.
     */
    void CopyProtectionStatusChanged( TBool aNewStatus );

    /**
     * This called after copy protection status listening has failed
     * in TV Out Configuration interface.
     *
     * @since TB 9.2
     * @param aError Symbian error code. 
     * @return void.
     */
    void CopyProtectionListenFailed( TInt aError );

    /**
     * This called after current copy protection status is read from
     * TV OU Config interface.
     *
     * @since TB 9.2
     * @param aCopyProtectionStatus Current status. 
     * @return void.
     */
    void CopyProtectionStatusGot( TBool aCopyProtectionStatus );
    
    /**
     * This called after setting change is notified
     * from TV Out Configuration interface.
     *
     * @since TB 9.2
     * @param None. 
     * @return void.
     */
    void SettingsChangedL();
    

    // from base class MPdeFSM


    /**
     * Process a command received from the Accessory FW.
     * Process command handled will be replied through the MPDAsyCmdHandler
     * interface when the command is fully handled.
     * 
     * @since TB9.2
     * @param aCommand Command to be processed.
     * @param aCmdParams Command parameters.
     * @param aAsyCmdHandler Call back interface to process command response.
     * @return TBool ETrue if command belonged to called FSM.
     */
    virtual TBool ProcessCommandL( const TProcessCmdId aCommand,
        const TASYCmdParams& aCmdParams,
        MPDAsyCmdHandler& aAsyCmdHandler );    
    
    /**
     * Get the Generic ID of connected accessory.
     * 
     * @since TB9.2
     * @param aAccPolGenericID Object where to copy actual values.
     * @return Error code. KErrNotFound if don't exist.
     */
    virtual TInt GetAccPolGenericID( TAccPolGenericID& aAccPolGenericID );

    
// from base class MFSMForBody


    /**
      * From MFSMForBody.
     * Function is called by host object to indicate that FSM can proceed to 
     * initial state and make necessary initialization actions.
     * 
     * @since TB 9.2
     * @param none. 
     * @return void.
     */
    virtual void Start();

    /**
     * Get the FSM's Id.
     *
     * @since TB 9.2
     * @param none. 
     * @return TFSMId FSM identification.
     */
    virtual TFSMId FSMID();

    /**
     * From MFSMForBody.
     * Get the id of current state.
     *
     * @since TB 9.2
     * @param none. 
     * @return TFSMState Current state identification.
     */
    virtual TFSMState CurrentStateID();

    /**
     * From MFSMForBody.
     * Function is called whenever an event that might have impact 
     * on the state machine occurs.
     *
     * @since TB 9.2
     * @param aInterfaceId Interface identification.
     * @param aEvent Event identification.
     * @return none.
     */
    virtual void Input(
            TFSMInterfaceId aInterfaceId ,
            TFSMEventId aEvent );

    /**
     * From MFSMForBody.
     * Get the pointer of current state object.
     *
     * @since TB 9.2
     * @param none. 
     * @return MFSMState* Current state's interface pointer.
     */
    virtual MFSMState* CurrentState();

    /**
     * From MFSMForBody.
     * Get the name of current state.
     *
     * @since TB 9.2
     * @param none. 
     * @return TPtrC Name of the current state.
     */
    virtual TPtrC CurrentStateName();

    /**
     * Get the ids of current main and substate id.
     *
     * @since TB 9.2
     * @param none. 
     * @return TFSMMainAndSubState Current main- and substate ids.
     *         Substate id is zero if current state havent any substates.
     */
    virtual TFSMMainAndSubState CurrentMainAndSubstateIDs();

// from base class MFSMForState

    /**
     * From MFSMForState.
     * Function is called by  current state to indicate that FSM has to change
     * its state. Pervious state has performed necessary exit actions if any.
     *
     * @since TB 9.2
     * @param aNextState Next state where to transit. 
     * @return TBool True is transition valid. False if nextstate value invalid.
     */
    virtual TBool Transit( TFSMState aNextState );
    
    CPDEngine * GetPDEngine() { return iPdEngine; }
    
protected:


private:

    /**
     * C++ default constructor.
     */
    CHDMICableStatusFSM();

    /**
     * By default Symbian OS constructor is private.
     * @param aAccessoryServer Accessory Server.
     */
    void ConstructL(
            RAccessoryServer& aAccessoryServer, CPDEngine *aPdEngine );

    /**
     * Initialize the Standby Figure settings
     * 
     * @param None
     * @return None
     */
    void SetStandbyFiguresSettingsL();
    
private: // data

    /**
     * An array for state object pointers.
     * Own
     */
    MFSMState* iStateArray[ EHDMICableStateNbrOfUsedStates ];
    
    /**
     * Identification of the current state. Used to point the 
     * corresponding state object in the above array. 
     * 0 <= a valid state id =< EHDMICableStateMaxValue
     */
    TFSMState iCurrentStateId;

    /**
     * TV Out Configuration's Listener.
     * Own
     */
    CTVOutConfigForHDMI* iTVOutConfigForHDMI; 

    /**
     * EDID data Handler.
     * Own
     */
    CEDIDHandler* iEDIDHandler;

    /**
     * Accessory Control Interface.
     * Own
     */
    CAccessoryControlIf* iAccessoryControlIf;

    /**
     * ASY Command Handler pointer.
     * Not own
     */
    MPDAsyCmdHandler* iAsyCmdHandler;
    
    /**
     * Plugged Display Engine pointer.
     * Not own
     */    
    CPDEngine *iPdEngine;
    
    };


#endif // C_HDMICABLESTATUSFSM_H
