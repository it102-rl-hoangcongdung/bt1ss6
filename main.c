#include <stdio.h>
#include <string.h>

int main() {
    const int MAX_PHIEU = 50;
    char maPhieu[50][20] = {"PM101", "PM102", "PM103"};
    int ngayQuaHan[50] = {0, 3, 5};
    int soLuong = 3;
    int choice;

    do {
        printf("\n--- HE THONG QUAN LY MUON TRA SACH (LIBRARY_WMS) ---\n");
        printf("1. Xem danh sach phieu muon\n");
        printf("2. Them moi phieu muon\n");
        printf("3. Cap nhat so ngay qua han\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Loi: Vui long nhap so nguyen hop le!\n");
            while (getchar() != '\n');
            continue;
        }
        
        while (getchar() != '\n');

        switch (choice) {
            case 1: {
                printf("\n--- DANH SACH PHIEU MUON SACH ---\n");
                printf("%-5s | %-10s | %-15s | %-15s\n", "STT", "Ma Phieu", "So Ngay Qua Han", "Tien Phat (VND)");
                printf("---------------------------------------------------\n");
                for (int i = 0; i < soLuong; i++) {
                    long long tienPhat = (long long)ngayQuaHan[i] * 5000;
                    printf("%-5d | %-10s | %-12d ngay | %lld VND\n", i + 1, maPhieu[i], ngayQuaHan[i], tienPhat);
                }
                printf("---------------------------------------------------\n");
                printf("Tong so phieu: %d\n", soLuong);
                break;
            }
            case 2: {
                if (soLuong >= MAX_PHIEU) {
                    printf("Loi: Danh sach phieu muon da day, khong the them!\n");
                    break;
                }
                printf("Nhap ma phiếu muon mới: ");
                scanf("%s", maPhieu[soLuong]);
                while (getchar() != '\n');
                ngayQuaHan[soLuong] = 0;
                soLuong++;
                printf("Them moi thanh công phieu muon!\n");
                break;
            }
            case 3: {
                char searchCode[20];
                printf("Nhap ma phieu muon can cap nhat: ");
                scanf("%s", searchCode);
                while (getchar() != '\n');

                int foundIndex = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], searchCode) == 0) {
                        foundIndex = i;
                        break;
                    }
                }

                if (foundIndex == -1) {
                    printf("Khong tìm thấy phieu muon '%s' trong danh sách!\n", searchCode);
                } else {
                    printf("Tìm thay phieu muon '%s' tai vi tri index %d.\n", searchCode, foundIndex);
                    int newDays;
                    while (1) {
                        printf("Nhập so ngay qua han mới: ");
                        if (scanf("%d", &newDays) != 1) {
                            printf("Loi: Vui long nhap số nguyên!\n");
                            while (getchar() != '\n');
                            continue;
                        }
                        while (getchar() != '\n');

                        if (newDays < 0) {
                            printf("Loi: So ngay qua han phai >= 0. Vui long nhap lai!\n");
                        } else {
                            ngayQuaHan[foundIndex] = newDays;
                            printf("Cap nhat thanh cong! So ngay qua han moi cua %s la %d ngay.\n", searchCode, newDays);
                            break;
                        }
                    }
                }
                break;
            }
            case 0:
                printf("Thoát chuong trình LIBRARY_WMS. Tam biet!\n");
                break;
            default:
                printf("Chuc nang không hop lệ! Vui lòng chọn tu 0 đến 3.\n");
        }
    } while (choice != 0);

    return 0;
}