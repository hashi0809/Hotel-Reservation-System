void addRoom(void) 
{
    if (roomCount >= MAX)
    {
        printf("Danh sach phong da day!\n");
        return;
    }

    Room r = {0};

    printf("Nhap ma phong: ");
    if (scanf("%d", &r.roomId) != 1 || r.roomId <= 0)
    {
        printf("Ma phong khong hop le!\n");
        printf("Nhan enter de nhap lai");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == r.roomId)
        {
            printf("Ma phong da ton tai!\n");
        	scanf("%*[^\n]");
        	getchar();
            return;
        }
    }

    printf("Nhap loai phong (Don/Doi/Vip/TongThong): ");
    if (scanf("%19s", r.roomType) != 1)
        return;

    char firstChar = r.roomType[0];
    
    if (firstChar == 'V' || firstChar == 'v') 
    {
        strcpy(r.roomType, "VIP");
    } 
    else if (firstChar == 'T' || firstChar == 't') 
    {
        strcpy(r.roomType, "TongThong");
    } 
    else if (firstChar == 'D' || firstChar == 'd') 
    {
        int len = strlen(r.roomType);
        char lastChar = r.roomType[len - 1];

        if (len == 1 || lastChar == 'n' || lastChar == 'N') 
        {
            strcpy(r.roomType, "Don");
        } 
        else if (lastChar == 'i' || lastChar == 'I') 
        {
            strcpy(r.roomType, "Doi");
        } 
        else 
        {
            printf("Loai phong khong hop le!\n");
            scanf("%*[^\n]");
        	getchar();
            return;
        }
    } 
    else 
    {
        printf("Loai phong khong hop le!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    printf("-> Da ghi nhan loai phong: %s\n", r.roomType); 

    printf("Nhap gia phong: ");
    if (scanf("%ld", &r.pricePerDay) != 1 || r.pricePerDay <= 0)
    {
        printf("Gia phong khong hop le!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    printf("Nhap so khach toi da (1-10): ");
    if (scanf("%d", &r.maxGuests) != 1 || r.maxGuests < 1 || r.maxGuests > 10)
    {
        printf("So khach phai tu 1 den 10!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    scanf("%*[^\n]");
    getchar();

    r.status = ROOM_EMPTY;
    strcpy(r.guestName, "");
    strcpy(r.checkInDate, "");
    strcpy(r.checkOutDate, "");

    rooms[roomCount] = r;
    roomCount++;

    printf("Them phong thanh cong!\n");
}

void displayRooms(void) 
{
    if (roomCount == 0)
    {
        printf("Danh sach phong dang trong!\n");
        return;
    }

    printf("\n=================================================================================================================\n");
    printf("%-10s %-12s %-12s %-10s %-12s %-20s %-12s %-12s\n",
           "Ma phong", "Loai", "Gia/ngay", "Max Khach", "Trang thai", "Ten khach hang", "Ngay vao", "Ngay ra");
    printf("=================================================================================================================\n");

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].status == ROOM_BOOKED)
        {
            printf("%-10d %-12s %-12ld %-10d %-12s %-20s %-12s %-12s\n",
                   rooms[i].roomId,
                   rooms[i].roomType,
                   rooms[i].pricePerDay,
                   rooms[i].maxGuests,
                   "Da dat",
                   rooms[i].guestName,
                   rooms[i].checkInDate,
                   strlen(rooms[i].checkOutDate) > 0 ? rooms[i].checkOutDate : "Chua tra");
        }
        else
        {
            printf("%-10d %-12s %-12ld %-10d %-12s %-20s %-12s %-12s\n",
                   rooms[i].roomId,
                   rooms[i].roomType,
                   rooms[i].pricePerDay,
                   rooms[i].maxGuests,
                   "NULL",
                   "NULL",
                   "NULL",
                   "NULL");
        }
    }
    printf("=================================================================================================================\n\n");
}





void saveToFile(void)
{
    char fileName[100];
    char fullPath[120];
    int c;

    printf("Nhap ten file muon luu (khong can .txt): ");
    if (scanf("%99s", fileName) != 1)
    {
        printf("Ten file khong hop le!\n");
        return;
    }
   	scanf("%*[^\n]");
        getchar();

    sprintf(fullPath, "%s.txt", fileName);
    FILE *f = fopen(fullPath, "w");

    if (f == NULL)
    {
        printf("Khong mo duoc file d? ghi!\n");
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        fprintf(f, "%d|%s|%ld|%d|%d",
                rooms[i].roomId,
                rooms[i].roomType,
                rooms[i].pricePerDay,
                rooms[i].maxGuests,
                rooms[i].status);

        if (rooms[i].status == ROOM_BOOKED)
        {
            fprintf(f, "|%s|%s|%s\n",
                    rooms[i].guestName,
                    rooms[i].checkInDate,
                    rooms[i].checkOutDate);
        }
        else
        {
            fprintf(f, "|NULL|NULL|NULL\n");
        }
    }

    fclose(f);
    printf("Luu file %s thanh cong!\n", fullPath);
}

void loadFromFile(void)
{
    char fileName[100];
    char fullPath[120];
    Room temp[MAX];
    int count = 0;
    char line[256];
    int c;

    printf("Nhap ten file muon doc (khong can .txt): ");
    if (scanf("%99s", fileName) != 1)
    {
        printf("Ten file khong hop le!\n");
        return;
    }
    scanf("%*[^\n]");
    getchar();

    sprintf(fullPath, "%s.txt", fileName);
    FILE *f = fopen(fullPath, "r");

    if (f == NULL)
    {
        printf("Khong tim thay file %s!\n", fullPath);
        return;
    }

    while (fgets(line, sizeof(line), f) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';
        
        if (strlen(line) == 0) continue;

        Room r = {0};
        char gName[51] = {0};
        char cIn[11] = {0};
        char cOut[11] = {0};

        int n = sscanf(line, "%d|%19[^|]|%ld|%d|%d|%50[^|]|%10[^|]|%10s",
                       &r.roomId,
                       r.roomType,
                       &r.pricePerDay,
                       &r.maxGuests,
                       &r.status,
                       gName,
                       cIn,
                       cOut);

        if (n != 8 || count >= MAX)
        {
            printf("Du lieu file khong dung dinh dang 8 truong!\n");
            fclose(f);
            return;
        }

        if (r.status == ROOM_EMPTY)
        {
            r.guestName[0] = '\0';
            r.checkInDate[0] = '\0';
            r.checkOutDate[0] = '\0';
        }
        else
        {
            strcpy(r.guestName, gName);
            strcpy(r.checkInDate, cIn);
            strcpy(r.checkOutDate, cOut);
        }

        temp[count] = r;
        count++;
    }

    fclose(f);

    for (int i = 0; i < count; i++)
        rooms[i] = temp[i];

    roomCount = count;
    printf("Doc file %s va cap nhat danh sach thanh cong!\n", fullPath);
}




void updateRoom(void) 
{
	  int id, index = -1, c;
    Room r;

    printf("Nhap ma phong can cap nhat: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Ma phong khong hop le!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Khong tim thay phong!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    scanf("%*[^\n]");
    getchar();
        
    r = rooms[index];

    printf("Nhap loai phong moi: ");
    if (scanf("%19s", r.roomType) != 1)
        return;

    char firstChar = r.roomType[0];
    
    if (firstChar == 'V' || firstChar == 'v') 
    {
        strcpy(r.roomType, "VIP");
    } 
    else if (firstChar == 'T' || firstChar == 't') 
    {
        strcpy(r.roomType, "TongThong");
    } 
    else if (firstChar == 'D' || firstChar == 'd') 
    {
        int len = strlen(r.roomType);
        char lastChar = r.roomType[len - 1];

        if (len == 1 || lastChar == 'n' || lastChar == 'N') 
        {
            strcpy(r.roomType, "Don");
        } 
        else if (lastChar == 'i' || lastChar == 'I') 
        {
            strcpy(r.roomType, "Doi");
        } 
        else 
        {
            printf("Loai phong khong hop le!\n");
            scanf("%*[^\n]");
        	getchar();
            return;
        }
    } 

	if(firstChar == 'D' || firstChar == 'd')
	{
		int len = strlen(r.roomType);
        char lastChar = r.roomType[len - 1];
        
		if(lastChar == 'n' || lastChar == 'N')
		{
			printf("so khach toi da moi: 1\n");
			r.maxGuests = 1;
		}
		else if(lastChar == 'i' || lastChar == 'I')
		{
			printf("so khach toi da moi: 2\n");
			r.maxGuests = 2;
		}
	}
	
	else if(firstChar == 'V' || firstChar == 'v') 
	{
		printf("Nhap so khach toi da moi (1-5): ");
		if (scanf("%d", &r.maxGuests) != 1 ||
    	r.maxGuests < 1 || r.maxGuests > 5)
		{	
    	printf("So khach phai tu 1 den 5!\n");
    	scanf("%*[^\n]");
    	getchar();
    	return;
    	}
	}
	else if (firstChar == 'T' || firstChar == 't') 
	{
		printf("Nhap so khach toi da moi (1-10): ");
		if (scanf("%d", &r.maxGuests) != 1 ||
    	r.maxGuests < 1 || r.maxGuests > 10)
		{	
    	printf("So khach phai tu 1 den 10!\n");
    	scanf("%*[^\n]");
    	getchar();
    	return;
    	}
	}
	scanf("%*[^\n]");
    getchar();
		
    rooms[index] = r;
    printf("Cap nhat phong thanh cong!\n"); 
}

void deleteRoom(void) 
{
int id, index = -1, c;

    printf("Nhap ma phong can xoa: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Ma phong khong hop le!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Khong tim thay phong!\n");
       	scanf("%*[^\n]");
        getchar();
        return;
    }

    if (rooms[index].status == ROOM_BOOKED)
    {
        printf("Phong dang duoc dat, khong the xoa!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    for (int i = index; i < roomCount - 1; i++)
        rooms[i] = rooms[i + 1];

    roomCount--;

    scanf("%*[^\n]");
    getchar();
    printf("Xoa phong thanh cong!\n");
}