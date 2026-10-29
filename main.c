#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10000
#define ROOM_EMPTY 0
#define ROOM_BOOKED 1
// Phan cong nhom:
// - TV2 Thai Toan: CRUD (them, hien thi, cap nhat, xoa) va luu/doc file
// - TV3 Ho Vinh Trung: dat phong, tra phong
// - Nhom truong Phuc Xo: menu, loc/tim kiem, thong ke, sap xep, ham ngay thang, nhap lieu
typedef struct
{
    int roomId;
    char roomType[20];
    long pricePerDay;
    int maxGuests;
    int status;
    char guestName[51];
    char checkInDate[9];
    char checkOutDate[9];
} Room;
Room rooms[MAX];
int roomCount = 0;
long totalRevenue = 0;
void clearInput(void)
{
    scanf("%*[^\n]");
    getchar();
}
/* Tam dung cho nguoi dung doc xong: chi dung ngay sau mot lan nhap bang scanf,
   vi luc do bo dem con sot dung 1 phim Enter. clearInput an Enter thua do,
   getchar sau do moi that su doi Enter moi. */
void Enter(void)
{
    printf("Nhan Enter de tiep tuc...");
    clearInput();
    getchar();
}
int findRooms(int roomId)
{
    int i;
    for (i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == roomId)
            return i;
    }
    return -1;
}
int roomExists(int id)
{
    int i;
    for (i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == id)
            return 1;
    }
    return 0;
}
int ganLoaiPhong(Room *r, int chon)
{
    switch (chon)
    {
    case 1:
        strcpy(r->roomType, "Don");
        r->pricePerDay = 350000;
        r->maxGuests = 1;
        return 1;
    case 2:
        strcpy(r->roomType, "Doi");
        r->pricePerDay = 550000;
        r->maxGuests = 2;
        return 1;
    case 3:
        strcpy(r->roomType, "VIP");
        r->pricePerDay = 1500000;
        r->maxGuests = 5;
        return 1;
    case 4:
        strcpy(r->roomType, "TongThong");
        r->pricePerDay = 3500000;
        r->maxGuests = 10;
        return 1;
    default:
        return 0;
    }
}
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int daysInMonth(int month, int year)
{
    int d[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1 || month > 12)
        return 0;
    if (month == 2 && isLeapYear(year))
        return 29;
    return d[month - 1];
}
int isValidDate(char *date)
{
    int d, m, y;
    if (strlen(date) != 8)
        return 0;
    if (sscanf(date, "%2d%2d%4d", &d, &m, &y) != 3)
        return 0;
    if (y < 1900 || m < 1 || m > 12)
        return 0;
    return d >= 1 && d <= daysInMonth(m, y);
}
long dateToDays(char *date)
{
    int d, m, y, i;
    long total = 0;
    sscanf(date, "%2d%2d%4d", &d, &m, &y);
    for (i = 1900; i < y; i++)
        total += isLeapYear(i) ? 366 : 365;
    for (i = 1; i < m; i++)
        total += daysInMonth(i, y);
    return total + d;
}
int phongCoTrangThai(int idx, int trangThai)
{
    return rooms[idx].status == trangThai;
}
int ngayRaHopLe(char *ngayVao, char *ngayRa)
{
    return isValidDate(ngayRa) && dateToDays(ngayRa) >= dateToDays(ngayVao);
}
int soKhachHopLe(int soKhach, int maxGuests)
{
    return soKhach >= 1 && soKhach <= maxGuests;
}
int giaHopLe(long gia)
{
    return gia > 0;
}
const char *chuoiHoacNull(char *s)
{
    return s[0] ? s : "<NULL>";
}
void nullThanhRong(char *s)
{
    if (strcmp(s, "<NULL>") == 0)
        s[0] = '\0';
}
int dongHopLe(Room *r)
{
    return (strcmp(r->roomType, "Don") == 0 ||
            strcmp(r->roomType, "Doi") == 0 ||
            strcmp(r->roomType, "VIP") == 0 ||
            strcmp(r->roomType, "TongThong") == 0) &&
           giaHopLe(r->pricePerDay) &&
           r->maxGuests >= 1 && r->maxGuests <= 10 &&
           (r->status == ROOM_EMPTY || r->status == ROOM_BOOKED);
}
int dongDatHopLe(char *gName, char *cIn, char *cOut)
{
    return strcmp(gName, "<NULL>") != 0 && isValidDate(cIn) && ngayRaHopLe(cIn, cOut);
}
void displayMenu(void)
{
    printf("--- QUAN LY DAT PHONG KHACH SAN ---\n");
    printf("1. Them phong moi\n");
    printf("2. Hien thi tat ca phong\n");
    printf("3. Tim kiem / Hien thi phong\n");
    printf("4. Dat phong\n");
    printf("5. Tra phong + tinh tien\n");
    printf("6. Cap nhat phong theo thuoc tinh\n");
    printf("7. Xoa phong\n");
    printf("8. Thong ke doanh thu\n");
    printf("9. Sap xep phong theo gia\n");
    printf("10. Luu danh sach ra file\n");
    printf("11. Doc danh sach tu file\n");
    printf("0. Thoat\n");
    printf("Nhap lua chon: ");
}
void inPhong(int idx, int chiTiet)
{
    int booked;
    const char *trangThai, *tenKhach, *ngayVao, *ngayRa;
    if (chiTiet)
    {
        printf("------THONG TIN PHONG------\n");
        printf("Ma phong: %d\n", rooms[idx].roomId);
        printf("Loai phong: %s\n", rooms[idx].roomType);
        printf("Gia phong: %ld VND/ngay\n", rooms[idx].pricePerDay);
        printf("So khach toi da: %d\n", rooms[idx].maxGuests);
        printf("Trang thai: %s\n", phongCoTrangThai(idx, ROOM_BOOKED) ? "Da dat" : "Trong");
        if (phongCoTrangThai(idx, ROOM_BOOKED))
        {
            printf("Ten khach hang: %s\n", rooms[idx].guestName);
            printf("Ngay vao: %s\n", rooms[idx].checkInDate);
            printf("Ngay ra: %s\n", rooms[idx].checkOutDate);
        }
        return;
    }
    booked = phongCoTrangThai(idx, ROOM_BOOKED);
    trangThai = booked ? "Da dat" : "Trong";
    tenKhach = booked ? rooms[idx].guestName : "-";
    ngayVao = booked ? rooms[idx].checkInDate : "-";
    ngayRa = "-";
    if (booked)
        ngayRa = strlen(rooms[idx].checkOutDate) > 0 ? rooms[idx].checkOutDate : "Chua tra";
    printf("%-10d %-12s %-12ld %-10d %-12s %-20s %-12s %-12s\n",
           rooms[idx].roomId, rooms[idx].roomType, rooms[idx].pricePerDay,
           rooms[idx].maxGuests, trangThai, tenKhach, ngayVao, ngayRa);
}
// TV2 - Thai Toan
void displayRooms(void)
{
    int i;
    if (roomCount == 0)
    {
        printf("Danh sach phong dang trong!\n");
        return;
    }
    printf("\n=================================================================================================================\n");
    printf("%-10s %-12s %-12s %-10s %-12s %-20s %-12s %-12s\n",
           "Ma phong", "Loai", "Gia/ngay", "Max Khach", "Trang thai", "Ten khach hang", "Ngay vao", "Ngay ra");
    printf("=================================================================================================================\n");
    for (i = 0; i < roomCount; i++)
        inPhong(i, 0);
    printf("=================================================================================================================\n\n");
}
// TV2 - Thai Toan
int displayRoomById(int id)
{
    int index;
    index = findRooms(id);
    if (index == -1)
        return 0;
    inPhong(index, 1);
    return 1;
}
int filterRooms(int thuocTinh, char *giaTriChu, long giaTriSo)
{
    int i, dem, khop, inTieuDe;
    dem = 0;
    inTieuDe = 0;
    for (i = 0; i < roomCount; i++)
    {
        khop = 0;
        if (thuocTinh == 1)
            khop = (strcmp(rooms[i].roomType, giaTriChu) == 0);
        else if (thuocTinh == 2)
            khop = (rooms[i].status == giaTriSo);
        else if (thuocTinh == 3)
            khop = (rooms[i].maxGuests == giaTriSo);
        else if (thuocTinh == 4)
            khop = (rooms[i].pricePerDay == giaTriSo);
        else if (thuocTinh == 5)
            khop = (phongCoTrangThai(i, ROOM_EMPTY) && rooms[i].maxGuests >= giaTriSo);
        if (khop)
        {
            if (!inTieuDe)
            {
                printf("\n%-10s %-12s %-12s %-10s %-12s %-20s %-12s %-12s\n",
                       "Ma phong", "Loai", "Gia/ngay", "Max Khach", "Trang thai", "Ten khach hang", "Ngay vao", "Ngay ra");
                inTieuDe = 1;
            }
            inPhong(i, 0);
            dem++;
        }
    }
    return dem;
}
int searchRoomsByName(char *ten)
{
    int i, dem, inTieuDe;
    dem = 0;
    inTieuDe = 0;
    for (i = 0; i < roomCount; i++)
    {
        if (phongCoTrangThai(i, ROOM_BOOKED) && strcmp(rooms[i].guestName, ten) == 0)
        {
            if (!inTieuDe)
            {
                printf("\n%-10s %-12s %-12s %-10s %-12s %-20s %-12s %-12s\n",
                       "Ma phong", "Loai", "Gia/ngay", "Max Khach", "Trang thai", "Ten khach hang", "Ngay vao", "Ngay ra");
                inTieuDe = 1;
            }
            inPhong(i, 0);
            dem++;
        }
    }
    return dem;
}
// TV2 - Thai Toan
int addRoom(int id, int loaiChon)
{
    Room r;
    if (roomCount >= MAX)
        return 3;
    if (roomExists(id))
        return 1;
    r.roomId = id;
    r.status = ROOM_EMPTY;
    strcpy(r.roomType, "");
    strcpy(r.guestName, "");
    strcpy(r.checkInDate, "");
    strcpy(r.checkOutDate, "");
    if (!ganLoaiPhong(&r, loaiChon))
        return 2;
    rooms[roomCount] = r;
    roomCount++;
    return 0;
}
// TV3 - Ho Vinh Trung
int bookRoom(int id, char *ten, int soKhach, char *ngayVao, char *ngayRa)
{
    int index;
    index = findRooms(id);
    if (index == -1)
        return 1;
    if (phongCoTrangThai(index, ROOM_BOOKED))
        return 2;
    if (!soKhachHopLe(soKhach, rooms[index].maxGuests))
        return 3;
    if (!isValidDate(ngayVao) || !isValidDate(ngayRa))
        return 4;
    if (!ngayRaHopLe(ngayVao, ngayRa))
        return 5;
    rooms[index].status = ROOM_BOOKED;
    strcpy(rooms[index].guestName, ten);
    strcpy(rooms[index].checkInDate, ngayVao);
    strcpy(rooms[index].checkOutDate, ngayRa);
    return 0;
}
// TV3 - Ho Vinh Trung
int checkoutRoom(int id, char *ngayRa, int *soNgay, long *tien)
{
    int index;
    long days, bill;
    index = findRooms(id);
    if (index == -1)
        return 1;
    if (phongCoTrangThai(index, ROOM_EMPTY))
        return 2;
    if (!isValidDate(ngayRa))
        return 3;
    if (!ngayRaHopLe(rooms[index].checkInDate, ngayRa))
        return 4;
    days = dateToDays(ngayRa) - dateToDays(rooms[index].checkInDate);
    if (days < 1)
        days = 1;
    bill = days * rooms[index].pricePerDay;
    totalRevenue += bill;
    *soNgay = (int)days;
    *tien = bill;
    rooms[index].status = ROOM_EMPTY;
    strcpy(rooms[index].guestName, "");
    strcpy(rooms[index].checkInDate, "");
    strcpy(rooms[index].checkOutDate, "");
    return 0;
}
// TV2 - Thai Toan
int capNhatPhong(int id, int thuocTinh, int giaTriSo, long giaTriDai, char *giaTriChu)
{
    int index;
    if (!roomExists(id))
        return 1;
    index = findRooms(id);
    switch (thuocTinh)
    {
    case 1:
        if (phongCoTrangThai(index, ROOM_BOOKED))
            return 2;
        if (!ganLoaiPhong(&rooms[index], giaTriSo))
            return 4;
        return 0;
    case 2:
        if (phongCoTrangThai(index, ROOM_BOOKED))
            return 2;
        if (!giaHopLe(giaTriDai))
            return 4;
        rooms[index].pricePerDay = giaTriDai;
        return 0;
    case 3:
        if (phongCoTrangThai(index, ROOM_BOOKED))
            return 2;
        if (giaTriSo < 1 || giaTriSo > 10)
            return 4;
        rooms[index].maxGuests = giaTriSo;
        return 0;
    case 4:
        if (phongCoTrangThai(index, ROOM_EMPTY))
            return 3;
        if (giaTriChu == NULL || strlen(giaTriChu) == 0)
            return 4;
        strcpy(rooms[index].guestName, giaTriChu);
        return 0;
    case 5:
        if (phongCoTrangThai(index, ROOM_EMPTY))
            return 3;
        if (!isValidDate(giaTriChu))
            return 4;
        if (strlen(rooms[index].checkOutDate) > 0 && dateToDays(giaTriChu) > dateToDays(rooms[index].checkOutDate))
            return 4;
        strcpy(rooms[index].checkInDate, giaTriChu);
        return 0;
    case 6:
        if (phongCoTrangThai(index, ROOM_EMPTY))
            return 3;
        if (!isValidDate(giaTriChu))
            return 4;
        if (strlen(rooms[index].checkInDate) > 0 && dateToDays(giaTriChu) < dateToDays(rooms[index].checkInDate))
            return 4;
        strcpy(rooms[index].checkOutDate, giaTriChu);
        return 0;
    default:
        return 4;
    }
}
// TV2 - Thai Toan
int deleteRoom(int id)
{
    int index, i;
    if (!roomExists(id))
        return 1;
    index = findRooms(id);
    if (phongCoTrangThai(index, ROOM_BOOKED))
        return 2;
    for (i = index; i < roomCount - 1; i++)
        rooms[i] = rooms[i + 1];
    roomCount--;
    return 0;
}
void thongKe(int *tong, int *trong, int *daDat)
{
    int i;
    *tong = roomCount;
    *trong = 0;
    *daDat = 0;
    for (i = 0; i < roomCount; i++)
    {
        if (phongCoTrangThai(i, ROOM_EMPTY))
            (*trong)++;
        else if (phongCoTrangThai(i, ROOM_BOOKED))
            (*daDat)++;
    }
}
void sortByPrice(int tangDan)
{
    int i, j, swap;
    Room temp;
    for (i = 0; i < roomCount - 1; i++)
    {
        for (j = i + 1; j < roomCount; j++)
        {
            if (tangDan == 1)
                swap = (rooms[i].pricePerDay > rooms[j].pricePerDay);
            else
                swap = (rooms[i].pricePerDay < rooms[j].pricePerDay);
            if (swap)
            {
                temp = rooms[i];
                rooms[i] = rooms[j];
                rooms[j] = temp;
            }
        }
    }
}
// TV2 - Thai Toan
int saveToFile(const char *tenFile)
{
    int i;
    FILE *f;
    if (roomCount == 0)
        return 1;
    f = fopen(tenFile, "w");
    if (f == NULL)
        return 2;
    for (i = 0; i < roomCount; i++)
    {
        fprintf(f, "%d|%s|%ld|%d|%d",
                rooms[i].roomId, rooms[i].roomType, rooms[i].pricePerDay,
                rooms[i].maxGuests, rooms[i].status);
        fprintf(f, "|%s|%s|%s\n",
                chuoiHoacNull(rooms[i].guestName),
                chuoiHoacNull(rooms[i].checkInDate),
                chuoiHoacNull(rooms[i].checkOutDate));
    }
    fclose(f);
    return 0;
}
// TV2 - Thai Toan
int loadFromFile(const char *tenFile)
{
    char line[256];
    char gName[51];
    char cIn[11];
    char cOut[11];
    static Room temp[MAX];
    Room r;
    int count, i, n;
    FILE *f;
    f = fopen(tenFile, "r");
    if (f == NULL)
        return 1;
    count = 0;
    while (fgets(line, sizeof(line), f) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0)
            continue;
        r.roomId = 0;
        r.pricePerDay = 0;
        r.maxGuests = 0;
        r.status = 0;
        strcpy(r.roomType, "");
        strcpy(r.guestName, "");
        strcpy(r.checkInDate, "");
        strcpy(r.checkOutDate, "");
        gName[0] = '\0';
        cIn[0] = '\0';
        cOut[0] = '\0';
        n = sscanf(line, "%d|%19[^|]|%ld|%d|%d|%50[^|]|%10[^|]|%10s",
                   &r.roomId, r.roomType, &r.pricePerDay, &r.maxGuests,
                   &r.status, gName, cIn, cOut);
        if (n != 8 || count >= MAX)
        {
            fclose(f);
            return 2;
        }
        if (strcmp(r.roomType, "DON") == 0 || strcmp(r.roomType, "don") == 0)
            strcpy(r.roomType, "Don");
        else if (strcmp(r.roomType, "DOI") == 0 || strcmp(r.roomType, "doi") == 0)
            strcpy(r.roomType, "Doi");
        else if (strcmp(r.roomType, "vip") == 0 || strcmp(r.roomType, "Vip") == 0)
            strcpy(r.roomType, "VIP");
        else if (strcmp(r.roomType, "TONGTHONG") == 0 || strcmp(r.roomType, "tongthong") == 0)
            strcpy(r.roomType, "TongThong");
        if (!dongHopLe(&r))
        {
            fclose(f);
            return 2;
        }
        for (i = 0; i < count; i++)
        {
            if (temp[i].roomId == r.roomId)
            {
                fclose(f);
                return 2;
            }
        }
        if (r.status == ROOM_BOOKED && !dongDatHopLe(gName, cIn, cOut))
        {
            fclose(f);
            return 2;
        }
        if (r.status == ROOM_EMPTY)
        {
            strcpy(r.guestName, "");
            strcpy(r.checkInDate, "");
            strcpy(r.checkOutDate, "");
        }
        else
        {
            strcpy(r.guestName, gName);
            strcpy(r.checkInDate, cIn);
            strcpy(r.checkOutDate, cOut);
            nullThanhRong(r.guestName);
            nullThanhRong(r.checkInDate);
            nullThanhRong(r.checkOutDate);
        }
        temp[count] = r;
        count++;
    }
    fclose(f);
    for (i = 0; i < count; i++)
        rooms[i] = temp[i];
    roomCount = count;
    return 0;
}
long nhapSo(const char *prompt, long min, long max, const char *loi)
{
    long v;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%ld", &v) != 1)
        {
            clearInput();
            printf("%s", loi);
            continue;
        }
        if (v < min || v > max)
        {
            printf("%s", loi);
            continue;
        }
        return v;
    }
}
void nhapChuoi(const char *prompt, char *chuoi, int kieu)
{
    while (1)
    {
        printf("%s", prompt);
        gets(chuoi);
        if (kieu == 1)
        {
            if (isValidDate(chuoi))
                break;
            printf("Ngay khong hop le! Vui long nhap lai.\n");
        }
        else
        {
            if (strlen(chuoi) > 0)
                break;
            printf("Ten khach hang khong duoc de trong! Vui long nhap lai.\n");
        }
    }
}
int xacNhan(const char *prompt)
{
    char c;
    while (1)
    {
        printf("%s", prompt);
        if (scanf(" %c", &c) != 1)
        {
            clearInput();
            continue;
        }
        if (c == 'y' || c == 'Y')
            return 1;
        if (c == 'n' || c == 'N')
            return 0;
        clearInput();
    }
}
void lapTenFileTxt(const char *ten, char *full, int n)
{
    snprintf(full, n, "%s.txt", ten);
}
int main(void)
{
    int choice;
    do
    {
        displayMenu();
        if (scanf("%d", &choice) != 1)
        {
            clearInput();
            choice = -1;
            printf("\n");
            continue;
        }
        switch (choice)
        {
        case 0:
            if (roomCount > 0 && saveToFile("data.txt") == 0)
                printf("-> Da tu dong luu vao data.txt\n");
            printf("Tam biet!\n");
            break;
        case 1:
        {
            int id, chon, kq, idx;
            while (1)
            {
                id = (int)nhapSo("Nhap ma phong: ", 1, 2147483647, "Ma phong khong hop le! Vui long nhap lai.\n");
                if (findRooms(id) != -1)
                {
                    printf("Ma phong da ton tai!\n");
                    continue;
                }
                break;
            }
            printf("Loai phong cua khach san gom:\n");
            printf("1.Don\n2.Doi\n3.VIP\n4.TongThong\n");
            chon = (int)nhapSo("Chon loai phong: ", 1, 4, "Loai phong khong hop le!\n");
            kq = addRoom(id, chon);
            if (kq == 0)
            {
                idx = findRooms(id);
                printf("-> Da ghi nhan loai phong: %s\n", rooms[idx].roomType);
                printf("-> Gia phong: %ld VND/ngay (gia co dinh theo loai phong)\n", rooms[idx].pricePerDay);
                printf("-> So khach toi da: %d khach (co dinh theo loai phong)\n", rooms[idx].maxGuests);
                printf("Them phong thanh cong!\n");
                if (saveToFile("data.txt") == 0)
                    printf("-> Da tu dong luu vao data.txt\n");
                Enter();
            }
            else if (kq == 1)
                printf("Ma phong da ton tai!\n");
            else if (kq == 3)
                printf("Danh sach phong da day!\n");
            else
                printf("Loai phong khong hop le!\n");
            break;
        }
        case 2:
            displayRooms();
            Enter();
            break;
        case 3:
        {
            int cach;
            printf("Chon cach tim kiem:\n");
            printf("1. Theo ma phong\n");
            printf("2. Loc theo thuoc tinh\n");
            printf("3. Theo ten khach\n");
            cach = (int)nhapSo("Nhap lua chon: ", 1, 3, "Lua chon khong hop le! Vui long nhap lai.\n");
            switch (cach)
            {
                case 1:
                {
            int id, kq;
            id = (int)nhapSo("Nhap ma phong: ", 1, 2147483647, "Ma phong khong hop le! Vui long nhap lai.\n");
            kq = displayRoomById(id);
            if (kq == 0)
                printf("Khong tim thay phong!\n");
            break;
                }
                case 2:
                {
            int thuocTinh, chon, dem;
            char loai[20];
            long giaTri;
            Room tam;
            printf("Chon thuoc tinh de loc:\n");
            printf("1. Loai phong\n");
            printf("2. Trang thai\n");
            printf("3. So khach toi da\n");
            printf("4. Gia phong\n");
            printf("5. Phu hop so khach\n");
            thuocTinh = (int)nhapSo("Nhap lua chon: ", 1, 5, "Lua chon khong hop le! Vui long nhap lai.\n");
            strcpy(loai, "");
            giaTri = 0;
            if (thuocTinh == 1)
            {
            	chon = (int)nhapSo("Loai phong cua khach san gom:\n1.Don\n2.Doi\n3.VIP\n4.TongThong\n Chon loai phong: ", 1, 4, "Loai phong khong hop le!\n");
                ganLoaiPhong(&tam, chon);
                strcpy(loai, tam.roomType);
            }
            else if (thuocTinh == 2)
            {
                chon = (int)nhapSo("Chon trang thai: 1.Trong 2.Da dat: ", 1, 2, "Trang thai khong hop le!\n");
                giaTri = (chon == 2) ? 1 : 0;
            }
            else if (thuocTinh == 3)
            {
                giaTri = nhapSo("Nhap so khach toi da (1-10): ", 1, 10, "So khach khong hop le! Vui long nhap lai.\n");
            }
            else if (thuocTinh == 4)
            {
                giaTri = nhapSo("Nhap gia phong: ", 1, 2147483647L, "Gia phong khong hop le! Vui long nhap lai.\n");
            }
            else
            {
                giaTri = nhapSo("Nhap so khach (1-10): ", 1, 10, "So khach khong hop le! Vui long nhap lai.\n");
            }
            dem = filterRooms(thuocTinh, loai, giaTri);
            if (dem > 0)
                printf("Tim thay %d phong.\n", dem);
            else
                printf("Khong co phong phu hop.\n");
            break;
                }
                case 3:
                {
                    int dem, i, coKhach;
                    char ten[51];
                    coKhach = 0;
                    for (i = 0; i < roomCount; i++)
                    {
                        if (phongCoTrangThai(i, ROOM_BOOKED))
                        {
                            coKhach = 1;
                            break;
                        }
                    }
                    if (!coKhach)
                    {
                        printf("Khong tim thay phong!\n");
                        break;
                    }
                    clearInput();
                    nhapChuoi("Nhap ten khach: ", ten, 2);
                    dem = searchRoomsByName(ten);
                    if (dem > 0)
                        printf("Tim thay %d phong.\n", dem);
                    else
                        printf("Khong tim thay phong!\n");
                    break;
                }
                default:
                    printf("Lua chon khong hop le!\n");
                    break;
            }
            break;
        }
        case 4:
        {
            int id, guests, kq, idx;
            char ten[51], ngayVao[32], ngayRa[32], pr[80];
            printf("------DAT PHONG------\n");
            id = (int)nhapSo("Nhap ma phong: ", 1, 2147483647, "Ma phong khong hop le! Vui long nhap lai.\n");
            idx = findRooms(id);
            if (idx == -1)
            {
                printf("Khong tim thay phong!\n");
                break;
            }
            if (phongCoTrangThai(idx, ROOM_BOOKED))
            {
                printf("Phong nay da duoc dat roi!\n");
                break;
            }
            clearInput();
            nhapChuoi("Nhap ho & ten cua ban: ", ten, 2);
            snprintf(pr, sizeof(pr), "Nhap so luong khach (Toi da %d khach): ", rooms[idx].maxGuests);
            guests = (int)nhapSo(pr, 1, rooms[idx].maxGuests, "So luong khach khong hop le! Vui long nhap lai.\n");
            clearInput();
            nhapChuoi("Nhap ngay vao (DDMMYYYY): ", ngayVao, 1);
            while (1)
            {
                nhapChuoi("Nhap ngay ra (DDMMYYYY): ", ngayRa, 1);
                if (ngayRaHopLe(ngayVao, ngayRa))
                    break;
                printf("Ngay ra phai tu ngay vao tro di! Vui long nhap lai.\n");
            }
            kq = bookRoom(id, ten, guests, ngayVao, ngayRa);
            if (kq == 0)
            {
                printf("Da dat phong cho anh/chi: %s \n", ten);
                printf("---DAT PHONG THANH CONG---\n");
            }
            else if (kq == 1)
                printf("Khong tim thay phong!\n");
            else if (kq == 2)
                printf("Phong nay da duoc dat roi!\n");
            else if (kq == 3)
                printf("So luong khach khong hop le!\n");
            else if (kq == 4)
                printf("Ngay khong hop le!\n");
            else
                printf("Ngay ra phai tu ngay vao tro di!\n");
            break;
        }
        case 5:
        {
            int id, kq, idx, soNgay;
            long tien, donGia;
            char ngayRa[32], tenKhach[51], ngayVao[32];
            printf("------TRA PHONG------\n");
            id = (int)nhapSo("Nhap ma phong: ", 1, 2147483647, "Ma phong khong hop le! Vui long nhap lai.\n");
            idx = findRooms(id);
            if (idx == -1)
            {
                printf("Khong tim thay phong!\n");
                break;
            }
            if (phongCoTrangThai(idx, ROOM_EMPTY))
            {
                printf("Phong nay dang trong, chua duoc dat!\n");
                break;
            }
            if (!xacNhan("Ban co chac chan muon tra phong? (y/n): "))
            {
                printf("Da huy tra phong.\n");
                clearInput();
                break;
            }
            clearInput();
            while (1)
            {
                nhapChuoi("Nhap ngay ra (DDMMYYYY): ", ngayRa, 1);
                if (ngayRaHopLe(rooms[idx].checkInDate, ngayRa))
                    break;
                printf("Ngay ra phai tu ngay vao tro di! Vui long nhap lai.\n");
            }
            strcpy(tenKhach, rooms[idx].guestName);
            strcpy(ngayVao, rooms[idx].checkInDate);
            donGia = rooms[idx].pricePerDay;
            kq = checkoutRoom(id, ngayRa, &soNgay, &tien);
            if (kq == 0)
            {
                printf("----HOA DON THANH TOAN----\n");
                printf("Ma phong: %d\n", id);
                printf("Khach hang: %s\n", tenKhach);
                printf("Ngay vao: %s\n", ngayVao);
                printf("Ngay ra: %s\n", ngayRa);
                printf("So ngay o: %d ngay\n", soNgay);
                printf("Don gia: %ld VND/ngay\n", donGia);
                printf("Thanh tien: %ld VND\n", tien);
                printf("Thanh toan thanh cong!\n");
            }
            else if (kq == 1)
                printf("Khong tim thay phong!\n");
            else if (kq == 2)
                printf("Phong nay dang trong, chua duoc dat!\n");
            else if (kq == 3)
                printf("Ngay khong hop le!\n");
            else
                printf("Ngay ra phai tu ngay vao tro di!\n");
            break;
        }
        case 6:
        {
            int id, chon, kq, idx;
            long gia;
            int soKhach;
            char ten[51], ngay[32];
            id = (int)nhapSo("Nhap ma phong can cap nhat: ", 1, 2147483647, "Ma phong khong hop le! Vui long nhap lai.\n");
            if (!roomExists(id))
            {
                printf("Khong tim thay phong!\n");
                break;
            }
            printf("Chon thuoc tinh can cap nhat:\n");
            printf("1. Loai phong\n");
            printf("2. Gia phong\n");
            printf("3. So khach toi da\n");
            printf("4. Ten khach\n");
            printf("5. Ngay vao\n");
            printf("6. Ngay ra\n");
            chon = (int)nhapSo("Nhap lua chon: ", 1, 6, "Lua chon khong hop le! Vui long nhap lai.\n");
            kq = -1;
            if (chon == 1)
            {
                int loaiChon;
                loaiChon = (int)nhapSo("Chon loai phong moi: 1.Don 2.Doi 3.VIP 4.TongThong: ", 1, 4, "Loai phong khong hop le!\n");
                kq = capNhatPhong(id, 1, loaiChon, 0, NULL);
                idx = findRooms(id);
                if (kq == 0)
                {
                    printf("Gia phong moi: %ld VND/ngay (gia co dinh theo loai phong)\n", rooms[idx].pricePerDay);
                    printf("So khach toi da moi: %d khach\n", rooms[idx].maxGuests);
                    printf("Cap nhat phong thanh cong!\n");
                }
                else if (kq == 1)
                    printf("Khong tim thay phong!\n");
                else if (kq == 2)
                    printf("Phong dang co khach, khong duoc sua loai phong!\n");
                else
                    printf("Loai phong khong hop le!\n");
            }
            else if (chon == 2)
            {
                gia = nhapSo("Nhap gia phong moi: ", 1, 2147483647L, "Gia phong khong hop le! Vui long nhap lai.\n");
                kq = capNhatPhong(id, 2, 0, gia, NULL);
                if (kq == 0)
                    printf("Cap nhat gia phong thanh cong!\n");
                else if (kq == 1)
                    printf("Khong tim thay phong!\n");
                else if (kq == 2)
                    printf("Phong dang co khach, khong duoc sua gia phong!\n");
                else
                    printf("Gia phong khong hop le!\n");
            }
            else if (chon == 3)
            {
                soKhach = (int)nhapSo("Nhap so khach toi da moi (1-10): ", 1, 10, "So khach khong hop le! Vui long nhap lai.\n");
                kq = capNhatPhong(id, 3, soKhach, 0, NULL);
                if (kq == 0)
                    printf("Cap nhat so khach toi da thanh cong!\n");
                else if (kq == 1)
                    printf("Khong tim thay phong!\n");
                else if (kq == 2)
                    printf("Phong dang co khach, khong duoc sua so khach toi da!\n");
                else
                    printf("So khach khong hop le!\n");
            }
            else if (chon == 4)
            {
                clearInput();
                nhapChuoi("Nhap ten khach moi: ", ten, 2);
                kq = capNhatPhong(id, 4, 0, 0, ten);
                if (kq == 0)
                    printf("Cap nhat ten khach thanh cong!\n");
                else if (kq == 1)
                    printf("Khong tim thay phong!\n");
                else if (kq == 3)
                    printf("Phong dang trong, khong co khach de doi ten!\n");
                else
                    printf("Ten khach hang khong hop le!\n");
            }
            else if (chon == 5)
            {
                clearInput();
                nhapChuoi("Nhap ngay vao moi (DDMMYYYY): ", ngay, 1);
                kq = capNhatPhong(id, 5, 0, 0, ngay);
                if (kq == 0)
                    printf("Cap nhat ngay vao thanh cong!\n");
                else if (kq == 1)
                    printf("Khong tim thay phong!\n");
                else if (kq == 3)
                    printf("Phong dang trong, khong co ngay vao de sua!\n");
                else
                    printf("Ngay vao phai truoc hoac bang ngay ra!\n");
            }
            else
            {
                clearInput();
                nhapChuoi("Nhap ngay ra moi (DDMMYYYY): ", ngay, 1);
                kq = capNhatPhong(id, 6, 0, 0, ngay);
                if (kq == 0)
                    printf("Cap nhat ngay ra thanh cong!\n");
                else if (kq == 1)
                    printf("Khong tim thay phong!\n");
                else if (kq == 3)
                    printf("Phong dang trong, khong co ngay ra de sua!\n");
                else
                    printf("Ngay ra phai tu ngay vao tro di!\n");
            }
            break;
        }
        case 7:
        {
            int id, kq, idx;
            char pr[80];
            id = (int)nhapSo("Nhap ma phong can xoa: ", 1, 2147483647, "Ma phong khong hop le! Vui long nhap lai.\n");
            idx = findRooms(id);
            if (idx == -1)
            {
                printf("Khong tim thay phong!\n");
                break;
            }
            if (phongCoTrangThai(idx, ROOM_BOOKED))
            {
                printf("Phong dang duoc dat, khong the xoa!\n");
                break;
            }
            snprintf(pr, sizeof(pr), "Ban co chac chan muon xoa phong %d? (y/n): ", id);
            if (!xacNhan(pr))
            {
                printf("Da huy xoa phong.\n");
                clearInput();
                break;
            }
            clearInput();
            kq = deleteRoom(id);
            if (kq == 0)
                printf("Xoa phong thanh cong!\n");
            else if (kq == 1)
                printf("Khong tim thay phong!\n");
            else
                printf("Phong dang duoc dat, khong the xoa!\n");
            break;
        }
        case 8:
        {
            int tong, trong, daDat;
            thongKe(&tong, &trong, &daDat);
            printf("------THONG KE DOANH THU------\n");
            printf("Tong so phong: %d\n", tong);
            printf("So phong dang trong: %d\n", trong);
            printf("So phong da co nguoi: %d\n", daDat);
            if (tong > 0)
                printf("Ty le lap day: %.1f%%\n", daDat * 100.0 / tong);
            printf("Tong doanh thu cua khach san la: %ld VND\n", totalRevenue);
            
            Enter();
            break;
        }
        case 9:
        {
            int tangDan;
            if (roomCount < 2)
            {
                printf("Khong du phong de sap xep!\n");
                break;
            }
            printf("--- SAP XEP PHONG THEO GIA ---\n");
            printf("1. Tang dan theo gia\n");
            printf("2. Giam dan theo gia\n");
            tangDan = (int)nhapSo("Nhap lua chon: ", 1, 2, "Lua chon khong hop le!\n");
            clearInput();
            sortByPrice(tangDan);
            printf("Sap xep phong thanh cong! Hay chon chuc nang 2 de xem lai danh sach.\n");
            break;
        }
        case 10:
        {
            int kq;
            char tenFile[100], fullPath[120];
            if (roomCount == 0)
            {
                printf("Danh sach phong dang trong, khong co gi de luu!\n");
                break;
            }
            printf("Nhap ten file muon luu (khong can .txt): ");
            if (scanf("%99s", tenFile) != 1)
            {
                printf("Ten file khong hop le!\n");
                break;
            }
            clearInput();
            lapTenFileTxt(tenFile, fullPath, sizeof(fullPath));
            kq = saveToFile(fullPath);
            if (kq == 0)
                printf("Luu file %s thanh cong!\n", fullPath);
            else if (kq == 1)
                printf("Danh sach phong dang trong, khong co gi de luu!\n");
            else
                printf("Khong mo duoc file de ghi!\n");
            break;
        }
        case 11:
        {
            int kq;
            char tenFile[100], fullPath[120];
            if (!xacNhan("Doc file se xoa du lieu hien tai. Tiep tuc? (y/n): "))
            {
                printf("Da huy doc file.\n");
                clearInput();
                break;
            }
            clearInput();
            printf("Nhap ten file muon doc (khong can .txt): ");
            if (scanf("%99s", tenFile) != 1)
            {
                printf("Ten file khong hop le!\n");
                break;
            }
            clearInput();
            lapTenFileTxt(tenFile, fullPath, sizeof(fullPath));
            kq = loadFromFile(fullPath);
            if (kq == 0)
                printf("Doc file %s va cap nhat danh sach thanh cong!\n", fullPath);
            else if (kq == 1)
                printf("Khong tim thay file %s!\n", fullPath);
            else
                printf("Du lieu file khong hop le! Giu nguyen danh sach hien tai.\n");
            break;
        }
        default:
            printf("Lua chon khong hop le!\n");
            break;
        }
        if (choice != 0)
            printf("\n");
    } while (choice != 0);
    return 0;
}
