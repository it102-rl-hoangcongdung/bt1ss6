# BÁO CÁO BÀI TẬP LẬP TRÌNH C: QUẢN LÝ SỐ NGÀY QUÁ HẠN MƯỢN SÁCH THƯ VIỆN

> 👤 **Học viên:** Hoàng Công Dũng | **Mã SV:** PTIT-HCM-009
> 🏫 **Môn học:** it102-rl-hoangcongdung

---

## 📊 Sơ đồ thiết kế hệ thống (Activity Diagram)

> 💡 *Sơ đồ dưới đây được render tự động trực tiếp trên GitHub bằng Mermaid. Bạn cũng có thể tải file **`bt1.drawio`** trong repository này để mở và chỉnh sửa trực tiếp trên [Draw.io (diagrams.net)](https://app.diagrams.net).* 

```mermaid
graph TD
  Start([Bắt đầu chương trình]) --> Init[Khởi tạo mảng maPhieu, ngayQuaHan và soLuong = 3]
  Init --> Menu[Hiển thị Menu chính:
1. Xem danh sách
2. Thêm mới
3. Cập nhật
0. Thoát]
  Menu --> InputChoice[Nhận lựa chọn từ người dùng]
  InputChoice --> CleanBuffer1[Làm sạch bộ đệm với while getchar != newline]
  CleanBuffer1 --> CheckChoice{Phân nhánh lựa chọn}
  
  CheckChoice -- Lựa chọn 1 --> Case1[Xem danh sách phiếu mượn]
  Case1 --> LoopList[Vòng lặp in danh sách & tính tienPhat = ngayQuaHan * 5000]
  LoopList --> Menu
  
  CheckChoice -- Lựa chọn 2 --> Case2[Thêm mới phiếu mượn]
  Case2 --> CheckFull{soLuong >= 50?}
  CheckFull -- Đúng --> ErrFull[Báo lỗi: Danh sách đầy]
  ErrFull --> Menu
  CheckFull -- Sai --> InputCode[Nhập mã phiếu mượn mới]
  InputCode --> SaveNew[Lưu vào maPhieu[soLuong], ngayQuaHan = 0, soLuong++]
  SaveNew --> Menu
  
  CheckChoice -- Lựa chọn 3 --> Case3[Cập nhật số ngày quá hạn]
  Case3 --> InputSearch[Nhập mã phiếu cần tìm]
  InputSearch --> SearchLoop[Duyệt mảng tìm vị trí bằng strcmp]
  SearchLoop --> FoundCheck{Tìm thấy không?}
  FoundCheck -- Không tìm thấy --> ErrNotFound[Báo lỗi không tìm thấy mã phiếu]
  ErrNotFound --> Menu
  FoundCheck -- Tìm thấy --> InputDays[Nhập số ngày quá hạn mới]
  InputDays --> CleanBuffer2[Làm sạch bộ đệm getchar]
  CleanBuffer2 --> ValidateDays{ngayQuaHan >= 0?}
  ValidateDays -- Số âm --> ErrDays[Báo lỗi: Số ngày không âm]
  ErrDays --> InputDays
  ValidateDays -- Hợp lệ --> UpdateData[Ghi đè vào mảng ngayQuaHan tại vị trí index]
  UpdateData --> Menu
  
  CheckChoice -- Lựa chọn 0 --> End([Thoát chương trình và in lời chào])
```

---

## 1. Mục tiêu và Bối cảnh bài toán

Bài thực hành này giúp củng cố kiến thức về mảng một chiều lưu trữ số nguyên, mảng hai chiều ký tự quản lý danh sách chuỗi song song, và kỹ thuật xây dựng vòng lặp điều khiển menu trong ngôn ngữ C.

Ứng dụng LIBRARY_WMS được thiết kế chạy trực tiếp trên Terminal, hỗ trợ thủ thư thao tác quản lý dữ liệu hiệu quả mà không cần sử dụng cấu trúc struct hay hàm phức tạp.

- Sử dụng mảng song song char maPhieu[50][20] và int ngayQuaHan[50] với biến đếm soLuong.
- Áp dụng triệt để hàm strcmp() để tìm kiếm vị trí phần tử trong mảng chuỗi.
- Xử lý chống trôi lệnh nhập liệu bàn phím bằng getchar() sau khi dùng scanf đọc số nguyên.

## 2. Phân tích giải pháp kỹ thuật và Bẫy dữ liệu

Trong quá trình viết mã, vấn đề lớn nhất thường gặp là hiện tượng trôi lệnh khi người dùng nhập số nguyên rồi chuyển sang nhập chuỗi ký tự. Bộ đệm bàn phím vẫn còn lưu ký tự xuống dòng '
', khiến hàm nhập chuỗi bị bỏ qua.

Để giải quyết triệt để lỗi này, tôi đã bổ sung tường minh vòng lặp while (getchar() != '
'); ngay sau mỗi lệnh scanf đọc số nguyên.

- Quy tắc tính tiền phạt: tienPhat = ngayQuaHan * 5000 (đơn vị VNĐ).
- Kiểm tra tràn mảng: Chặn thêm mới khi soLuong đạt giới hạn 50 phiếu.
- Kiểm tra dữ liệu âm: Bắt buộc số ngày quá hạn nhập vào phải lớn hơn hoặc bằng 0.

## 3. Bảng đặc tả chi tiết luồng nghiệp vụ chương trình

Dưới đây là bảng phân tích chi tiết các chức năng CRUD được hiện thực hóa bên trong hàm main():

| Chức năng | Thao tác người dùng | Xử lý kỹ thuật trong mã nguồn | Kết quả đầu ra |
| --- | --- | --- | --- |
| Xem danh sách | Chọn phím 1 | Dùng vòng lặp for từ 0 đến soLuong - 1, in thông tin và tính tiền phạt | Hiển thị bảng danh sách trực quan |
| Thêm mới | Chọn phím 2 | Kiểm tra soLuong < 50, nhận chuỗi mã phiếu, gán hạn = 0, tăng soLuong | Thêm thành công phiếu mượn mới |
| Cập nhật | Chọn phím 3 | Nhập mã phiếu, dùng strcmp tìm index, nhập số ngày mới >= 0 và ghi đè | Cập nhật dữ liệu quá hạn thành công |
| Thoát | Chọn phím 0 | Thoát khỏi vòng lặp do-while điều khiển menu | Kết thúc chương trình |

## 4. Hướng dẫn biên dịch và kiểm thử mã nguồn

Mã nguồn được lưu hoàn chỉnh trong file main.c, tuân thủ chuẩn C11.

Sinh viên có thể sử dụng terminal trên Visual Studio Code để biên dịch và chạy thử nghiệm theo các lệnh chuẩn sau:

- Lệnh biên dịch: gcc -std=c11 main.c -o main
- Lệnh chạy trên Linux/macOS: ./main
- Lệnh chạy trên Windows: main.exe

---

## 📁 Danh sách tệp tin nộp bài trong Repository
- 📝 `bt1.docx`: Báo cáo tài liệu phân tích nghiệp vụ hoàn chỉnh.
- 🎨 `bt1.drawio`: File thiết kế sơ đồ chuẩn theo quy định đề bài (mở trực tiếp bằng [Draw.io](https://app.diagrams.net) hoặc Lucidchart).
- 💻 `main.c`: Mã nguồn chương trình.
