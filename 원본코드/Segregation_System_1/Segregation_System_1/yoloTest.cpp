//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include "detection.h"
//
//using namespace std;
//using namespace cv;
//
//int main()
//{
//    VideoCapture cap(0);
//
//    Inference inf("best.onnx", Size(640, 640), "model.txt", false);
//    loadClassNames("model.txt");
//
//    Mat frame;
//    int frameCounter = 0;
//
//    while (true)
//    {
//        cap >> frame;
//        if (frame.empty()) {
//            cerr << "Error: Could not grab frame!" << endl;
//            break;
//        }
//
//        vector<Detection> detections = inf.runInference(frame);
//
//        if (frameCounter % 20 == 0) {
//            if (processDamage(detections)) {
//                cout << "Damage detected! Updating database..." << endl;
//            }
//            if (processQR(detections)) {
//                cout << "QR code detected! Updating database..." << endl;
//            }
//        }
//
//        drawDetections(frame, detections);
//        imshow("Inference", frame);
//
//        frameCounter++;
//        if (waitKey(1) == 'q') break;
//    }
//
//    cap.release();
//    destroyAllWindows();
//    return 0;
//}
