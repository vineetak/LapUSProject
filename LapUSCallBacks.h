//
//  video.h
//  LapUS
//
//  Created by Colin Lea on 10/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef LapUS_Callbacks_h
#define LapUS_Callbacks_h


//#include <cisstStereoVision.h>
//#include <cisstStereoVisionQt.h>
//#include <cisstMultiTask.h>
//#include <cisstCommon.h>
//#include <cisstVector.h>
//#include <cisstParameterTypes.h>

//#include "LapUSCallBackSignals.h"

#if DAVINCI_ENABLED
  #include <sawIntuitiveDaVinci/mtsIntuitiveDaVinci.h>	
#endif

class MyCallBacks {
public:
    //LapUSCallBackSignals signals;
    mtsCommandWriteBase * cbStandbySwitch;
    mtsCommandWriteBase * cbReadySwitch;
    mtsCommandWriteBase * cbMasterClutch;
    mtsCommandWriteBase * cbCameraClutch;
    mtsCommandVoid * cbHeadIn;
    mtsCommandVoid * cbHeadOut;
    mtsCommandVoid * cbClutchQuickTap;
    mtsCommandVoid * cbCameraQuickTap;
    mtsCommandWriteBase * cbMastersAsMice;
    mtsCommandWriteBase * cbMTMLClutch;
    mtsCommandWriteBase * cbMTMRClutch;
    mtsCommandWriteBase * cbMTMLeftButton;
    mtsCommandWriteBase * cbMTMRightButton;

	bool headOut, leftButton, rightButton, masterClutch, cameraClutch, clutchQuick, cameraQuick,released;
//	bool headOutState, footOn;
    bool mamLeft , mamRight , mamFootOn;

    // commenting colin's code
	MyCallBacks():/*headOut(false), headOutState(false),*/ leftButton(false), rightButton(false), masterClutch(false), cameraClutch(false), clutchQuick(false), cameraQuick(false),mamLeft(false),mamRight(false),mamFootOn(false) {}
    ~MyCallBacks() {}

    ///////////////////
    // Event callbacks.

    // Callback function for Standby Switch presses.
    void standby_switch_callback(const prmEventButton & payload)
    {
        std::cout << "EVENT: Standby Switch:" << payload << std::endl;
    }

    // Callback function for Ready Switch presses.
    void ready_switch_callback(const prmEventButton & payload)
    {
        std::cout << "EVENT: Ready Switch:" << payload << std::endl;
    }

    // Callback function for Master Clutch pedal presses.
    void master_clutch_callback(const prmEventButton & payload)
    {
		if (payload.Type() == prmEventButton::PRESSED)
		{
            // if(mamFootOn == true ){
            //     mamFootOn = false;
            //   //  mamRight = false;
            //    // mamLeft = false;
            // }
            // else 
                mamFootOn = true;
			//footOn = true;
		} else if (payload.Type() == prmEventButton::RELEASED)
		{
            mamFootOn = false;
			//footOn = false;
	//		headOutState = false;
		}
			
        std::cout << "EVENT: Master Clutch:" << payload << std::endl;
    }

    // Callback function for Camera Clutch pedal presses.
    void camera_clutch_callback(const prmEventButton & payload)
    {
        std::cout << "EVENT: Camera Clutch:" << payload << std::endl;
    }

    // Callback function for Head In.
    void head_in_callback(void)
    {
	//	headOut = false;
        std::cout << "EVENT: Head in." << std::endl;
    }

    // Callback function for Head In.
    void head_out_callback(void)
    {
	//	headOut = true;
	//	headOutState = !headOutState;
        std::cout << "EVENT: Head out." << std::endl;
    }

    // Callback function for Arm Swaps.
    void master_quicktap_callback(void)
    {
        std::cout << "EVENT: Clutch Quicktap." << std::endl;
    }

    // Callback function for Video Swaps.
    void camera_quicktap_callback(void)
    {
        // Vineeta commenting old colin's code
		// if (!headOut)
		// {
		// 	headOutState = false;
		// }
        std::cout << "EVENT: Camera Quicktap." << std::endl;
    }

    // Callback function for MaM mode.
    void masters_as_mice_callback(const prmEventButton & payload)
    {
        if(payload.Type() == prmEventButton::PRESSED)
            std::cout << "EVENT: MaM Pressed :" << payload << std::endl;
        else 
            std::cout << "EVENT: MaM: Released" << payload << std::endl;

    }

    // Callback function for MTM Clutch LEFT
    void mtm_left_clutch_callback(const prmEventButton & payload)
    {
        std::cout << "EVENT: MTM Clutch LEFT:" << payload << std::endl;
    }

    // Callback function for MTM Clutch RIGHT
    void mtm_right_clutch_callback(const prmEventButton & payload)
    {
        std::cout << "EVENT: MTM Clutch RIGHT:" << payload << std::endl;
    }

    // Callback function for MTM left button pressed
    void mtm_left_button_callback(const prmEventButton & payload)
    {
        std::cout << "EVENT: MTM Left Button:" << payload << std::endl;
        if (payload.Type() == prmEventButton::PRESSED)
        {
            if(mamLeft == true)
                mamLeft = false;
            else 
                mamLeft = true;

     //       std::cout << "EVENT: MTM Left Button:" << payload << std::endl;
        }
        else if(payload.Type() == prmEventButton::RELEASED){

     //       mamLeft = false;
       //     std::cout << "EVENT: MTM Left Button:" << payload << std::endl;
        }
    }

    // Callback function for MTM right button pressed
    void mtm_right_button_callback(const prmEventButton & payload)
    {
        if (payload.Type() == prmEventButton::PRESSED)
        {
            rightButton = true;
            if(mamRight == true && mamLeft == false) /// reset only after left is reset
                mamRight = false;
            else 
                mamRight = true;

         //   std::cout << "EVENT: MTM Right Button:" << payload << std::endl;
        }
        else if(payload.Type() == prmEventButton::RELEASED){

            released = true;
           // mamRight = false;
           // std::cout << "EVENT: MTM Right Button:" << payload << std::endl;
        }
		// rightButton = true;
  //       std::cout << "EVENT: MTM Right Button:" << payload << std::endl;
    }

    template <class _classType>
    mtsCommandVoid * MakeCommandVoid(void (_classType::*method)(void),
                                     _classType * classInstantiation, const std::string & commandName) {
        return new mtsCommandVoid(new mtsCallableVoidMethod<_classType>(method, classInstantiation),
                                  commandName);
    }

    template <class _classType, class _parameterType>
    mtsCommandWriteBase * MakeCommandWrite(void (_classType::*method)(const _parameterType&),
                                           _classType * classInstantiation, const std::string & commandName,
                                           const _parameterType & argumentPrototype) {
        return new mtsCommandWrite<_classType, _parameterType>(method, classInstantiation, commandName, argumentPrototype);
    }

    bool AddHandlers(mtsComponent * component)
    {
        mtsInterfaceProvided * providedInterface = component->GetInterfaceProvided("Console");
        if (!providedInterface) { 
			std::cout<<"Could not find the provided interface\n";
            CMN_LOG_INIT_ERROR << "Could not find daVinci MainInterface" << std::endl;
            return false;
        }

        cbHeadIn = MakeCommandVoid(&MyCallBacks::head_in_callback,
                                   this, "HeadIn");
        providedInterface->AddObserver("HeadIn", cbHeadIn);

        cbHeadOut = MakeCommandVoid(&MyCallBacks::head_out_callback,
                                    this, "HeadOut");
        providedInterface->AddObserver("HeadOut", cbHeadOut);

        cbClutchQuickTap = MakeCommandVoid(&MyCallBacks::master_quicktap_callback,
                                           this, "ClutchQuickTap");
        providedInterface->AddObserver("ClutchQuickTap", cbClutchQuickTap);

        cbCameraQuickTap = MakeCommandVoid(&MyCallBacks::camera_quicktap_callback,
                                           this, "CameraQuickTap");
        providedInterface->AddObserver("CameraQuickTap", cbCameraQuickTap);

        // Standby switch interface
        providedInterface = component->GetInterfaceProvided("Standby");
        if (!providedInterface) {
			std::cout<<"Could not find the da vinci stand by \n";
            CMN_LOG_INIT_ERROR << "Could not find daVinci Standby" << std::endl;
            return false;
        }
        cbStandbySwitch = MakeCommandWrite(&MyCallBacks::standby_switch_callback,
                                           this, "Standby", prmEventButton());
        providedInterface->AddObserver("Button", cbStandbySwitch);

        // Ready switch interface
        providedInterface = component->GetInterfaceProvided("Ready");
        if (!providedInterface) {
			std::cout<<"";
            CMN_LOG_INIT_ERROR << "Could not find daVinci Ready" << std::endl;
            return false;
        }
        cbReadySwitch = MakeCommandWrite(&MyCallBacks::ready_switch_callback,
                                         this, "Ready", prmEventButton());
        providedInterface->AddObserver("Button", cbReadySwitch);

        // Master Clutch interface
        providedInterface = component->GetInterfaceProvided("Clutch");
        if (!providedInterface) {
            CMN_LOG_INIT_ERROR << "Could not find daVinci Clutch" << std::endl;
            return false;
        }
        cbMasterClutch = MakeCommandWrite(&MyCallBacks::master_clutch_callback,
                                          this, "Clutch", prmEventButton());
        providedInterface->AddObserver("Button", cbMasterClutch);

        // Camera Control interface
        providedInterface = component->GetInterfaceProvided("Camera");
        if (!providedInterface) {
            CMN_LOG_INIT_ERROR << "Could not find daVinci Camera" << std::endl;
            return false;
        }
        cbCameraClutch = MakeCommandWrite(&MyCallBacks::camera_clutch_callback,
                                          this, "Camera", prmEventButton());
        providedInterface->AddObserver("Button", cbCameraClutch);

        // MaM interface
        providedInterface = component->GetInterfaceProvided("MastersAsMice");
        if (!providedInterface) {
            CMN_LOG_INIT_ERROR << "Could not find daVinci MastersAsMice" << std::endl;
            return false;
        }
        cbMastersAsMice = MakeCommandWrite(&MyCallBacks::masters_as_mice_callback,
                                           this, "MastersAsMice", prmEventButton());
        providedInterface->AddObserver("Button", cbMastersAsMice);

        // MaM clutches
        providedInterface = component->GetInterfaceProvided("MTML1Clutch");
        if (!providedInterface) {
            CMN_LOG_INIT_ERROR << "Could not find daVinci MTMLClutch" << std::endl;
            return false;
        }
        cbMTMLClutch = MakeCommandWrite(&MyCallBacks::mtm_left_clutch_callback,
                                        this, "MTMLClutch", prmEventButton());
        providedInterface->AddObserver("Button", cbMTMLClutch);
        providedInterface = component->GetInterfaceProvided("MTMR1Clutch");
        if (!providedInterface) {
            CMN_LOG_INIT_ERROR << "Could not find daVinci MTMRClutch" << std::endl;
            return false;
        }
        cbMTMRClutch = MakeCommandWrite(&MyCallBacks::mtm_right_clutch_callback,
                                        this, "MTMRClutch", prmEventButton());
        providedInterface->AddObserver("Button", cbMTMRClutch);

        // MTML button interface
        providedInterface = component->GetInterfaceProvided("MTML1Select");

        if (!providedInterface) {
            CMN_LOG_INIT_ERROR << "Could not find daVinci MTMLSelect" << std::endl;
            return false;
        }
        cbMTMLeftButton = MakeCommandWrite(&MyCallBacks::mtm_left_button_callback,
                                           this, "MTMLeftSelect", prmEventButton());
        providedInterface->AddObserver("Button", cbMTMLeftButton);

        // MTMR button interface
        providedInterface = component->GetInterfaceProvided("MTMR1Select");
        if (!providedInterface) {
            CMN_LOG_INIT_ERROR << "Could not find daVinci MTMRSelct" << std::endl;
            return false;
        }
        cbMTMRightButton = MakeCommandWrite(&MyCallBacks::mtm_right_button_callback,
                                            this, "MTMRightSelect", prmEventButton());
        providedInterface->AddObserver("Button", cbMTMRightButton);

		std::cout << "All event handlers added" << std::endl;

        return true;
    }

    /* TEMP -- needed for mtsCommandReadOrWrite. */
    virtual std::string GetName(void) const {
        return "daVinci example";
    }
};


#endif
