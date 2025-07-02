#include "pch.h"
#include "database.h"
#include <iostream>
using namespace std;

// 제품 이름에 따라 가격을 설정하는 함수
int getProductPrice(const string& product_name, const string& manufacturer) {
    if (product_name == "TV") {
        if (manufacturer == "Samsung") {
            return 500;  // 삼성 TV 가격
        }
        else if (manufacturer == "Apple") {
            return 600;  // 애플 TV 가격
        }
    }
    else if (product_name == "Phone") {
        if (manufacturer == "Samsung") {
            return 700;  // 삼성 Phone 가격
        }
        else if (manufacturer == "Apple") {
            return 800;  // 애플 Phone 가격
        }
    }
    else if (product_name == "Laptop") {
        if (manufacturer == "Samsung") {
            return 1000;  // 삼성 Laptop 가격
        }
        else if (manufacturer == "Apple") {
            return 1200;  // 애플 Laptop 가격
        }
    }
    return 0;  // 가격이 설정되지 않은 경우
}

// 고객 정보 입력 함수
void inputCustomerInfo(string& customer_name, string& address, string& phone) {
    cout << u8"고객의 이름을 입력하세요: ";
    cin >> customer_name;
    cout << u8"고객의 주소를 입력하세요: ";
    cin >> address;
    cout << u8"고객의 전화번호를 입력하세요: ";
    cin >> phone;
}

// 제품 선택 함수
string selectProduct(int choice) {
    //int choice;
    string product_name;

    //cout << u8"제품을 선택하세요 (1: TV, 2: Phone, 3: Laptop): ";
    //cin >> choice;

    switch (choice) {
    case 1:
        product_name = "TV";
        break;
    case 2:
        product_name = "Phone";
        break;
    case 3:
        product_name = "Laptop";
        break;
    default:
        cout << "잘못된 선택입니다." << endl;
        return "";
    }
    return product_name;
}

// 제조사 선택 함수
string selectManufacturer(int manufacturer_choice) {

    string manufacturer;

    //cout << u8"제조사를 선택하세요 (1: Samsung, 2: Apple): ";
    //cin >> manufacturer_choice;

    switch (manufacturer_choice) {
    case 1:
        manufacturer = "Samsung";
        break;
    case 2:
        manufacturer = "Apple";
        break;
    default:
        cout << "잘못된 선택입니다." << endl;
        return "";
    }
    return manufacturer;
}
