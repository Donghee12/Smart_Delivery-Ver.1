#pragma once
#include "Qrcodegen.hpp"
#include <opencv2/opencv.hpp>
#include <mysql/jdbc.h>
#include <iostream>
using qrcodegen::QrCode;
using namespace cv;
using namespace std;
using namespace sql;


Mat qr_makeQrCodeMat(const QrCode& qr, int iBorder/* = 0*/);	// qr코드 생성

//qr 코드 데이터 입력
Mat qr_inputData(string customer_name, string address, string phone, string product_name, int customer_id);
Mat qr_inputData(string order_num);

void t_qrgen(Connection* conn);		// Seoul출력, 저장 테스트