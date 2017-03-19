#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <raspicam/raspicam_cv.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stropts.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/input.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>
#include <omp.h>
#include <limits>
#include <cmath>

/*----------------------------------------------------------------------------*/
/*Variables globales*/
/*IHM*/
Mat img;

/*----------------------------------------------------------------------------*/
/*Fonctions*/
// Tous les algorithmes de tracking
void tracking_test();

/*---------------------------------------------------------------------------*/

void tracking_test(){
        Mat image;
	    cap.grab();
	    cap.retrieve(image);
		
    	cvtColor(image, imgHSV, COLOR_BGR2HSV);

    		
    	inRange(imgHSV, Scalar(170, 0, 0), Scalar(179,255,255), imgCalibre);
    		
    	Moments oMoments = moments(imgCalibre);

    	double dM01 = oMoments.m01;
    	double dM10 = oMoments.m10;
    	double dSurface = oMoments.m00;
   
    	imgCalibre = Mat::zeros(imgCalibre.size(), CV_8UC3);
    	
    	return ();
    	//return ce qu'il faut
     }
     

int main(int argc, char** argv){
    // Algorithme de tracking de base
    //  Appeler l'algo ?
}
