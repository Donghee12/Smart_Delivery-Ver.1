#include "Qrcodegen.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "database.h"
#include "scanQRCode.h"
#include "detection.h"
//#include "ar_SerialClass.h"
#include <string.h>

using qrcodegen::QrCode;
using namespace cv;
using namespace std;

//extern void ar_serial_Communication(char* ar_input_data, int direction);
//extern string ar_g_converyor_stop;

extern OrderDetails orderData;

//ar_Serial* ar_sp = new ar_Serial("COM6");

int main()
{
    system("color f0");
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    char ar_input_data;

    int a = 1;
    int flag = 0;  // QR 코드 인식 상태 (0: 인식 안 됨, >0: 인식 성공)
    int frameCounter = 0;
    bool detect_damage = false;
    bool detect_QR = false;

    Inference inf("best.onnx", Size(640, 640), "model.txt", false);
    loadClassNames("model.txt");

    Mat img_frame;
    VideoCapture cap(0);
    cap.set(CAP_PROP_EXPOSURE, -6);
    cap.set(CAP_PROP_FOCUS, 255);
    Connection* conn = db_connect_to(db_config);
    conn->setSchema("test_db");

    flag = 0;  // 매번 프레임 시작 시 flag 초기화
    while (1)
    {
        detect_damage = false;
        detect_QR = false;

        cap.read(img_frame);
        if (img_frame.empty())
            return -1;

        //vector<Detection> detections = inf.runInference(img_frame);
        //drawDetections(img_frame, detections);  // YOLO 객체 검출 표시

        //if (frameCounter % 1 == 0)
       // {
           // Sleep(500);
            //detect_damage = processDamage(detections);  // DAMAGE 여부 검출
            //detect_QR = processQR(detections);          // QR 여부 검출

            if (detect_damage)  // DAMAGE 검출 = TRUE
            {
                cout << "Damage detected!" << endl;
                ar_input_data = 'E';
                //ar_serial_Communication(&ar_input_data, 2);  // Arduino로 'E'를 보냄
               // frameCounter++;
                continue;  // 다시 while로 돌아감
            }

            //if (detect_QR)  // QR 검출 = TRUE
            //{
                //cout << "QR code detected!" << endl;

                // QR 코드 인식 처리
                //while (true)  // QR 코드 인식을 계속 시도
                //{
                    flag = scanQRCode(img_frame, conn);  // QR 코드 인식 시도

                    if (flag > 0)  // QR 코드 인식 성공 시
                    {
                        printOrderData(conn, flag);
                        ar_input_data = orderData.addr[0];
                        //ar_serial_Communication(&ar_input_data, 2);
                        cout << "QR 코드 인식 성공: 주문 번호 " << flag << endl;
                        flag = 0;
                        //break;  // QR 코드 인식 성공 후 루프 탈출
                    }

                    //cout << "QR 코드 인식 중..." << endl;

                    if (flag < 0)  // QR 코드 인식 실패 (유효하지 않음)
                    {
                        cout << "QR 코드 인식 실패 (오류)" << endl;
                        ar_input_data = 'E';
                        //ar_serial_Communication(&ar_input_data, 2);
                        break;  // 실패 후 탈출 (다시 시도하지 않음)
                    }

                    // QR 코드가 인식되지 않았을 경우 계속해서 시도
                    // flag가 0일 때 계속 QR 코드를 인식 시도하도록 해야함.
               //}
            //}
        //}


        //frameCounter++;
        imshow("VideoFeed", img_frame);
        if (waitKey(1) == 27)  // ESC 키를 눌러 종료
            break;
    }

    cap.release();
    //destroyAllWindows();

    return 0;
}

//void QR()
//{
//    Mat frame;
//
//    VideoCapture cap(0);
//    if (!cap.isOpened())
//    {
//        cout << "카메라 연결 오류" << endl;
//        return -1;  // 카메라 연결 실패 시 종료
//    }
//
//    QRCodeDetector detector;  // QR 코드 탐지기 객체 생성
//
//    String lastQRCode = "";  // 마지막으로 인식된 QR 코드 정보 저장
//    bool qrDetected = false;  // QR 코드가 한번이라도 인식된 상태를 추적
//
//    while (1)  // 무한루프 카메라에서 계속해서 프레임을 읽음
//    {
//        bool ret = cap.read(frame);  // 읽은 프레임을 frame에 저장
//
//        if (!ret)
//        {
//            cout << "캡쳐 실패" << endl;
//            break;
//        }
//
//        // QR 코드 탐지 및 디코딩
//        vector<Point> points;  // qr코드의 외곽점 저장하는 벡터
//        String info = detector.detectAndDecode(frame, points);  // qr코드 탐지 및 디코딩
//
//        // QR 코드가 발견되었고, 마지막 QR 코드와 다를 경우
//        if (!info.empty() && info != lastQRCode)
//        {
//            polylines(frame, points, true, Scalar(0, 0, 255), 2);  // qr코드의 외곽선 출력
//            putText(frame, info, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));  // 정보 출력
//            cout << "QR 코드 검출 성공: " << info << endl;
//
//            lastQRCode = info;  // 마지막으로 인식된 QR 코드 정보를 업데이트
//        }
//
//        imshow("frame", frame);  // 결과 출력
//
//        if (waitKey(1) == 27)  // ESC 키를 눌러 종료
//            break;
//    }
//
//    cap.release();
//    return 0;  // 정상 종료
//}