#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

//定义货物类型
struct goods {
	int goods_number;//编号
	char name[30];//货物名称
	char producer[30];//生产厂家
	char type[30];//种类
	int price;//售价
	int totality;//库存量

	struct goods* next;//链接下一个货物
};

//初始化货物信息
struct goods* Inti_header(void);
//创建货物信息
void Inti_GoodsList(struct goods* header);
//货物B替换货物A的位置
//>>编号查询方式
void Insert_GoodsList(struct goods* header, int oleNumber);
//删除货物A
//>>编号查询方式
void Del_GoodsList(struct goods* header);
//修改货物的信息
//>>编号查询方式
void Modify_GoodsList(struct goods* header);
//展示所有货物信息(遍历)
void Showall_GoodsList(struct goods* header);
//查找某个货物
//>>编号查询方式
void ShowOne_GoodsList(struct goods* header);
//排序
//>>按序号
void Sort_GoodsList(struct goods* header);

//销售功能
void sell_goods(struct goods* head);

//保存
void Save_GoodsList(struct goods* header, char* filename);
//读取文件，创建链表
void  OutputFile(struct goods* header, char* filename);
//清空输入缓存区
void FreeBuff(void);


//菜单
void menu(void);
//>>创建货物信息菜单
void menu_Inti_GoodsList(void);
//>>展示所有货物信息菜单
void menu_Showall_GoodsList(void);
//>>修改货物信息菜单
void menu_Modify_GoodsList(void);
//>>排序货物信息菜单
void menu_Sort_GoodsList(void);
//>>查找货物信息菜单
void menu_ShowOne_GoodsList(void);
//>>货架菜单
void menu_Shelt(void);
//销售
void menu_sell_goods(void);
//光标定位
void gotoxy(int x, int y);
//清屏
void clr_scr(int w_start, int h_start, int w_end, int h_end);



void run(void) {
	//创建三个链表
	struct goods* OnShelf = Inti_header();//上架的货物清单
	struct goods* OffShelf = Inti_header();//下架的货物清单
	struct goods* Order = Inti_header();//进货清单
	struct goods* Temp = OnShelf;

	//加载初始货物信息
	OutputFile(OnShelf, "在售货物信息.txt");
	OutputFile(OffShelf, "下架货物信息.txt");
	OutputFile(Order, "进货信息.txt");
	int shelf_code = -1;
	while (1) {
		menu_Shelt();
		printf("请选择货架:");
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
			printf("出现错误...");
			clr_scr(0, 18, 35, 30);//清除指令框
			break;
		}

		while (1) {
			menu();
			int project_num = -1;
			printf("请选择功能:");
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
					Save_GoodsList(Temp, "在售货物信息.txt");
				}
				if (shelf_code == 2) {
					Save_GoodsList(Temp, "下架货物信息.txt");
				}
				if (shelf_code == 3) {
					Save_GoodsList(Temp, "进货信息.txt");
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

// 业务
struct goods* Inti_header(void) {
	//创建头结点
	struct goods* header = malloc(sizeof(struct goods));
	header->goods_number = 0;
	*header->name = "header";//header->name 是二级指针，因为name是数组，该二级指针指向name的地址，也就是首元素地址，所以不可以直接赋值，需要用到‘*’
	*header->producer = "producer";
	*header->type = "type";
	header->price = 0;
	header->totality = 0;
	header->next = NULL;

	return header;
}
void Inti_GoodsList(struct goods* header) {
	menu_Inti_GoodsList();
	struct goods* pRear = header;//尾部指针
	int temp_Number = -1;//装数据
	char temp_String[30];
	int intput_flag = -1;//输入标志
	//让指针移动到最后一个结点
	while (pRear != NULL) {
		if (pRear->next == NULL) {
			break;
		}
		pRear = pRear->next;//临时指针移动
	}

	while (1) {
		//创建新货物节点
		struct goods* pTemp = malloc(sizeof(struct goods));
		pTemp->next = NULL;//最后一个节点指向空
		pRear->next = pTemp;//连接前一个节点

		printf("货物编号:");
		while (1) {
			scanf("%d", &temp_Number);
			if (temp_Number < 0) {
				gotoxy(0, 16);
				printf("输入错误，请重新输入...");
				clr_scr(0, 18, 35, 19);//清空输入框
				gotoxy(0, 18);
				printf("货物编号:");
				FreeBuff();
			}
			else {
				clr_scr(0, 16, 35, 17);//清除错误提示
				gotoxy(0, 19);//光标移动到下一行
				pTemp->goods_number = temp_Number;
				break;
			}
		}
		FreeBuff();
		//TODO  结束信息录入


		printf("货物名称:");
		scanf("%s", &temp_String);
		strcpy(pTemp->name, temp_String);//NOTE 对字符型数组，赋值问题
		FreeBuff();


		printf("生产厂家:");
		scanf("%s", &temp_String);
		strcpy(pTemp->producer,temp_String);
		FreeBuff();

		printf("类别:");
		scanf("%s", &temp_String);
		strcpy(pTemp->type, temp_String);
		FreeBuff();

		//TODO  清空缓冲区

		printf("售价:");
		while (1) {
			scanf("%d", &temp_Number);
			if (temp_Number < 0) {
				gotoxy(0, 16);
				printf("输入错误，请重新输入...");
				clr_scr(0, 22, 35, 23);//清空输入框
				gotoxy(0, 22);
				printf("售价:");
				FreeBuff();
			}
			else {
				clr_scr(0, 16, 35, 17);//清除错误提示
				gotoxy(0, 23);//光标移动到下一行
				pTemp->price = temp_Number;
				break;
			}
		}
		FreeBuff();

		printf("库存量:");
		while (1) {
			scanf("%d", &temp_Number);
			if (temp_Number < 0) {
				gotoxy(0, 16);
				printf("输入错误，请重新输入...");
				clr_scr(0, 23, 35, 24);//清空输入框
				gotoxy(0, 23);
				printf("库存量:");
				FreeBuff();
			}
			else {
				clr_scr(0, 16, 35, 17);//清除错误提示
				gotoxy(0, 24);//光标移动到下一行
				pTemp->totality = temp_Number;
				break;
			}
		}
		FreeBuff();

		//清除指令框
		clr_scr(0, 18, 35, 30);
		//清除提示框
		clr_scr(0, 16, 35, 17);
		//录入反馈
		gotoxy(0, 14);
		printf("已经成功录入一件货物信息...\n1.结束录入\n2.继续录入\n");
		gotoxy(0, 18);
		printf("指令:");
		scanf("%d", &intput_flag);
		FreeBuff();

		//清除指令框
		clr_scr(0, 18, 35, 30);
		//清除提示框
		clr_scr(0, 14, 35, 17);
		gotoxy(0, 18);

		if (intput_flag == 1) {
			break;
		}

		pRear = pTemp;//尾部指针移动
	}
}
void Showall_GoodsList(struct goods* header) {
	menu_Showall_GoodsList();
	if (header == NULL) {
		return;
	}

	struct goods* pTemp = header->next;//临时指针
	int y = 4;
	while (pTemp != NULL) {
		gotoxy(9, y);
		printf("%d", pTemp->goods_number);//货物编号
		gotoxy(18, y);
		printf("%s", &pTemp->name);//货物名称
		gotoxy(27, y);
		printf("%s", &pTemp->producer);//生产厂家
		gotoxy(42, y);
		printf("%s", &pTemp->type);//类别
		gotoxy(52, y);
		printf("%d", pTemp->price);//售价
		gotoxy(65, y);
		printf("%d", pTemp->totality);//库存量
		printf("\n");
		y++;//光标移动
		pTemp = pTemp->next;//临时指针移动
	}
	//操作反馈
	gotoxy(0, 15);
	printf("按任意键返回菜单...\n已经成功显示所有货物信息...\n");
	gotoxy(0, 18);
	printf("指令:");
	getchar();
	FreeBuff();


}
void Del_GoodsList(struct goods* header) {

	if (header == NULL) {
		return;
	}
	//两个辅助指针
	struct goods* pCrr = header->next;
	struct goods* pBhd = header;
	//查找的编号
	char temp_String[30];
	gotoxy(0, 19);
	printf("需删除的货物的名称:");
	scanf("%s", &temp_String);
	FreeBuff();
	while (pCrr != NULL) {
		if (strstr(pCrr->name, temp_String) != NULL) { // 将strcmp改为strstr，用于模糊匹配
			pBhd->next = pCrr->next;//重新建立前驱和后继结点的关系
			free(pCrr);//释放结点的内存
			clr_scr(0, 19, 35, 30);
			gotoxy(0, 16);
			printf("成功删除,按下任意键退出...\n");
			gotoxy(0, 29);
			printf("指令:");
			getchar();
			FreeBuff();
			return;
		}
		//指针移动
		pBhd = pCrr;
		pCrr = pCrr->next;
	}
	//清除指令框
	clr_scr(0, 19, 35, 30);
	gotoxy(0, 16);
	printf("未找到该商品,按下任意键退出...\n");
	gotoxy(0, 19);
	printf("指令:");
	getchar();
	FreeBuff();
	return;
}
void sell_goods(struct goods* header) {
	menu_sell_goods();
	if (header == NULL) {
		return;
	}
	struct goods* pTemp = header->next;//临时指针
	int y = 4;
	while (pTemp != NULL) {
		gotoxy(9, y);
		printf("%d", pTemp->goods_number);//货物编号
		gotoxy(18, y);
		printf("%s", &pTemp->name);//货物名称
		gotoxy(27, y);
		printf("%s", &pTemp->producer);//生产厂家
		gotoxy(42, y);
		printf("%s", &pTemp->type);//类别
		gotoxy(52, y);
		printf("%d", pTemp->price);//售价
		gotoxy(65, y);
		printf("%d", pTemp->totality);//库存量
		printf("\n");
		y++;//光标移动
		pTemp = pTemp->next;//临时指针移动
	}
	char input_type[30], input_name[30];
	int input_quantity;
	struct goods* ptr = header->next;

	// 输入类别和商品名称
	gotoxy(0, 18);
	printf("请输入商品类别：");
	scanf("%s", &input_type);
	FreeBuff();
	//清除指令框
	clr_scr(0, 18, 35, 30);

	gotoxy(0, 18);
	printf("请输入商品名称：");
	scanf("%s", &input_name);
	FreeBuff();
	//清除指令框
	clr_scr(0, 18, 35, 30);

	// 查找该商品是否存在
	while (ptr != NULL) {
		if (strcmp(ptr->type, input_type) == 0 && strcmp(ptr->name, input_name) == 0)
			break;
		ptr = ptr->next;
	}

	// 商品不存在
	if (ptr == NULL) {
		//清除提示框
		clr_scr(0, 15, 35, 17);
		gotoxy(0, 15);
		printf("该商品不存在\n");
		gotoxy(0, 18);
		printf("指令:");
		getchar();
		return;
	}

	// 判断库存量是否足够
	if (ptr->totality == 0) {
		//清除提示框
		clr_scr(0, 15, 35, 17);
		gotoxy(0, 15);
		printf("商品已售罄\n");
		gotoxy(0, 18);
		printf("指令:");
		getchar();
		return;
	}

	// 输入购买数量
	gotoxy(0, 18);
	printf("请输入购买数量：");
	scanf("%d", &input_quantity);
	//清除指令框
	FreeBuff();
	clr_scr(0, 18, 35, 30);

	// 库存量不足
	if (input_quantity > ptr->totality) {
		//清除提示框
		clr_scr(0, 15, 35, 17);
		gotoxy(0, 15);
		printf("库存量不足\n");
		gotoxy(0, 18);
		printf("指令:");
		getchar();
		return;
	}

	// 计算并更新库存量
	int total_price = input_quantity * ptr->price;
	ptr->totality -= input_quantity;


	//操作反馈
	gotoxy(0, 15);
	printf("购买成功");
	gotoxy(0, 18);
	printf("指令:");
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
	int temp_Number = -1;//装数据
	char temp_String[30];//装数据
	char* project_list[] = { "编号","货物名称","生产厂家", "类别", "售价", "库存量" };//NOTE 数组储存多个字符串

	gotoxy(0, 18);
	printf("货物编号:");
	scanf("%d", &GoodsNumber);
	FreeBuff();
	//清除指令框
	clr_scr(0, 18, 35, 30);
	//辅助指针
	struct goods* pCrr = header->next;
	//查找
	while (pCrr != NULL) {
		if (pCrr->goods_number == GoodsNumber) {
			break;
		}
		//指针移动
		pCrr = pCrr->next;
	}
	if (pCrr == NULL) {
		//清除指令框
		clr_scr(0, 18, 35, 30);
		gotoxy(0, 16);
		printf("未找到该商品,按下任意键退出...\n");
		gotoxy(0, 18);
		printf("指令:");
		getchar();
		FreeBuff();
		return;
	}
	//展示
	gotoxy(9, 4);
	printf("%d", pCrr->goods_number);//货物编号
	gotoxy(18, 4);
	printf("%s", &pCrr->name);//货物名称
	gotoxy(30, 4);
	printf("%s", &pCrr->producer);//生产厂家
	gotoxy(42, 4);
	printf("%s", &pCrr->type);//类别
	gotoxy(52, 4);
	printf("%d", pCrr->price);//售价
	gotoxy(65, 4);
	printf("%d", pCrr->totality);//库存量

	gotoxy(0, 5);
	//修改
	while (1) {
		gotoxy(0, 18);
		printf("请输入修改指令:");
		scanf("%d", &ModifyProject_int);
		FreeBuff();
		//修改信息
		switch (ModifyProject_int)
		{
		case 1:
			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("当前修改的项目是\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("请输入修改后的\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%d", &temp_Number);
			FreeBuff();
			pCrr->goods_number = temp_Number;
			break;
		case 2:
			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("当前修改的项目是\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("请输入修改后的\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%s", &temp_String);
			FreeBuff();
			strcpy(pCrr->name, temp_String);//NOTE 字符串赋值
			break;
		case 3:
			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("当前修改的项目是\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("请输入修改后的\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%s", &temp_String);
			FreeBuff();
			strcpy(pCrr->producer,temp_String);//NOTE 字符串赋值
			break;
		case 4:
			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("当前修改的项目是\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("请输入修改后的\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%s", &temp_String);
			FreeBuff();
			strcpy(pCrr->producer,temp_String);//NOTE 字符串赋值
			break;
		case 5:
			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("当前修改的项目是\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("请输入修改后的\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%d", &temp_Number);
			FreeBuff();
			pCrr->price = temp_Number;
			break;
		case 6:
			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("当前修改的项目是\"%s\"\n", project_list[ModifyProject_int - 1]);
			gotoxy(0, 18);
			printf("请输入修改后的\"%s\":", project_list[ModifyProject_int - 1]);
			scanf("%d", &temp_Number);
			FreeBuff();
			pCrr->totality = temp_Number;
			break;
		case 7:
			return;
		default:
			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
			gotoxy(0, 16);
			printf("输入错误，请重新输入...\n");
			break;
		}

		if (ModifyProject_int < 7 && ModifyProject_int>0) {
			//展示
			clr_scr(0, 4, 50, 5);
			gotoxy(9, 4);
			printf("%d", pCrr->goods_number);//货物编号
			gotoxy(18, 4);
			printf("%s", &pCrr->name);//货物名称
			gotoxy(30, 4);
			printf("%s", &pCrr->producer);//生产厂家
			gotoxy(42, 4);
			printf("%s", pCrr->type);//类别
			gotoxy(52, 4);
			printf("%d", pCrr->price);//售价
			gotoxy(65, 4);
			printf("%d", pCrr->totality);//库存量
			gotoxy(0, 5);

			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
			//操作反馈
			gotoxy(0, 14);
			printf("1.结束修改\n2.继续修改\n");
			gotoxy(0, 16);
			printf("修改成功...\n");
			gotoxy(0, 18);
			printf("指令:");
			scanf("%d", &intput_flag);
			FreeBuff();
			if (intput_flag == 1)
			{	//清除指令框
				clr_scr(0, 18, 35, 30);
				//清除提示框
				clr_scr(0, 14, 35, 17);
				return;
			}
			//清除指令框
			clr_scr(0, 18, 35, 30);
			//清除提示框
			clr_scr(0, 16, 35, 17);
		}
	}

}
void Sort_GoodsList(struct goods* header) {
	menu_Sort_GoodsList();
	if (header == NULL) {
		return;
	}

	//辅助指针
	struct goods* pCrr = header->next;
	struct goods* pBhd = header;
	struct goods* pMiddle = header;
	int PCrr_num = -1;
	int PMiddle_num = -1;
	//计算货物数量
	int count = 0;
	while (pCrr != NULL) {
		count++;
		//指针移动
		pCrr = pCrr->next;
	}

	//排序
	char* project_list[] = { "编号", "售价", "库存量","生产厂家" };
	int sort_project = -1;
	pCrr = header->next;//初始值
	gotoxy(0, 18);
	printf("请输入排序的依据:");
	scanf("%d", &sort_project);
	FreeBuff();

	switch (sort_project) {
	case 1:
		for (int i = 0; i < count; i++) {
			//>>指针初始化
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
			//>>指针初始化
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
			//>>指针初始化
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
			// 指针初始化
			pMiddle = header->next;
			pCrr = pMiddle->next;
			pBhd = header;
			for (int j = 0; j < count - i - 1; j++) { // 更改循环终止条件
				if (pCrr == NULL) {
					break;
				}
				// 生产厂家名称比较
				if (strlen(pCrr->producer) > strlen(pMiddle->producer)) {
					pMiddle->next = pCrr->next;
					pCrr->next = pMiddle;
					pBhd->next = pCrr;
				}
				pBhd = pBhd->next;
				pMiddle = pMiddle->next;
				pCrr = pCrr->next; // 更新指针位置
			}
		}
		break;
	case 5:
		return;
		break;
	default:
		gotoxy(0, 16);
		printf("输入错误...");
		break;
	}
	if (sort_project < 6 && sort_project>0)
	{	//清除指令框
		clr_scr(0, 18, 35, 30);
		//清除提示框
		clr_scr(0, 16, 35, 17);
		//操作反馈
		gotoxy(0, 15);
		printf("按任意键返回菜单...\n已经成功排序所有货物信息...\n");
		gotoxy(0, 18);
		printf("指令:");
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
	struct goods* pTemp = header->next;//临时指针

	gotoxy(0, 18);
	printf("请输入查找的货物名称：");
	scanf("%s", &temp_String);
	FreeBuff();
	while (pTemp != NULL) {
		if (strstr(pTemp->name, temp_String) != NULL) {
			break;
		}
		pTemp = pTemp->next;//临时指针移动
	}

	while (pTemp != NULL) {
		if (strstr(pTemp->name, temp_String) != NULL) {
			break;
		}
		pTemp = pTemp->next;//临时指针移动
	}

	if (pTemp == NULL) {
		//清除指令框
		clr_scr(0, 18, 35, 30);
		gotoxy(0, 16);
		printf("未找到该商品,按下任意键退出...\n");
		gotoxy(0, 18);
		printf("指令:");
		getchar();
		FreeBuff();
		return;
	}
	gotoxy(9, 5);
	printf("%d", pTemp->goods_number);//货物编号
	gotoxy(18, 5);
	printf("%s", &pTemp->name);//货物名称
	gotoxy(30, 5);
	printf("%s", &pTemp->producer);//生产厂家
	gotoxy(42, 5);
	printf("%s", pTemp->type);//类别
	gotoxy(52, 5);
	printf("%d", pTemp->price);//售价
	gotoxy(65, 5);
	printf("%d", pTemp->totality);//库存量
	printf("\n");

	//清除指令框
	clr_scr(0, 18, 35, 30);
	//清除提示框
	clr_scr(0, 16, 35, 17);
	gotoxy(0, 16);
	printf("查找成功,按下任意键退出...\n");
	gotoxy(0, 18);
	printf("指令:");
	getchar();
	FreeBuff();

}
void Save_GoodsList(struct goods* header, char* filename) {
	if (header == NULL) {
		return;
	}
	struct goods* pCrr = header->next;
	FILE* pList;//文件指针
	if ((pList = fopen(filename, "w")) == NULL) {
		gotoxy(0, 16);
		printf("无法打开货物文件\n");
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
	fclose(pList);//ＷＨＹ　fopen和fclose一起用，但fopen_s不可以和fclose一起用
	//清除指令框
	clr_scr(0, 18, 35, 30);
	gotoxy(0, 16);
	printf("保存成功,按下任意键退出...\n");
	gotoxy(0, 18);
	printf("指令:");
	getchar();
	FreeBuff();
	return;

}
void  OutputFile(struct goods* header, char* filename) {
	//辅助指针
	struct goods* pCrr;
	pCrr = header;
	int goods_number;//编号,用于判断是否还存在信息
	char str[30] = "\0";//信息存放
	FILE* fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("文件未找到");
		exit(0);
		return;
	}
	while (fscanf(fp, "%d", &goods_number) != EOF) {
		struct goods* pTemp = malloc(sizeof(struct goods));
		pTemp->next = NULL;//最后一个节点指向空
		pCrr->next = pTemp;//连接前一个节点
		//取值
		pTemp->goods_number = goods_number;//while循环的判断条件里已经取值了
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
	//清空输入缓存区
	scanf("%*[^\n]");
	scanf("%*c");
}
// UI
void menu(void) {
	gotoxy(36., 1);
	printf("超市货物管理系统\n");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(42, 4);
	printf("主菜单");
	gotoxy(28, 5);
	printf("=================================");
	gotoxy(28, 6);
	printf("1.创建货物信息     2.删除货物信息\n");
	gotoxy(28, 7);
	printf("3.查找货物信息     4.修改货物信息\n");
	gotoxy(28, 8);
	printf("5.展示所有信息     6.货物信息排序\n");
	gotoxy(28, 9);
	printf("7.销售             8.保存货物信息\n");
	gotoxy(28, 10);
	printf("9.退出\n");
	gotoxy(28, 11);
	printf("=================================");
	gotoxy(0, 18);
	printf("=========================================================================================");
}
void menu_Inti_GoodsList(void) {
	gotoxy(36, 1);
	printf("货物信息添加模块");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(36, 4);
	printf("需填写以下信息");
	gotoxy(34, 5);
	printf("===================");
	gotoxy(34, 6);
	printf("1.编号     2.名称\n");
	gotoxy(34, 7);
	printf("3.生产厂家   4.类别\n");
	gotoxy(34, 8);
	printf("5.出售价   6.库存量\n");
	gotoxy(34, 9);
	printf("===================");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void menu_Showall_GoodsList(void) {
	gotoxy(36, 1);
	printf("货物信息展示模块");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(7, 3);
	printf("编  号     名  称     生产厂家     类别     售  价     库存量\n");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void menu_sell_goods(void) {
	gotoxy(40, 1);
	printf("商品列表");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(7, 3);
	printf("编  号     名  称     生产厂家     类别     售  价     库存量\n");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void menu_Modify_GoodsList(void) {
	//展示信息
	gotoxy(36, 1);
	printf("货物信息修改模块");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(7, 3);
	printf("编  号     名  称     生产厂家     类别     售  价     库存量\n");
	gotoxy(0, 5);
	printf("=========================================================================================");
	printf("\n");

	//选择修改的项目
	gotoxy(40, 7);
	printf("业务");
	gotoxy(28, 8);
	printf("============================");
	gotoxy(28, 9);
	printf("1.修改编号     2.修改名称\n");
	gotoxy(28, 10);
	printf("3.修改生产厂家   4.修改类别\n");
	gotoxy(28, 11);
	printf("5.修改出售价   6.修改库存量\n");
	gotoxy(28, 12);
	printf("7.退出\n");
	gotoxy(28, 13);
	printf("============================");
	gotoxy(0, 17);
	printf("=========================================================================================");


}
void menu_Shelt(void) {
	gotoxy(0, 1);
	printf("=========================================================================================");
	gotoxy(40, 4);
	printf("货物分区\n");
	gotoxy(33, 5);
	printf("=====================");
	gotoxy(33, 6);
	printf("1.在售区     2.下架区\n");
	gotoxy(33, 7);
	printf("3.进货区     4.退出\n");
	gotoxy(33, 8);
	printf("=====================");
	gotoxy(0, 17);
	printf("=========================================================================================");

}
void menu_Sort_GoodsList(void) {
	//选择排序依据
	gotoxy(36, 1);
	printf("货物信息排序模块");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(43, 4);
	printf("项目");
	gotoxy(36, 5);
	printf("===================");
	gotoxy(36, 6);
	printf("1.编号      2.售价\n");
	gotoxy(36, 7);
	printf("3.库存量   4.生产厂家\n");
	gotoxy(36, 8);
	printf("5.退出\n");
	gotoxy(36, 9);
	printf("===================");
	gotoxy(0, 17);
	printf("=========================================================================================");
}
void menu_ShowOne_GoodsList(void) {
	gotoxy(37, 1);
	printf("货物信息查找模块");
	gotoxy(0, 2);
	printf("=========================================================================================");
	gotoxy(7, 4);
	printf("编  号     名  称     生产厂家     类别     售  价     库存量\n");
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
