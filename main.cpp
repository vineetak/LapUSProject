#include <QApplication>
#include <iostream>
#include <QWidget>

#include <cisstStereoVision.h>
#include <cisstStereoVisionQt.h>
#include <cisstOSAbstraction.h>

#include <sawIntuitiveDaVinci/mtsIntuitiveDaVinci.h>

#include "LapUSMainWindow.h"
#include "LapUSMouse.h"
#include "BrowserWidget.h"
#include <sstream>
#include <cisstStereoVision/svlDefinitions.h>

using namespace std;


int main(int argc,char** argv){

	/* Create new application  */
	QApplication app(argc, argv);

	/* ----------------------------- daVinci Initialization ---------------------------*/
	svlInitialize();
    // Initialize component manager so we can work with the daVinci
    mtsComponentManager *componentManager = mtsComponentManager::GetInstance();
	// Init daVinci
	mtsIntuitiveDaVinci *daVinci = new mtsIntuitiveDaVinci("daVinci", 60 /* Hz */ );
	componentManager->AddComponent(daVinci);

	// Start manager to start streaming davinci data
	componentManager->CreateAll();
    componentManager->StartAll();
    /* ---------------	------- Initialize the Live video ---------------------------------------------*/
		// create a new stream 
	svlStreamManager streamLive(1);
	// create the capture source
	svlFilterSourceVideoCapture sourceLive(1);

	if (sourceLive.LoadSettings("Live.dat") != SVL_OK) {
        cout << endl;
        sourceLive.DialogSetup();
		sourceLive.SaveSettings("Live.dat");
    }
	svlFilterImageChannelSwapper rgbSwapperLive;
	svlFilterOutput *outputLive;
	
	// TODO check if we need the rgbchannel swapper
	streamLive.SetSourceFilter(&sourceLive);
	outputLive = sourceLive.GetOutput();
	string saveFolderPath ="./SaveFolder";
	QDir d(saveFolderPath.c_str());
	if(!d.exists()){
		QDir().mkdir(saveFolderPath.c_str());
	}
	svlFilterImageFileWriter Liveimagewriter;

	ostringstream oss1;
	oss1 << saveFolderPath << "/Live_"  ;
	Liveimagewriter.SetFilePath(oss1.str(),"bmp");
	Liveimagewriter.EnableTimestamps();
    Liveimagewriter.Pause();

	outputLive->Connect(Liveimagewriter.GetInput());
	outputLive = Liveimagewriter.GetOutput();

	outputLive->Connect(rgbSwapperLive.GetInput());
	outputLive = rgbSwapperLive.GetOutput();
	
	if (streamLive.Play() != SVL_OK)
	{
		cout << "Error starting Live video!" << endl;
	}	

	/* ---------------------- Initialize the US video ---------------------------------------------*/

	svlFilterImageOpenGLQtWidget *vidWidget = new svlFilterImageOpenGLQtWidget();
	// create a new stream 
	svlStreamManager streamUS(1);
	// create the capture source
	svlFilterSourceVideoCapture sourceUS(1);

	if (sourceUS.LoadSettings("US.dat") != SVL_OK) {
        cout << endl;
        sourceUS.DialogSetup();
		sourceUS.SaveSettings("US.dat");
    }
	svlFilterImageChannelSwapper rgbSwapperUS;
	svlFilterOutput *outputUS;
	
	// TODO check if we need the rgbchannel swapper
	streamUS.SetSourceFilter(&sourceUS);
	outputUS = sourceUS.GetOutput();

	svlFilterImageFileWriter USimagewriter;

	
	ostringstream oss;
	//QDir(saveFolderPath);
	oss << saveFolderPath  <<"/US_"  ;
	USimagewriter.SetFilePath(oss.str(),"bmp");
    USimagewriter.EnableTimestamps();
    USimagewriter.Pause();
	

	outputUS->Connect(USimagewriter.GetInput());
	outputUS = USimagewriter.GetOutput();

	outputUS->Connect(rgbSwapperUS.GetInput());
	outputUS = rgbSwapperUS.GetOutput();
	if(vidWidget){
		cout<<"Connecting to the video widget";
		outputUS->Connect(vidWidget->GetInput());
		outputUS = vidWidget->GetOutput();
	}

	if (streamUS.Play() != SVL_OK)
	{
		cout << "Error starting US video!" << endl;
		
	}	
	cout << "Video Setup Complete." << endl;
	/* ------------------------ Setup the image writer ----------*/
	
	


	/* ------------------------Set up the main window ------------------------------*/

	QWidget*  window = new LapUSMainWindow(daVinci,vidWidget,USimagewriter,Liveimagewriter);
	//window->show();

	app.exec();

//	QWidget*  window = new LapUSMainWindow();
	//window->show();

	/*-------------------------Executes the application -----------*/
	// I dont know why this 
	componentManager->KillAll();
	streamUS.Release();
	return 0;
}


/* TODO list  

1) Watch for a way to minimize the widgets


*/