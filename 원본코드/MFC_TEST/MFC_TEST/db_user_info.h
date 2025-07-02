#pragma once
#ifndef DB_USER_INFO_H
#define DB_USER_INFO_H

#include <string>
using namespace std;

// 제품 이름에 따라 가격을 설정하는 함수
int getProductPrice(const string& product_name, const string& manufacturer);

// 고객 정보 입력 함수
void inputCustomerInfo(string& customer_name, string& address, string& phone);

// 제품 선택 함수
string selectProduct(int choice);

// 제조사 선택 함수
string selectManufacturer(int manufacturer_choice);

#endif // DB_USER_INFO_H
