// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// Example CTestStep derived implementation
// 
//

/**
 @file NavModelFinalCheckAndCleanupStep.cpp
*/
#include "NavModelFinalCheckAndCleanupStep.h"
#include "Te_LbsAssistanceDataSuiteDefs.h"
#include "Te_LbsAssistanceDataSuiteServer.h"
#include "NavModelFinalCheckAndCleanupStep.h"

CNavModelFinalCheckAndCleanupStep::~CNavModelFinalCheckAndCleanupStep()
/**
 * Destructor
 */
	{
	}

CNavModelFinalCheckAndCleanupStep::CNavModelFinalCheckAndCleanupStep(CTe_LbsAssistanceDataSuite& aOwningServer):
	CTe_LbsAssistanceDataSuiteStepBase(aOwningServer)
	{
	// **MUST** call SetTestStepName in the constructor as the controlling
	// framework uses the test step name immediately following construction to set
	// up the step's unique logging ID.
	SetTestStepName(KNavModelFinalCheckAndCleanupStep);
	}

TVerdict CNavModelFinalCheckAndCleanupStep::doTestStepPreambleL()
/**
 * @return - TVerdict code
 * Override of base class virtual
 */
	{
	SetTestStepResult(EPass);

    // First time here Ephemeris may not exist in the node. Make sure to
    // create it before starting the step
    iServer.iNavigationModelReader.DataBuffer()=iServer.iNavigationModelBuilder.DataBuffer();
   	TBool exists = iServer.iNavigationModelReader.FieldExists(TUEPositioningGpsNavigationModel::ENavigationModelSatelliteInfoArray);
   	if(!exists)
		{
        ERR_PRINTF1(_L("Array doesn't exist"));
       	SetTestStepResult(EFail);	
   		}
   	else
   		{
   		iServer.iNavigationModelReader.GetArrayReader(TUEPositioningGpsNavigationModel::ENavigationModelSatelliteInfoArray,iServer.iNavModelSatInfoArrayReader);
   		}
   		
   	return TestStepResult();
	}

// Perform some random value checks
//
//
TVerdict CNavModelFinalCheckAndCleanupStep::doTestStepL()
/**
 * @return - TVerdict code
 * Override of base class pure virtual
 * Our implementation only gets called if the base class doTestStepPreambleL() did
 * not leave. That being the case, the current test result value will be EPass.
 */
	{
	TUint value;
	// From array node at index zero, check that Ephemeris has been set and the following
	// fields are as follow:
	// CodeOnL2: 1; FitInterval:19; IDot: 28
	iServer.iNavModelSatInfoArrayReader.GetFieldReader(0, iServer.iNavModelSatInfoReader);
	
	if(!iServer.iNavModelSatInfoReader.FieldExists(TNavigationModelSatInfo::EEphemerisParameter))
		{
		ERR_PRINTF1(_L("Ephemeris missing"));
		SetTestStepResult(EFail);	
		User::Leave(KErrNotFound);
		}	
	iServer.iNavModelSatInfoReader.GetFieldReader(TNavigationModelSatInfo::EEphemerisParameter, iServer.iEphemerisReader);

	if(!iServer.iEphemerisReader.FieldExists(TEphemerisParameter::ECodeOnL2))
		{
		ERR_PRINTF1(_L("Missing ECodeOnL2 at index 0"));
    	SetTestStepResult(EFail);
		}
	else
		{
		TUint value;
		iServer.iEphemerisReader.GetField(TEphemerisParameter::ECodeOnL2,value);
		if(value != 1)
			{
			ERR_PRINTF1(_L("ECodeOnL2 value set different from value retrieved"));
    	    SetTestStepResult(EFail);
			}
		}
	
	 if(!iServer.iEphemerisReader.FieldExists(TEphemerisParameter::EFitInterval))
		{
		ERR_PRINTF1(_L("Missing EFitInterval at index 0"));
    	SetTestStepResult(EFail);
		}
	 else
		{
		iServer.iEphemerisReader.GetField(TEphemerisParameter::EFitInterval,value);
		if(value != 19)
			{
			ERR_PRINTF1(_L("EFitInterval value set different from value retrieved"));
    	    SetTestStepResult(EFail);
			}
		}
	
	 if(!iServer.iEphemerisReader.FieldExists(TEphemerisParameter::EIDot))
		{
		ERR_PRINTF1(_L("Missing EIDot at index 0"));
    	SetTestStepResult(EFail);
		}
	 else
		{
		iServer.iEphemerisReader.GetField(TEphemerisParameter::EIDot,value);
		if(value != 28)
			{
			ERR_PRINTF1(_L("EIDot value set different from value retrieved"));
    	    SetTestStepResult(EFail);
			}
		}
	
	// From array node at index 31, check that Ephemeris has been set and the following
	// fields are as follow:
	// CodeOnL2: 32; FitInterval:50; IDot: 59
	iServer.iNavModelSatInfoArrayReader.GetFieldReader(31, iServer.iNavModelSatInfoReader);
	
	if(!iServer.iNavModelSatInfoReader.FieldExists(TNavigationModelSatInfo::EEphemerisParameter))
		{
		ERR_PRINTF1(_L("Ephemeris missing"));
		SetTestStepResult(EFail);	
		User::Leave(KErrNotFound);
		}	
		
	iServer.iNavModelSatInfoReader.GetFieldReader(TNavigationModelSatInfo::EEphemerisParameter, iServer.iEphemerisReader);

	if(!iServer.iEphemerisReader.FieldExists(TEphemerisParameter::ECodeOnL2))
		{
		ERR_PRINTF1(_L("Missing ECodeOnL2 at index 0"));
    	SetTestStepResult(EFail);
		}
	else
		{
		TUint value;
		iServer.iEphemerisReader.GetField(TEphemerisParameter::ECodeOnL2,value);
		if(value != 32)
			{
			ERR_PRINTF1(_L("ECodeOnL2 value set different from value retrieved"));
    	    SetTestStepResult(EFail);
			}
		}
	
	if(!iServer.iEphemerisReader.FieldExists(TEphemerisParameter::EFitInterval))
		{
		ERR_PRINTF1(_L("Missing EFitInterval at index 0"));
    	SetTestStepResult(EFail);
		}
	else
		{
		iServer.iEphemerisReader.GetField(TEphemerisParameter::EFitInterval,value);
		if(value != 50)
			{
			ERR_PRINTF1(_L("EFitInterval value set different from value retrieved"));
    	    SetTestStepResult(EFail);
			}
		}
	
	if(!iServer.iEphemerisReader.FieldExists(TEphemerisParameter::EIDot))
		{
		ERR_PRINTF1(_L("Missing EIDot at index 0"));
    	SetTestStepResult(EFail);
		}
	else
		{
		iServer.iEphemerisReader.GetField(TEphemerisParameter::EIDot,value);
		if(value != 59)
			{
			ERR_PRINTF1(_L("EIDot value set different from value retrieved"));
    	    SetTestStepResult(EFail);
			}
		}
		
	return TestStepResult();
	
	}


TVerdict CNavModelFinalCheckAndCleanupStep::doTestStepPostambleL()
/**
 * @return - TVerdict code
 * Override of base class virtual
 */
	{
	// Close the Navigation Model property to prevent 
	// TEF warnings due to memory leakage.
	iServer.iNavigationModelReader.Close();
	iServer.iNavigationModelBuilder.Close();
	return TestStepResult();
	}
