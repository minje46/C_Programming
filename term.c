#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Smartphone {
	char Model[30], Vender[20];
	float Display_size;
	char Screen_resolution[10], OS[12], CPU_type[35];
	int CPU_clock;
	float memory_size;
	int price;
	struct Smartphone *next;
	int flag;  // flag 를 0으로 초기화 하여 search 에서 중복 search 를 가능하게함
};

void open(struct Smartphone **);
void Print(struct Smartphone *, int);
void Insert(struct Smartphone *);
void Delete(struct Smartphone *);
void Sort(struct Smartphone *);
void S_sort(struct Smartphone *, int);
void N_sort(struct Smartphone *, int);
void Search(struct Smartphone *);
void Part_search_s(struct Smartphone *, int, char *);
void Part_search_n(struct Smartphone *, int, float);
void Save(struct Smartphone *);



void main(){

	FILE *h;
	struct Smartphone *head = NULL, *new_n = NULL, *prev = NULL;
	int x;
	int k = 1;
	char v1[200], v2[200];

	while (1)
	{
		printf("\n +---------------------------+");
		printf("\n | Select Number of function |");
		printf("\n +---------------------------+");
		printf("\n | 1. File Open              |");
		printf("\n | 2. Print                  |");
		printf("\n | 3. Insert                 |");
		printf("\n | 4. Delete                 |");
		printf("\n | 5. Sort                   |");
		printf("\n | 6. Search                 |");
		printf("\n | 7. Save                   |");
		printf("\n +---------------------------+");
		printf("\n | 0. Exit                   |");
		printf("\n +---------------------------+");
		printf("\n ☞  ");
		scanf("%d", &x);

		switch (x)  // switch 문으로 함수 선택
		{
		case 1: open(&head); k = 0; break;
		case 2:if (k)printf("\n 파일이 없습니다! 파일을 먼저 열어주세요.\n"); else Print(head, 0); break;
		case 3:if (k)printf("\n 파일이 없습니다! 파일을 먼저 열어주세요.\n"); else Insert(head); break;
		case 4:if (k)printf("\n 파일이 없습니다! 파일을 먼저 열어주세요.\n"); else Delete(head); break;
		case 5:if (k)printf("\n 파일이 없습니다! 파일을 먼저 열어주세요.\n"); else Sort(head); break;
		case 6:if (k)printf("\n 파일이 없습니다! 파일을 먼저 열어주세요.\n"); else Search(head); break;
		case 7:if (k)printf("\n 파일이 없습니다! 파일을 먼저 열어주세요.\n"); else Save(head); break;
		case 0:exit(1);
		}
	}
}

void open(struct Smartphone ** head){
	struct Smartphone *hd, *new_n = NULL, *prev = NULL;
	int i;
	char v1[200], v2[200];
	FILE *h;

	printf("\n 파일을 선택해 주세요 \n 1. 원본 파일  2. 새 파일 \n ☞ ");
	scanf("%d", &i);

	if (i == 1) {
		if ((h = fopen("term_project4.txt", "r")) == NULL) {
			printf("File Could Not Be Opened.\n");
			exit(1);
		}
	}

	else if (i == 2) {
		if ((h = fopen("saved_New_data.txt", "r")) == NULL) {
			printf("File Could Not Be Opened.\n");
			exit(1);
		}
	}

	if (h) {
		hd = (struct Smartphone *)malloc(sizeof(struct Smartphone));  // 말뚝 head 노드를 하나 만들어줌
		*head = hd;  // main 함수로 말뚝 head 값을 돌려줌
		new_n = (struct Smartphone *)malloc(sizeof(struct Smartphone));  // 새 노드를 하나 만들어 처음 while 문으로 넘겨줌
		new_n->flag = 0;

		fgets(v1, sizeof(v1), h);
		fgets(v2, sizeof(v2), h);  // 처음 두줄 스킵함

		while (fscanf(h, "| %s | %s | %f | %s | %s | %s | %d | %f | %d | ", new_n->Model, new_n->Vender, &new_n->Display_size, new_n->Screen_resolution, new_n->OS, new_n->CPU_type, &new_n->CPU_clock, &new_n->memory_size, &new_n->price) != EOF)
		{
			if (prev) {  // prev가 null 이 아닐시 prev 노드와 새로운 노드를 링크드 시켜줌 
				prev->next = new_n;
				new_n->next = NULL;
			}

			else {  // prev가 null 일 경우 말뚝 head 와 새로운 노드를 링크드 시켜줌
				hd->next = new_n;
				new_n->next = NULL;
			}

			prev = new_n;  // prev 를 새로 만들어 주는 노드로 지정해줌
			new_n = (struct Smartphone *)malloc(sizeof(struct Smartphone));
			new_n->flag = 0;
		}
	}fclose(h);

}

void Search(struct Smartphone *head)
{
	int x, i = 0;
	int bool_v = 1;
	char sc_c[30];
	int sc_i = 0;
	float sc_f = 0;
	struct Smartphone *p = head->next;

	while (bool_v != 0)
	{
		printf("\n +--------------------------------------------------+");
		printf("\n | Which type of information do you want to search ?|");
		printf("\n +--------------------------------------------------+");
		printf("\n | 1. Model                                         |");
		printf("\n | 2. Vendor                                        |");
		printf("\n | 3. Display size                                  |");
		printf("\n | 4. Screen revolution                             |");
		printf("\n | 5. O/S                                           |");
		printf("\n | 6. CPU type                                      |");
		printf("\n | 7. CPU clock                                     |");
		printf("\n | 8. Memory size                                   |");
		printf("\n | 9. Price                                         |");
		printf("\n +--------------------------------------------------+");
		printf("\n | 0. Exit                                          |");
		printf("\n +--------------------------------------------------+");
		printf("\n ☞  ");
		scanf("%d", &x);

		i++;  // i 는 중복 검색에 있어 구조체 flag와 비교하여 프린트 함수에서 같을시 프린트 해줌

		switch (x)  // search 함수에서 9가지의 검색 목록중 선택하여 partial search 함수로 가게함
		{
		case 1:	printf(" Enter the wanted Model : ");
			scanf("%s", sc_c);
			Part_search_s(head, x, sc_c);
			Print(head, i);
			break;

		case 2:	printf(" Enter the wanted Vendor : ");
			scanf("%s", sc_c);
			Part_search_s(head, x, sc_c);
			Print(head, i);
			break;

		case 3:	printf(" Enter the wanted Display Size : ");
			scanf("%f", &sc_f);
			Part_search_n(head, x, sc_f);
			Print(head, i);
			break;

		case 4:	printf(" Enter the wanted Screen Resolution : ");
			scanf("%s", sc_c);
			Part_search_s(head, x, sc_c);
			Print(head, i);
			break;

		case 5:	printf(" Enter the wanted OS : ");
			scanf("%s", sc_c);
			Part_search_s(head, x, sc_c);
			Print(head, i);
			break;

		case 6:	printf(" Enter the wanted CPU type : ");
			scanf("%s", sc_c);
			Part_search_s(head, x, sc_c);
			Print(head, i);
			break;

		case 7:	printf(" Enter the wanted CPU clock : ");
			scanf("%d", &sc_i);
			sc_i = (float)sc_i;  // int 형식과 float 형식 두개로 넘겨야 하지만 (float)으로 강제 변환후 partial search 로 넘김
			Part_search_n(head, x, sc_i);
			Print(head, i);
			break;

		case 8:	printf(" Enter the wanted Memory size : ");
			scanf("%f", &sc_f);
			Part_search_n(head, x, sc_f);
			Print(head, i);
			break;

		case 9:
			printf(" Enter the wanted Price : ");
			scanf("%d", &sc_i);
			sc_i = (float)sc_i;
			Part_search_n(head, x, sc_i);
			Print(head, i);
			break;

		case 0: bool_v = 0; break;

		default:printf("\n 『Tyed code is error !』\n"); break;
		}
	}

	while (p) {  // 만약 검색 혹은 중복 검색을 하였을시, 추가된 구조체 flag 들을 0으로 다시 초기화 시켜줌
		p->flag = 0;
		p = p->next;
	}
}

void Print(struct Smartphone *head, int n)
{
	int x, y = 0, z = 0;
	struct Smartphone *p = head->next;

	printf("\n 1. 간단히 보기   2. 자세히 보기\n ☞ ");  // 검색 결과를 간단히 보기와 자세히 보기로 나누어 시각적 표현을 가능케함
	scanf("%d", &x);

	//  프린트 함수 호출시 넘겨받은 int parameter 값과 flag 값이 같을경우 프린트 해줌
	if (x == 1){
		printf("\n ##Searched data## \n\n");
		while (p)
		{
			if (p->flag == n) //  중복검색을 할시 flag 가 한개씩 올라가서 마지막 검색까지의 flag 값을 저장  
			{
				printf(" %-14s %-11s %-0.1f  %-9s  %-11s %-18s %-4d  %-5.2f  %-3d  \n\n", p->Model, p->Vender, p->Display_size, p->Screen_resolution, p->OS, p->CPU_type, p->CPU_clock, p->memory_size, p->price);
				z = 1;   //  검색한 결과가 있을경우 z 값을 1로 만들어주어 검색결과 없음 print 함수를 건너 뛰게 함
			}p = p->next;
		}
	}

	if (x == 2){
		printf("\n ##Searched data## \n\n");
		while (p)
		{
			if (p->flag == n){
				printf(" +---------------------++-------------------------+\n");
				printf(" | Model               =>    %20s |\n", p->Model);
				printf(" | Vender              =>    %20s |\n", p->Vender);
				printf(" | Display size        =>    %20.1f |\n", p->Display_size);
				printf(" | Screen revolution   =>    %20s |\n", p->Screen_resolution);
				printf(" | O/S                 =>    %20s |\n", p->OS);
				printf(" | CPU type            =>    %20s |\n", p->CPU_type);
				printf(" | CPU clock           =>    %20d |\n", p->CPU_clock);
				printf(" | Memory size         =>    %20.1f |\n", p->memory_size);
				printf(" | Price               =>    %20d |\n", p->price);
				printf(" +---------------------++-------------------------+\n");
				z = 1;
			}
			p = p->next;
		}
	}
	if ((x != 1) && (x != 2))
		printf(" Invalid code !");
	if (z == 0)
		printf(" ##데이터를 찾을수 없습니다.##\n"), n = 0;
}

void Part_search_s(struct Smartphone * head, int n, char *key)
{
	int i, j, k = 0;
	struct Smartphone *p = head->next;
	char *temp = NULL, *sc;

	while (p)
	{
		switch (n)  // n 값에 따라 검색할 정보를 sc 에 저장
		{
		case 1: sc = p->Model; break;
		case 2: sc = p->Vender;	break;
		case 4: sc = p->Screen_resolution; break;
		case 5: sc = p->OS;	break;
		case 6: sc = p->CPU_type; break;
		}

		k = 0;

		for (i = 0; i < strlen(sc); i++)
		{
			if ((sc[i] == key[0]) && (k == 0))
			{
				for (j = 0; j < strlen(key); j++)
					if (sc[i + j] != key[j])
						break;

				if (j == strlen(key))
					k = 1, (p->flag)++;  //  검색결과로 나온 구조체에 flag 를 하나 올려주어 검색하여 결과로 나온 값이라 저장함
			}
		}
		p = p->next;
	}
}

void Part_search_n(struct Smartphone * head, int choice, float num)
{
	int x;
	float k1, add, tmp;
	struct Smartphone *p = head->next;
	char *sc_1, *sc_2;

	switch (choice)  //  case에 따라 텍스트에 변화를 주어 시각적 효과를 높임
	{
	case 3: sc_1 = "Display size", sc_2 = "inch";  break;
	case 7: sc_1 = "Cpu Clock", sc_2 = "MHz";  break;
	case 8: sc_1 = "Memory size", sc_2 = "Gbyte";  break;
	case 9: sc_1 = "가격", sc_2 = "$";  break;
	default: break;
	}

	printf("\n 1. %s 범위로 찾기  2. %0.2f(%s) 이상 찾기  3. %0.2f(%s) 이하 찾기 \n ☞  ", sc_1, num, sc_2, num, sc_2);
	scanf("%d", &x);

	if (x == 1) {  // 추가 범위를 입력하여 그 범위 안의 값들을 가진 데이터를 찾아줌
		printf("\n 추가 %s(을)를 입력하세요 \n ☞  ", sc_1);
		scanf("%f", &add);

		while (1)
		{
			if (num == add) {  //  만약 추가 입력 범위가 원래의 입력값과 같을 경우 다시 다른 값을 받게함
				printf(" \n 값이 잘못 됐습니다. 다시 입력해 주세요. \n");
				printf("\n 추가 %s(을)를 입력하세요 \n ☞  ", sc_1);
				scanf("%f", &add);
			}
			else break;
		}

		while (p)
		{
			switch (choice)
			{
			case 3: sc_2 = "inch"; k1 = p->Display_size; break;
			case 7: sc_2 = "MHz"; k1 = p->CPU_clock; break;
			case 8: sc_2 = "Gbyte"; k1 = p->memory_size; break;
			case 9: sc_2 = "$"; k1 = p->price; break;
			default: break;
			}

			if (num > add) {  //  추가 범위가 처음 입력값보다 크거나 작을 경우가 있으므로 한 경우로 만들어 주기 위해 바꿔줌
				tmp = num;
				num = add;
				add = tmp;
			}

			if ((k1 >= num) && (k1 <= add))
				(p->flag)++;

			p = p->next;
		}
		printf(" \n (%0.2f ~ %0.2f)%s ", num, add, sc_2);
	}

	if (x == 2) {  //  입력값 이상 범위 값을 찾게함

		while (p)
		{
			switch (choice)
			{
			case 3: sc_2 = "inch"; k1 = p->Display_size; break;
			case 7: sc_2 = "MHz"; k1 = p->CPU_clock; break;
			case 8: sc_2 = "Gbyte"; k1 = p->memory_size; break;
			case 9: sc_2 = "$"; k1 = p->price; break;
			default: break;
			}

			if (k1 >= num)
				(p->flag)++;

			p = p->next;
		}
		printf(" \n (%0.2f)%s 이상 ", num, sc_2);
	}

	if (x == 3) {  //  입력값 이하 범위 값을 찾게함

		while (p)
		{
			switch (choice)
			{
			case 3: sc_2 = "inch"; k1 = p->Display_size; break;
			case 7: sc_2 = "MHz"; k1 = p->CPU_clock; break;
			case 8: sc_2 = "Gbyte"; k1 = p->memory_size; break;
			case 9: sc_2 = "$"; k1 = p->price; break;
			default: break;
			}

			if (k1 <= num)
				(p->flag)++;

			p = p->next;
		}
		printf(" \n (%0.2f)%s 이하 ", num, sc_2);
	}
}

void Insert(struct Smartphone *head)
{
	struct Smartphone *p = head->next, *tmp;

	while (p)
	{
		tmp = p;
		p = p->next;
	}
	p = (struct Smartphone *)malloc(sizeof(struct Smartphone));

	printf("\n 새로 추가할 정보를 입력 하세요.\n Model ,Vendor ,Display_Size ,Screen_Resolution ,O/S ,CPU_Type ,CPU_Clock ,Memory_Size ,Price\n ☞ ");
	scanf(" %s %s %f %s %s %s %d %f %d", p->Model, p->Vender, &p->Display_size, p->Screen_resolution, p->OS, p->CPU_type, &p->CPU_clock, &p->memory_size, &p->price);
	tmp->next = p;
	p->next = NULL;
	p->flag = 0;
}

void Delete(struct Smartphone * head)
{
	struct Smartphone *p = head->next, *prev;
	char model[30], c;
	int k = 1;

	printf("\n 스마트폰 목록 보러가기. Y / N \n ☞ ");
	scanf("%*c%c", &c);

	if (c == 'Y')
		Print(head, 0);

	while (k)
	{
		p = head->next;

		printf(" \n 지우실 모델 이름을 입력하세요. \n ☞ ");
		scanf("%s", model);

		while (p)
		{
			if (strcmp(p->Model, model) == 0)
				break;
			prev = p;
			p = p->next;
		}

		if (p)
		{
			k = 0;
			prev->next = p->next;
			free(p);
		}

		if (k == 1)
			printf("\n 모델명을 찾을 수 없습니다.\n");
		else
			printf("\n 모델 정보를 삭제 하였습니다.\n");
	}
}

void Sort(struct Smartphone *head)
{
	int x, bool_v = 1;

	while (bool_v != 0)
	{
		printf("\n +----------------------+");
		printf("\n | Select Sort type     |");
		printf("\n +----------------------+");
		printf("\n | 1. Model             |");
		printf("\n | 2. Vendor            |");
		printf("\n | 3. Display size      |");
		printf("\n | 4. Screen revolution |");
		printf("\n | 5. O/S               |");
		printf("\n | 6. CPU type          |");
		printf("\n | 7. CPU clock         |");
		printf("\n | 8. Memory size       |");
		printf("\n | 9. Price             |");
		printf("\n +----------------------+");
		printf("\n | 0. Exit              |");
		printf("\n +----------------------+");
		printf("\n ☞  ");
		scanf("%d", &x);

		switch (x)  //  partial sort 함수 호출
		{
		case 1:S_sort(head, x); break;
		case 2:S_sort(head, x); break;
		case 3:N_sort(head, x); break;
		case 4:S_sort(head, x); break;
		case 5:S_sort(head, x); break;
		case 6:S_sort(head, x); break;
		case 7:N_sort(head, x); break;
		case 8:N_sort(head, x); break;
		case 9:N_sort(head, x); break;
		case 0: bool_v = 0; break;
		default:printf("\n 『Tyed code is error !』\n"); break;
		}
	}
}

void N_sort(struct Smartphone *head, int n)			//Numerical Sort 함수
{
	struct Smartphone *g = head->next, *p = g->next;
	int x, p_tmp, c_tmp;
	float m_tmp, d_tmp;

	printf("\n 정렬 방식을 입력해 주세요.");
	printf("\n 1. Ascending sort  2. Descending sort \n ☞ ");
	scanf("%d", &x);

	switch (n)			//위의 sort함수에서 입력받은것을 switch문으로써 연결.
	{
	case 3:
		if(x==1)
		{
			while (g->next)
			{
				p = g->next;

				while (p) 
				{
					if (g->Display_size > p->Display_size)
					{
						d_tmp = p->Display_size;
						p->Display_size = g->Display_size;
						g->Display_size = d_tmp;
					}
					p = p->next;
				}
				printf("%f\n",g->Display_size);
				g = g->next;
			}
		}
		if(x==2)
		{
			while (g->next)
			{
				p = g->next;

				while (p) 
				{
					if (g->Display_size < p->Display_size)
					{
						d_tmp = p->Display_size;
						p->Display_size = g->Display_size;
						g->Display_size = d_tmp;
					}
					p = p->next;
				}
				printf("%f\n",g->Display_size);
				g = g->next;
			}
		}
		break;
	case 7:
		if(x==1)
		{
			while (g->next)
			{
				p = g->next;

				while (p) 
				{
					if (g->CPU_clock > p->CPU_clock)
					{
						c_tmp = p->CPU_clock;
						p->CPU_clock = g->CPU_clock;
						g->CPU_clock = c_tmp;
					}
					p = p->next;
				}
				printf("%d\n",g->CPU_clock);
				g = g->next;
			}
		}
		if(x==2)
		{
			while (g->next)
			{
				p = g->next;

				while (p) 
				{
					if (g->CPU_clock < p->CPU_clock)
					{
						c_tmp = p->CPU_clock;
						p->CPU_clock = g->CPU_clock;
						g->CPU_clock = c_tmp;
					}
					p = p->next;
				}
				printf("%d\n",g->CPU_clock);
				g = g->next;
			}
		}
		break;
	case 8:
		if(x==1)
		{
			while (g->next)
			{
				p = g->next;

				while (p) 
				{
					if (g->memory_size > p->memory_size)
					{
						m_tmp = p->memory_size;
						p->memory_size = g->memory_size;
						g->memory_size = m_tmp;
					}
					p = p->next;
				}
				printf("%f\n",g->memory_size);
				g = g->next;
			}
		}
		if(x==2)
		{
			while (g->next)
			{
				p = g->next;

				while (p) 
				{
					if (g->memory_size < p->memory_size)
					{
						m_tmp = p->memory_size;
						p->memory_size = g->memory_size;
						g->memory_size = m_tmp;
					}
					p = p->next;
				}
				printf("%f\n",g->memory_size);
				g = g->next;
			}
		}
		break;
	case 9:
		if(x==1)
		{
			while (g->next)
			{
				p = g->next;

				while (p) 
				{
					if (g->price > p->price)
					{
						p_tmp = p->price;
						p->price = g->price;
						g->price = p_tmp;
					}
					p = p->next;
				}
				printf("%d\n",g->price);
				g = g->next;
			}
		}
		if(x==2)
		{
			while (g->next)
			{
				p = g->next;

				while (p) 
				{
					if (g->price < p->price)
					{
						p_tmp = p->price;
						p->price = g->price;
						g->price = p_tmp;
					}
					p = p->next;
				}
				printf("%d\n",g->price);
				g = g->next;
			}
		}
		break;
	}



}

void S_sort(struct Smartphone *head, int n)					//Lexicographic Sort 함수
{
	struct Smartphone *g = head->next, *p = g->next;
	int i = 0, j = 1, k = 0;
	struct Smartphone *p_temp = NULL, *tp, *tg, *v, *temp;
	struct Smartphone *h = NULL, *tmp_h = NULL;
	char tem[30];
	int tmp, x, sort;
	char *sc_p, *sc_g;										//Nuemeric Sort 함수에서와는 다르게 sc_p와 sc_g 라는 변수를 이용하여 간단하게 코딩.

	printf("\n 정렬 방식을 입력해 주세요.");
	printf("\n 1. Ascending sort  2. Descending sort \n ☞ ");
	scanf("%d", &x);


	if (x == 1)
		sort = 1;
	else if (x == 2)
		sort = -1;

	while (g->next)
	{
		p = g->next;
		while (p){

			switch (n)		// sc_p와 sc_g 를 이용하여 각 각 model, vendor 등 설정을 안해주어도 됨.
			{
			case 1:sc_p = p->Model, sc_g = g->Model; break;
			case 2:sc_p = p->Vender, sc_g = g->Vender; break;
			case 4:sc_p = p->Screen_resolution, sc_g = g->Screen_resolution; break;
			case 5:sc_p = p->OS, sc_g = g->OS; break;
			case 6:sc_p = p->CPU_type, sc_g = g->CPU_type; break;
			}

			if (strcmp(strlwr(sc_g), strlwr(sc_p)) == sort)
			{
				strcpy(tem, sc_p);
				strcpy(sc_p, sc_g);
				strcpy(sc_g, tem);
			}
			p = p->next;
		}printf("%s\n",sc_g);
		g = g->next;
	}
}

void Save(struct Smartphone *head)
{
	FILE *save_txt;
	struct Smartphone *p = head->next;

	save_txt = fopen("saved_New_data.txt", "w");



	while (p)
	{
		fprintf(save_txt, "| %20s | %12s | %14.1f | %20s | %10s | %18s | %12d | %14.2f | %9d | \n", p->Model, p->Vender, p->Display_size, p->Screen_resolution, p->OS, p->CPU_type, p->CPU_clock, p->memory_size, p->price);
		p = p->next;
	}
	printf("\n Data was saved Successfuly! \n");
	fclose(save_txt);
}