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
    int flag = 0;  // QR �ڵ� �ν� ���� (0: �ν� �� ��, >0: �ν� ����)
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

    flag = 0;  // �Ź� ������ ���� �� flag �ʱ�ȭ
    while (1)
    {
        detect_damage = false;
        detect_QR = false;

        cap.read(img_frame);
        if (img_frame.empty())
            return -1;

        //vector<Detection> detections = inf.runInference(img_frame);
        //drawDetections(img_frame, detections);  // YOLO ��ü ���� ǥ��

        //if (frameCounter % 1 == 0)
       // {
           // Sleep(500);
            //detect_damage = processDamage(detections);  // DAMAGE ���� ����
            //detect_QR = processQR(detections);          // QR ���� ����

            if (detect_damage)  // DAMAGE ���� = TRUE
            {
                cout << "Damage detected!" << endl;
                ar_input_data = 'E';
                //ar_serial_Communication(&ar_input_data, 2);  // Arduino�� 'E'�� ����
               // frameCounter++;
                continue;  // �ٽ� while�� ���ư�
            }

            //if (detect_QR)  // QR ���� = TRUE
            //{
                //cout << "QR code detected!" << endl;

                // QR �ڵ� �ν� ó��
                //while (true)  // QR �ڵ� �ν��� ��� �õ�
                //{
                    flag = scanQRCode(img_frame, conn);  // QR �ڵ� �ν� �õ�

                    if (flag > 0)  // QR �ڵ� �ν� ���� ��
                    {
                        printOrderData(conn, flag);
                        ar_input_data = orderData.addr[0];
                        //ar_serial_Communication(&ar_input_data, 2);
                        cout << "QR �ڵ� �ν� ����: �ֹ� ��ȣ " << flag << endl;
                        flag = 0;
                        //break;  // QR �ڵ� �ν� ���� �� ���� Ż��
                    }

                    //cout << "QR �ڵ� �ν� ��..." << endl;

                    if (flag < 0)  // QR �ڵ� �ν� ���� (��ȿ���� ����)
                    {
                        cout << "QR �ڵ� �ν� ���� (����)" << endl;
                        ar_input_data = 'E';
                        //ar_serial_Communication(&ar_input_data, 2);
                        break;  // ���� �� Ż�� (�ٽ� �õ����� ����)
                    }

                    // QR �ڵ尡 �νĵ��� �ʾ��� ��� ����ؼ� �õ�
                    // flag�� 0�� �� ��� QR �ڵ带 �ν� �õ��ϵ��� �ؾ���.
               //}
            //}
        //}


        //frameCounter++;
        imshow("VideoFeed", img_frame);
        if (waitKey(1) == 27)  // ESC Ű�� ���� ����
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
//        cout << "ī�޶� ���� ����" << endl;
//        return -1;  // ī�޶� ���� ���� �� ����
//    }
//
//    QRCodeDetector detector;  // QR �ڵ� Ž���� ��ü ����
//
//    String lastQRCode = "";  // ���������� �νĵ� QR �ڵ� ���� ����
//    bool qrDetected = false;  // QR �ڵ尡 �ѹ��̶� �νĵ� ���¸� ����
//
//    while (1)  // ���ѷ��� ī�޶󿡼� ����ؼ� �������� ����
//    {
//        bool ret = cap.read(frame);  // ���� �������� frame�� ����
//
//        if (!ret)
//        {
//            cout << "ĸ�� ����" << endl;
//            break;
//        }
//
//        // QR �ڵ� Ž�� �� ���ڵ�
//        vector<Point> points;  // qr�ڵ��� �ܰ��� �����ϴ� ����
//        String info = detector.detectAndDecode(frame, points);  // qr�ڵ� Ž�� �� ���ڵ�
//
//        // QR �ڵ尡 �߰ߵǾ���, ������ QR �ڵ�� �ٸ� ���
//        if (!info.empty() && info != lastQRCode)
//        {
//            polylines(frame, points, true, Scalar(0, 0, 255), 2);  // qr�ڵ��� �ܰ��� ���
//            putText(frame, info, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));  // ���� ���
//            cout << "QR �ڵ� ���� ����: " << info << endl;
//
//            lastQRCode = info;  // ���������� �νĵ� QR �ڵ� ������ ������Ʈ
//        }
//
//        imshow("frame", frame);  // ��� ���
//
//        if (waitKey(1) == 27)  // ESC Ű�� ���� ����
//            break;
//    }
//
//    cap.release();
//    return 0;  // ���� ����
//}