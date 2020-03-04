#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define GENE_LENGTH 500
#define GENE_LIVE_LENGTH 100
#define MAX_WEIGHT 9999
#define PLAYTIME 20
#define GENE_PRINT_LENGTH 20

extern int GameDataSize;

typedef struct _GameData {
	char gametype[100];			// e.g. �ַ�, �Ϲ�, ������ �ѷ��� ��
	std::pair<int, int> kill;	// è�Ǿ� óġ
	std::pair<int, int> gold;	// ��� ȹ�淮
	std::pair<int, int> deal;	// è�Ǿ𿡰� ���� ���ط�
	std::pair<int, int> ward;	// �͵� ��ġ
	std::pair<int, int> damage;	// ���� ���ط�
	std::pair<int, int> CS;		// CS
}GameData;

typedef struct _Gene {
	int w[6];	// weight
	int correct_count;
}Gene;

int random(int a, int b);
Gene* init_genes(Gene genes[]);
GameData* readGameData(FILE* f, GameData gamedata[]);
Gene* make_correct_count(Gene genes[], GameData gamedata[]);
int compareGene(const void* gene1, const void* gene2);
