# Quản lý Đặt phòng Khách sạn (Hotel Booking Management)

Đồ án cuối khóa môn lập trình C — ứng dụng console quản lý đặt phòng khách sạn:
thêm/sửa/xóa phòng, đặt phòng, trả phòng + in hóa đơn, thống kê doanh thu và tỷ lệ lấp đầy.

## 1. Thành viên & phân công

| # | Họ tên | MSSV | Phụ trách |
|---|--------|------|-----------|
| 1 | Phúc Xo (trưởng nhóm) | 26689351 | Khung chương trình: struct, hàm nhập liệu, hàm tiện ích, menu chính, README |
| 2 | Thái Toàn | 26657561 | `addRoom`, `displayRooms`, `updateRoom`, `deleteRoom`, `saveToFile`, `loadFromFile` |
| 3 | Hồ Vĩnh Trung | 26640841 | `searchRooms`, `bookRoom`, `checkoutRoom`, `showStatistics`, `sortByPrice` |

> ⚠️ Quy tắc Git: làm việc trên nhánh `feat/<ten-chuc-nang>`, KHÔNG commit
> trực tiếp lên `main`. Xong việc tạo Pull Request để trưởng nhóm review rồi merge.
> Mỗi thành viên commit bằng tài khoản GitHub cá nhân — điểm cá nhân căn cứ
> vào lịch sử commit.

## 2. Cấu trúc dữ liệu

```c
typedef struct {
    int   roomId;            // 101, 102...
    char  roomType[20];      // "Don", "Doi", "VIP", "TongThong"
    long  pricePerDay;       // VND/ngày (số nguyên, không dùng float)
    int   maxGuests;         // số khách tối đa
    int   status;            // ROOM_EMPTY = trống, ROOM_BOOKED = đã đặt
    char  guestName[51];     // tên khách đang thuê
    char  checkInDate[9];    // ngày vào, dạng "DDMMYYYY" (vd "10102026")
    char  checkOutDate[9];   // ngày ra, dạng "DDMMYYYY" (trống khi chưa trả)
} Room;
```

Lưu trữ bằng mảng 1 chiều tĩnh `Room rooms[10000]`, đúng yêu cầu đề bài
(int ✓, long ✓, chuỗi ✓, trên 4 thuộc tính ✓).

Ngày tháng lưu dạng chuỗi `"DDMMYYYY"` (8 chữ số liền nhau) và kiểm tra bằng
`isValidDate` (đủ 8 số, đúng lịch kể cả năm nhuận). Số ngày thuê không lưu riêng
mà tính lúc trả phòng: `dateToDays(ngày ra) - dateToDays(ngày vào)`
(tối thiểu 1 ngày).

## 3. Chức năng

| Menu | Chức năng |
|------|-----------|
| 1 | Thêm phòng mới (`addRoom`) |
| 2 | Hiển thị danh sách dạng bảng (`displayRooms`) |
| 3 | Tìm kiếm theo mã / loại / phòng trống (`searchRooms`) |
| 4 | Đặt phòng (`bookRoom`) |
| 5 | Trả phòng + in hóa đơn (`checkoutRoom`) |
| 6 | Cập nhật thông tin phòng (`updateRoom`) |
| 7 | Xóa phòng — chặn xóa phòng đang có khách (`deleteRoom`) |
| 8 | Thống kê doanh thu & tỷ lệ lấp đầy (`showStatistics`) |
| 9 | Sắp xếp phòng theo giá (`sortByPrice`) |
| 10 | Lưu dữ liệu ra file `.txt` (`saveToFile`) |
| 11 | Đọc dữ liệu từ file `.txt` (`loadFromFile`) |
| 0 | Thoát |

Đọc số bằng `scanf`; dọn ký tự Enter thừa sau mỗi lần đọc (`getchar()`)
và dọn cả dòng khi nhập sai (`scanf("%*[^\n]")`) để tránh trôi lệnh và treo máy.
Tên hàm/biến tiếng Anh camelCase, mỗi chức năng là một hàm riêng.
Hàm tiện ích ngày tháng dùng chung: `isLeapYear`, `daysInMonth`,
`isValidDate`, `dateToDays`.

## 4. Biên dịch & chạy

Yêu cầu: trình biên dịch C (gcc). Biên dịch sạch, không warning với `-Wall -Wextra`.

```bash
# Linux / macOS
gcc -Wall -Wextra -o hotel main.c
./hotel

# Windows (MinGW)
gcc -Wall -Wextra -o hotel.exe main.c
hotel.exe
```

## 5. Định dạng file dữ liệu

File `.txt` do chương trình tự lưu/đọc (chức năng 10/11), mỗi dòng một phòng,
8 trường cách nhau bằng `|`:

```
<roomId>|<roomType>|<pricePerDay>|<maxGuests>|<status>|<guestName>|<checkInDate>|<checkOutDate>
...
```

Phòng trống ghi `guestName`, `checkInDate`, `checkOutDate` là `<NULL>`.
File chỉ lưu thông tin phòng + ngày đặt để tra cứu phòng trống theo ngày;
số ngày ở và doanh thu tính trong lúc chạy, không lưu vào file.

## 6. Demo

_(chụp ảnh màn hình menu + hóa đơn khi chạy, dán vào đây trước khi nộp)_
