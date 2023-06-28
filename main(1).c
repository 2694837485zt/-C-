#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

//�����������
struct goods {
	int goods_number;//���
	char name[30];//��������
	char producer[30];//��������
	char type[30];//����
	int price;//�ۼ�
	int totality;//�����

	struct goods* next;//������һ������
};

//��ʼ��������Ϣ
struct goods* Inti_header(void);
//����������Ϣ
void Inti_GoodsList(struct goods* header);
//����B�滻����A��λ��
//>>��Ų�ѯ��ʽ
void Insert_GoodsList(struct goods* header, int oleNumber);
//ɾ������A
//>>��Ų�ѯ��ʽ
void Del_GoodsList(struct goods* header);
//�޸Ļ������Ϣ
//>>��Ų�ѯ��ʽ
void Modify_GoodsList(struct goods* header);
//չʾ���л�����Ϣ(����)
void Showall_GoodsList(struct goods* header);
//����ĳ������
//>>��Ų�ѯ��ʽ
void ShowOne_GoodsList(struct goods* header);
//����
//>>�����
void Sort_GoodsList(struct goods* header);

//���۹���
void sell_goods(struct goods* head);

//����
void Save_GoodsList(struct goods* header, char* filename);
//��ȡ�ļ�����������
void  OutputFile(struct goods* header, char* filename);
//������뻺����
void FreeBuff(void);


//�˵�
void menu(void);
//>>����������Ϣ�˵�
void menu_Inti_GoodsList(void);
//>>չʾ���л�����Ϣ�˵�
void menu_Showall_GoodsList(void);
//>>�޸Ļ�����Ϣ�˵�
void menu_Modify_GoodsList(void);
//>>���������Ϣ�˵�
void menu_Sort_GoodsList(void);
//>>���һ�����Ϣ�˵�
void menu_ShowOne_GoodsList(void);
//>>���ܲ˵�
void menu_Shelt(void);
//����
void menu_sell_goods(void);
//��궨λ
void gotoxy(int x, int y);
//����
void clr_scr(int w_start, int h_start, int w_end, int h_end);



void run(void) {
	//������������
	struct goods* OnShelf = Inti_header();//�ϼܵĻ����嵥
	struct goods* OffShelf = Inti_header();//�¼ܵĻ����嵥
	struct goods* Order = Inti_header();//�����嵥
	struct goods* Temp = OnShelf;

	//���س�ʼ������Ϣ
	OutputFile(OnShelf, "���ۻ�����Ϣ.txt");
	OutputFile(OffShelf, "�¼ܻ�����Ϣ.txt");
	OutputFile(Order, "������Ϣ.txt");
	int shelf_code = -1;
	while (1) {
		menu_Shelt();
		printf("��ѡ�����:");
		scanf("%d", &shelf_code);
		FreeBuff();
		switch (shelf_code)
		{
		case 1:
			Temp = OnShelf;
			break;
		case 2:
			Temp = OffShelf;
			break;
		case 3:
			Temp = Order;
			break;
		case 4:
			exit(0);
			break;
		default:
			gotoxy(0, 16);
			printf("���ִ���...");
			clr_scr(0, 18, 35, 30);//���ָ���
			break;
		}

		while (1) {
			menu();
			int project_num = -1;
			printf("��ѡ����:");
			scanf("%d", &project_num);
			switch (project_num)
			{
			case 1:
				clr_scr(0, 0, 90, 40);
				Inti_GoodsList(Temp);
				break;
			case 2:
				Del_GoodsList(Temp);
				break;
			case 3:
				clr_scr(0, 0, 90, 40);
				ShowOne_GoodsList(Temp);
				break;
			case 4:
				clr_scr(0, 0, 90, 40);
				Modify_GoodsList(Temp);
				break;
			case 5:
				clr_scr(0, 0, 90, 40);
				Showall_GoodsList(Temp);
				break;
			case 6:
				clr_scr(0, 0, 90, 40);
				Sort_GoodsList(Temp);
				break;
			case 7:
				clr_scr(0, 0, 90, 40);
				sell_goods(Temp);
				break;
			case 8:
				if (shelf_code == 1) {
					Save_GoodsList(Temp, "���ۻ�����Ϣ.txt");
				}
				if (shelf_code == 2) {
					Save_GoodsList(Temp, "�¼ܻ�����Ϣ.txt");
				}
				if (shelf_code == 3) {
					Save_GoodsList(Temp, "������Ϣ.txt");
				}
				break;

			case 9:
				break;
			default:
				break;
			}
			if (project_num == 9)
			{
				break;
			}
			clr_scr(0, 0, 90, 40);
		}
		clr_scr(0, 0, 90, 40);
	}
}

void main(void) {
	run();


}

// ҵ��
struct goods* Inti_header(void) {
	//����ͷ���
	struct goods* header = malloc(sizeof(struct goods));
	header->goods_number = 0;
	*header->name = "header";//header->name �Ƕ���ָ�룬��Ϊname�����飬�ö���ָ��ָ��name�ĵ�ַ��Ҳ������Ԫ�ص�ַ�����Բ�����ֱ�Ӹ�ֵ����Ҫ�õ���*��
	*header->producer = "producer";
	*header->type = "type";
	header->price = 0;
	header->totality = 0;
	header->next = NULL;

	return header;
}
void Inti_GoodsList(struct goods* header) {
	menu_Inti_GoodsList();
	struct goods* pRear = header;//β��ָ��
	int temp_Number = -1;//װ����
	char temp_String[30];
	int intput_flag = -1;//�����־
	//��ָ���ƶ������һ�����
	while (pRear != NULL) {
		if (pRear->next == NULL) {
			break;
		}
		pRear = pRear->next;//��ʱָ���ƶ�
	}

	while (1) {
		//�����»���ڵ�
		struct goods* pTemp = malloc(sizeof(struct goods));
		pTemp->next = NULL;//���һ���ڵ�ָ���
		pRear->next = pTemp;//����ǰһ���ڵ�

		printf("������:");
		while (1) {
			scanf("%d", &temp_Number);
			if (temp_Number < 0) {
				gotoxy(0, 16);
				printf("�����������������...");
				clr_scr(0, 18, 35, 19);//��������
				gotoxy(0, 18);
				printf("������:");
				FreeBuff();
			}
			else {
				clr_scr(0, 16, 35, 17);//���������ʾ
				gotoxy(0, 19);//����ƶ�����һ��
				pTemp->goods_number = temp_Number;
				break;
			}
		}
		FreeBuff();
		//TODO  ������Ϣ¼��


		printf("��������:");
		scanf("%s", &temp_String);
		strcpy(pTemp->name, temp_String);//NOTE ���ַ������飬��ֵ����
		FreeBuff();


		printf("��������:");
		scanf("%s", &temp_String);
		strcpy(pTemp->producer,temp_String);
		FreeBuff();

		printf("���:");
		scanf("%s", &temp_String);
		strcpy(pTemp->type, temp_String);
		FreeBuff();

		//TODO  ��ջ�����

		printf("�ۼ�:");
		while (1) {
			scanf("%d", &temp_Number);
			if (temp_Number < 0) {
				gotoxy(0, 16);
				printf("�����������������...");
				clr_scr(0, 22, 35, 23);//��������
				gotoxy(0, 22);
				printf("�ۼ�:");
				FreeBuff();
			}
			else {
				clr_scr(0, 16, 35, 17);//���������ʾ
				gotoxy(0, 23);//����ƶ�����һ��
				pTemp->price = temp_Number;
				break;
			}
		}
		FreeBuff();

		printf("�����:");
		while (1) {
			scanf("%d", &temp_Number);
			if (temp_Number < 0) {
				gotoxy(0, 16);
				printf("�����������������...");
				clr_scr(0, 23, 35, 24);//��������
				gotoxy(0, 23);
				printf("�����:");
				FreeBuff();
			}
			else {
				clr_scr(0, 16, 35, 17);//���������ʾ
				gotoxy(0, 24);//����ƶ�����һ��
				pTemp->totality = temp_Number;
				break;
			}
		}
		FreeBuff();

		//���ָ���
		clr_scr(0, 18, 35, 30);
		//�����ʾ��
		clr_scr(0, 16, 35, 17);
		//¼�뷴��
		gotoxy(0, 14);
		printf("�Ѿ��ɹ�¼��һ��������Ϣ...\n1.����¼��\n2.����¼��\n");
		gotoxy(0, 18);
		printf("ָ��:");
		scanf("%d", &intput_flag);
		FreeBuff();

		//���ָ���
		clr_scr(0, 18, 35, 30);
		//�����ʾ��
		clr_scr(0, 14, 35, 17);
		gotoxy(0, 18);

		if (intput_flag == 1) {
			break;
		}

		pRear = pTemp;//β��ָ���ƶ�
	}
}
void Showall_GoodsList(struct goods* header) {
	menu_Showall_GoodsList();
	if (header == NULL) {
		return;
	}

	struct goods* pTemp = header->next;//��ʱָ��
	int y = 4;
	while (pTemp != NULL) {
		gotoxy(9, y);
		printf("%d", pTemp->goods_number);//������
		gotoxy(18, y);
		printf("%s", &pTemp->name);//��������
		gotoxy(27, y);
		printf("%s", &pTemp->producer);//��������
		gotoxy(42, y);
		printf("%s", &pTemp->type);//���
		gotoxy(52, y);
		printf("%d", pTemp->price);//�ۼ�
		gotoxy(65, y);
		printf("%d", pTemp->totality);//�����
		printf("\n");
		y++;//����ƶ�
		pTemp = pTemp->next;//��ʱָ���ƶ�
	}
	//��������
	gotoxy(0, 15);
	printf("����������ز˵�...\n�Ѿ��ɹ���ʾ���л�����Ϣ...\n");
	gotoxy(0, 18);
	printf("ָ��:");
	getchar();
	FreeBuff();


}
void Del_GoodsList(struct goods* header) {

	if (header == NULL) {
		return;
	}
	//��������ָ��
	struct goods* pCrr = header->next;
	struct goods* pBhd = header;
	//���ҵı��
	char temp_String[30];
	gotoxy(0, 19);
	printf("��ɾ���Ļ��������:");
	scanf("%s", &temp_String);
	FreeBuff();
	while (pCrr != NULL) {
		if (strstr(pCrr->name, temp_String) != NULL) { // ��strcmp��Ϊstrstr������ģ��ƥ��
			pBhd->next = pCrr->next;//���½���ǰ���ͺ�̽��Ĺ�ϵ
			free(pCrr);//�ͷŽ����ڴ�
			clr_scr(0, 19, 35, 30);
			gotoxy(0, 16);
			printf("�ɹ�ɾ��,����������˳�...\n");
			gotoxy(0, 29);
			printf("ָ��:");
			getchar();
			FreeBuff();
			return;
		}
		//ָ���ƶ�
		pBhd = pCrr;
		pCrr = pCrr->next;
	}
	//���ָ���
	clr_scr(0, 19, 35, 30);
	gotoxy(0, 16);
	printf("δ�ҵ�����Ʒ,����������˳�...\n");
	gotoxy(0, 19);
	printf("ָ��:");
	getchar();
	FreeBuff();
	return;
}
void sell_goods(struct goods* header) {
	menu_sell_goods();
	if (header == NULL) {
		return;
	}
	struct goods* pTemp = header->next;//��ʱָ��
	int y = 4;
	while (pTemp != NULL) {
		gotoxy(9, y);
		printf("%d", pTemp->goods_number);//������
		gotoxy(18, y);
		printf("%s", &pTemp->name);//��������
		gotoxy(27, y);
		printf("%s", &pTemp->producer);//��������
		gotoxy(42, y);
		printf("%s", &pTemp->type);//���
		gotoxy(52, y);
		printf("%d", pTemp->price);//�ۼ�
		gotoxy(65, y);
		printf("%d", pTemp->totality);//�����
		printf("\n");
		y++;//����ƶ�
		pTemp = pTemp->next;//��ʱָ���ƶ�
	}
	char input_type[30], input_name[30];
	int input_quantity;
	struct goods* ptr = header->next;

	// ����������Ʒ����
	gotoxy(0, 18);
	printf("��������Ʒ���");
	scanf("%s", &input_type);
	FreeBuff();
	//���ָ���
	clr_scr(0, 18, 35, 30);

	gotoxy(0, 18);
	printf("��������Ʒ���ƣ�");
	scanf("%s", &input_name);
	FreeBuff();
	//���ָ���
	clr_scr(0, 18, 35, 30);

	// ���Ҹ���Ʒ�Ƿ����
	while (ptr != NULL) {
		if (strcmp(ptr->type, input_type) == 0 && strcmp(ptr->name, input_name) == 0)
			break;
		ptr = ptr->next;
	}

	// ��Ʒ������
	if (ptr == NULL) {
		//�����ʾ��
		clr_scr(0, 15, 35, 17);
		gotoxy(0, 15);
		printf("����Ʒ������\n");
		gotoxy(0, 18);
		printf("ָ��:");
		getchar();
		return;
	}

	// �жϿ�����Ƿ��㹻
	if (ptr->totality == 0) {
		//�����ʾ��
		clr_scr(0, 15, 35, 17);
		gotoxy(0, 15);
		printf("��Ʒ������\n");
		gotoxy(0, 18);
		printf("ָ��:");
		getchar();
		return;
	}

	// ���빺������
	gotoxy(0, 18);
	printf("�����빺��������");
	scanf("%d", &input_quantity);
	//���ָ���
	FreeBuff();
	clr_scr(0, 18, 35, 30);

	// ���������
	if (input_quantity > ptr->totality) {
		//�����ʾ��
		clr_scr(0, 15, 35, 17);
		gotoxy(0, 15);
		printf("���������\n");
		gotoxy(0, 18);
		printf("ָ��:");
		getchar();
		return;
	}

	// ���㲢���¿����
	int total_price = input_quantity * ptr->price;
	ptr->totality -= input_quantity;


	//��������
	gotoxy(0, 15);
	printf("����ɹ�");
	gotoxy(0, 18);
	printf("ָ��:");
	getchar();
	FreeBuff();
}
void Modify_GoodsList(struct goods* header) {
	menu_Modify_GoodsList();
	if (header == NULL) {
		return;
	}

	int ModifyProject_int = -1;
	int GoodsNumber = -1;
	int intput_flag = -1;
	int temp_Number = -1;//װ����
	char temp_String[30];//װ����
	char* project_list[] = { "���","��������","��������", "���", "�ۼ�", "�����" };//NOTE ���鴢�����ַ���

	gotoxy(0, 18);
	printf("������:");
	scanf("%d", &GoodsNumber);
	FreeBuff();
	//���ָ���
	clr_scr(0, 18, 35, 30);
	//����ָ��
	struct goods* pCrr = header->next;
	//����
	while (pCrr != NULL) {
		if (pCrr->goods_number == GoodsNumber) {
			break;
		}
		//ָ���ƶ�
		pCrr = pCrr->next;
	}
	if (pCrr == NULL) {
		//���ָ���
		clr_scr(0, 18, 35, 30);
		gotoxy(0, 16);
		printf("δ�ҵ�����Ʒ,����������˳�...\n");
		gotoxy(0, 18);
		printf("ָ��:");
		getchar();
		FreeBuff();
		return;
	}
	//չʾ
	gotoxy(9, 4);
	printf("%d", pCrr->goods_number);//������
	gotoxy(18, 4);
	printf("%s", &pCrr->name);//��������
	gotoxy(30, 4);
	printf("%s", &pCrr->producer);//��������
	gotoxy(42, 4);
	printf("%s", &pCrr->type);//���
	gotoxy(52, 4);
	printf("%d", pCrr->price);//�ۼ�
	gotoxy(65, 4);
	printf("%d", pCrr->totality);//�����

	gotoxy(0, 5);
	//�޸�
	while (1) {
		gotoxy(0, 18);
		printf("�������޸�ָ��:");
		scanf("%d", &ModifyProject_int);
		FreeBuff();
		//�޸���Ϣ
		switch (ModifyProject_int)
		{
		case 1:
			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("��ǰ�޸ĵ���Ŀ��\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("�������޸ĺ��\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%d", &temp_Number);
			FreeBuff();
			pCrr->goods_number = temp_Number;
			break;
		case 2:
			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("��ǰ�޸ĵ���Ŀ��\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("�������޸ĺ��\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%s", &temp_String);
			FreeBuff();
			strcpy(pCrr->name, temp_String);//NOTE �ַ�����ֵ
			break;
		case 3:
			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("��ǰ�޸ĵ���Ŀ��\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("�������޸ĺ��\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%s", &temp_String);
			FreeBuff();
			strcpy(pCrr->producer,temp_String);//NOTE �ַ�����ֵ
			break;
		case 4:
			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("��ǰ�޸ĵ���Ŀ��\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("�������޸ĺ��\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%s", &temp_String);
			FreeBuff();
			strcpy(pCrr->producer,temp_String);//NOTE �ַ�����ֵ
			break;
		case 5:
			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("��ǰ�޸ĵ���Ŀ��\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("�������޸ĺ��\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%d", &temp_Number);
			FreeBuff();
			pCrr->price = temp_Number;
			break;
		case 6:
			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("��ǰ�޸ĵ���Ŀ��\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("�������޸ĺ��\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%d", &temp_Number);
			FreeBuff();
			pCrr->totality = temp_Number;
			break;
		case 7:
			return;
		default:
			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("�����������������...\n");
			break;
		}

		if (ModifyProject_int < 7 && ModifyProject_int>0) {
			//չʾ
			clr_scr(0, 4, 50, 5);
			gotoxy(9, 4);
			printf("%d", pCrr->goods_number);//������
			gotoxy(18, 4);
			printf("%s", &pCrr->name);//��������
			gotoxy(30, 4);
			printf("%s", &pCrr->producer);//��������
			gotoxy(42, 4);
			printf("%s", pCrr->type);//���
			gotoxy(52, 4);
			printf("%d", pCrr->price);//�ۼ�
			gotoxy(65, 4);
			printf("%d", pCrr->totality);//�����
			gotoxy(0, 5);

			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
			//��������
			gotoxy(0, 14);
			printf("1.�����޸�\n2.�����޸�\n");
			gotoxy(0, 16);
			printf("�޸ĳɹ�...\n");
			gotoxy(0, 18);
			printf("ָ��:");
			scanf("%d", &intput_flag);
			FreeBuff();
			if (intput_flag == 1)
			{	//���ָ���
				clr_scr(0, 18, 35, 30);
				//�����ʾ��
				clr_scr(0, 14, 35, 17);
				return;
			}
			//���ָ���
			clr_scr(0, 18, 35, 30);
			//�����ʾ��
			clr_scr(0, 16, 35, 17);
		}
	}

}
void Sort_GoodsList(struct goods* header) {
	menu_Sort_GoodsList();
	if (header == NULL) {
		return;
	}

	//����ָ��
	struct goods* pCrr = header->next;
	struct goods* pBhd = header;
	struct goods* pMiddle = header;
	int PCrr_num = -1;
	int PMiddle_num = -1;
	//�����������
	int count = 0;
	while (pCrr != NULL) {
		count++;
		//ָ���ƶ�
		pCrr = pCrr->next;
	}

	//����
	char* project_list[] = { "���", "�ۼ�", "�����","��������" };
	int sort_project = -1;
	pCrr = header->next;//��ʼֵ
	gotoxy(0, 18);
	printf("���������������:");
	scanf("%d", &sort_project);
	FreeBuff();

	switch (sort_project) {
	case 1:
		for (int i = 0; i < count; i++) {
			//>>ָ���ʼ��
			pMiddle = header->next;
			pCrr = pMiddle->next;
			pBhd = header;
			for (int j = 0; j < count - i; j++) {
				if (pCrr == NULL) {
					break;
				}
				PCrr_num = pCrr->goods_number;
				PMiddle_num = pMiddle->goods_number;
				if (PMiddle_num > PCrr_num) {
					pMiddle->next = pCrr->next;
					pCrr->next = pMiddle;
					pBhd->next = pCrr;
				}
				pBhd = pBhd->next;
				pMiddle = pBhd->next;
				pCrr = pMiddle->next;

			}
		}
		break;
	case 2:
		for (int i = 0; i < count; i++) {
			//>>ָ���ʼ��
			pMiddle = header->next;
			pCrr = pMiddle->next;
			pBhd = header;
			for (int j = 0; j < count - i; j++) {
				if (pCrr == NULL) {
					break;
				}
				PCrr_num = pCrr->price;
				PMiddle_num = pMiddle->price;
				if (PMiddle_num > PCrr_num) {
					pMiddle->next = pCrr->next;
					pCrr->next = pMiddle;
					pBhd->next = pCrr;
				}
				pBhd = pBhd->next;
				pMiddle = pBhd->next;
				pCrr = pMiddle->next;

			}
		}
		break;
	case 3:
		for (int i = 0; i < count; i++) {
			//>>ָ���ʼ��
			pMiddle = header->next;
			pCrr = pMiddle->next;
			pBhd = header;
			for (int j = 0; j < count - i; j++) {
				if (pCrr == NULL) {
					break;
				}
				PCrr_num = pCrr->totality;
				PMiddle_num = pMiddle->totality;
				if (PMiddle_num > PCrr_num) {
					pMiddle->next = pCrr->next;
					pCrr->next = pMiddle;
					pBhd->next = pCrr;
				}
				pBhd = pBhd->next;
				pMiddle = pBhd->next;
				pCrr = pMiddle->next;

			}
		}
		break;
	case 4:
		for (int i = 0; i < count; i++) {
			// ָ���ʼ��
			pMiddle = header->next;
			pCrr = pMiddle->next;
			pBhd = header;
			for (int j = 0; j < count - i - 1; j++) { // ����ѭ����ֹ����
				if (pCrr == NULL) {
					break;
				}
				// �����������ƱȽ�
				if (strlen(pCrr->producer) > strlen(pMiddle->producer)) {
					pMiddle->next = pCrr->next;
					pCrr->next = pMiddle;
					pBhd->next = pCrr;
				}
				pBhd = pBhd->next;
				pMiddle = pMiddle->next;
				pCrr = pCrr->next; // ����ָ��λ��
			}
		}
		break;
	case 5:
		return;
		break;
	default:
		gotoxy(0, 16);
		printf("�������...");
		break;
	}
	if (sort_project < 6 && sort_project>0)
	{	//���ָ���
		clr_scr(0, 18, 35, 30);
		//�����ʾ��
		clr_scr(0, 16, 35, 17);
		//��������
		gotoxy(0, 15);
		printf("����������ز˵�...\n�Ѿ��ɹ��������л�����Ϣ...\n");
		gotoxy(0, 18);
		printf("ָ��:");
		getchar();
		FreeBuff();
	}

}
void ShowOne_GoodsList(struct goods* header) {
	menu_ShowOne_GoodsList();
	if (header == NULL) {
		return;
	}

	char temp_String[30];
	struct goods* pTemp = header->next;//��ʱָ��

	gotoxy(0, 18);
	printf("��������ҵĻ������ƣ�");
	scanf("%s", &temp_String);
	FreeBuff();
	while (pTemp != NULL) {
		if (strstr(pTemp->name, temp_String) != NULL) {
			break;
		}
		pTemp = pTemp->next;//��ʱָ���ƶ�
	}

	while (pTemp != NULL) {
		if (strstr(pTemp->name, temp_String) != NULL) {
			break;
		}
		pTemp = pTemp->next;//��ʱָ���ƶ�
	}

	if (pTemp == NULL) {
		//���ָ���
		clr_scr(0, 18, 35, 30);
		gotoxy(0, 16);
		printf("δ�ҵ�����Ʒ,����������˳�...\n");
		gotoxy(0, 18);
		printf("ָ��:");
		getchar();
		FreeBuff();
		return;
	}
	gotoxy(9, 5);
	printf("%d", pTemp->goods_number);//������
	gotoxy(18, 5);
	printf("%s", &pTemp->name);//��������
	gotoxy(30, 5);
	printf("%s", &pTemp->producer);//��������
	gotoxy(42, 5);
	printf("%s", pTemp->type);//���
	gotoxy(52, 5);
	printf("%d", pTemp->price);//�ۼ�
	gotoxy(65, 5);
	printf("%d", pTemp->totality);//�����
	printf("\n");

	//���ָ���
	clr_scr(0, 18, 35, 30);
	//�����ʾ��
	clr_scr(0, 16, 35, 17);
	gotoxy(0, 16);
	printf("���ҳɹ�,����������˳�...\n");
	gotoxy(0, 18);
	printf("ָ��:");
	getchar();
	FreeBuff();

}
void Save_GoodsList(struct goods* header, char* filename) {
	if (header == NULL) {
		return;
	}
	struct goods* pCrr = header->next;
	FILE* pList;//�ļ�ָ��
	if ((pList = fopen(filename, "w")) == NULL) {
		gotoxy(0, 16);
		printf("�޷��򿪻����ļ�\n");
		exit(0);
	}
	while (pCrr != NULL) {
		fprintf(pList, "%d\t", pCrr->goods_number);
		fprintf(pList, "%s\t", pCrr->name);
		fprintf(pList, "%s\t", pCrr->producer);
		fprintf(pList, "%s\t", pCrr->type);
		fprintf(pList, "%d\t", pCrr->price);
		fprintf(pList, "%d\t", pCrr->totality);
		fprintf(pList, "\n");
		pCrr = pCrr->next;
	}
	fclose(pList);//�ףȣ١�fopen��fcloseһ���ã���fopen_s�����Ժ�fcloseһ����
	//���ָ���
	clr_scr(0, 18, 35, 30);
	gotoxy(0, 16);
	printf("����ɹ�,����������˳�...\n");
	gotoxy(0, 18);
	printf("ָ��:");
	getchar();
	FreeBuff();
	return;

}
void  OutputFile(struct goods* header, char* filename) {
	//����ָ��
	struct goods* pCrr;
	pCrr = header;
	int goods_number;//���,�����ж��Ƿ񻹴�����Ϣ
	char str[30] = "\0";//��Ϣ���
	FILE* fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("�ļ�δ�ҵ�");
		exit(0);
		return;
	}
	while (fscanf(fp, "%d", &goods_number) != EOF) {
		struct goods* pTemp = malloc(sizeof(struct goods));
		pTemp->next = NULL;//���һ���ڵ�ָ���
		pCrr->next = pTemp;//����ǰһ���ڵ�
		//ȡֵ
		pTemp->goods_number = goods_number;//whileѭ�����ж��������Ѿ�ȡֵ��
		fscanf(fp, "%s", &str);
		strcpy(pTemp->name, str);

		fscanf(fp, "%s", &str);
		strcpy(pTemp->producer, str);

		fscanf(fp, "%s", &str);
		strcpy(pTemp->type, str);

		fscanf(fp, "%d", &pTemp->price);
		fscanf(fp, "%d", &pTemp->totality);

		pCrr = pCrr->next;
	}
	fclose(fp);


}
void FreeBuff(void) {
	//������뻺����
	scanf("%*[^\n]");
	scanf("%*c");
}
// UI
void menu(void) {
	gotoxy(36., 1);
	printf("���л������ϵͳ\n");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(42, 4);
	printf("���˵�");
	gotoxy(28, 5);
	printf("=================================");
	gotoxy(28, 6);
	printf("1.����������Ϣ     2.ɾ��������Ϣ\n");
	gotoxy(28, 7);
	printf("3.���һ�����Ϣ     4.�޸Ļ�����Ϣ\n");
	gotoxy(28, 8);
	printf("5.չʾ������Ϣ     6.������Ϣ����\n");
	gotoxy(28, 9);
	printf("7.����             8.���������Ϣ\n");
	gotoxy(28, 10);
	printf("9.�˳�\n");
	gotoxy(28, 11);
	printf("=================================");
	gotoxy(0, 18);
	printf("=========================================================================================");
}
void menu_Inti_GoodsList(void) {
	gotoxy(36, 1);
	printf("������Ϣ���ģ��");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(36, 4);
	printf("����д������Ϣ");
	gotoxy(34, 5);
	printf("===================");
	gotoxy(34, 6);
	printf("1.���     2.����\n");
	gotoxy(34, 7);
	printf("3.��������   4.���\n");
	gotoxy(34, 8);
	printf("5.���ۼ�   6.�����\n");
	gotoxy(34, 9);
	printf("===================");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void menu_Showall_GoodsList(void) {
	gotoxy(36, 1);
	printf("������Ϣչʾģ��");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(7, 3);
	printf("��  ��     ��  ��     ��������     ���     ��  ��     �����\n");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void menu_sell_goods(void) {
	gotoxy(40, 1);
	printf("��Ʒ�б�");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(7, 3);
	printf("��  ��     ��  ��     ��������     ���     ��  ��     �����\n");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void menu_Modify_GoodsList(void) {
	//չʾ��Ϣ
	gotoxy(36, 1);
	printf("������Ϣ�޸�ģ��");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(7, 3);
	printf("��  ��     ��  ��     ��������     ���     ��  ��     �����\n");
	gotoxy(0, 5);
	printf("=========================================================================================");
	printf("\n");

	//ѡ���޸ĵ���Ŀ
	gotoxy(40, 7);
	printf("ҵ��");
	gotoxy(28, 8);
	printf("============================");
	gotoxy(28, 9);
	printf("1.�޸ı��     2.�޸�����\n");
	gotoxy(28, 10);
	printf("3.�޸���������   4.�޸����\n");
	gotoxy(28, 11);
	printf("5.�޸ĳ��ۼ�   6.�޸Ŀ����\n");
	gotoxy(28, 12);
	printf("7.�˳�\n");
	gotoxy(28, 13);
	printf("============================");
	gotoxy(0, 17);
	printf("=========================================================================================");


}
void menu_Shelt(void) {
	gotoxy(0, 1);
	printf("=========================================================================================");
	gotoxy(40, 4);
	printf("�������\n");
	gotoxy(33, 5);
	printf("=====================");
	gotoxy(33, 6);
	printf("1.������     2.�¼���\n");
	gotoxy(33, 7);
	printf("3.������     4.�˳�\n");
	gotoxy(33, 8);
	printf("=====================");
	gotoxy(0, 17);
	printf("=========================================================================================");

}
void menu_Sort_GoodsList(void) {
	//ѡ����������
	gotoxy(36, 1);
	printf("������Ϣ����ģ��");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(43, 4);
	printf("��Ŀ");
	gotoxy(36, 5);
	printf("===================");
	gotoxy(36, 6);
	printf("1.���      2.�ۼ�\n");
	gotoxy(36, 7);
	printf("3.�����   4.��������\n");
	gotoxy(36, 8);
	printf("5.�˳�\n");
	gotoxy(36, 9);
	printf("===================");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void menu_ShowOne_GoodsList(void) {
	gotoxy(37, 1);
	printf("������Ϣ����ģ��");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(7, 4);
	printf("��  ��     ��  ��     ��������     ���     ��  ��     �����\n");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void clr_scr(int w_start, int h_start, int w_end, int h_end) {
	int i, j;
	for (i = w_start; i < w_end; i++) {
		for (j = h_start; j < h_end; j++)
		{
			gotoxy(i, j);
			printf(" ");
		}
	}
	printf("\n");
}
void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
