#include "myHeader.h"

int main() {
//	srand((int)time(NULL));
	srand(1000);
	FILE* f = fopen("GameData.txt", "r");
	
	GameData gamedata[500];

	Gene genes[GENE_LENGTH];
	Gene genes_last[GENE_LIVE_LENGTH];
	
	// GameData.txt -> gamedata[200]
	memcpy(gamedata, readGameData(f, gamedata), sizeof(GameData)*GameDataSize);

	// initializing
	memcpy(genes, init_genes(genes), sizeof(Gene)*GENE_LENGTH);
	
	double top_correct_rate, mean_correct_rate;
	for (int play = 0; play < PLAYTIME; play++) {
		// make correct_count
		memcpy(genes, make_correct_count(genes, gamedata), sizeof(Gene)*GENE_LENGTH);

		// sorting by Gene.correct_count
		qsort(genes, GENE_LENGTH, sizeof(Gene), compareGene);

		mean_correct_rate = 0;
		for (int i = 0; i < GENE_LENGTH; i++) {
			mean_correct_rate += genes[i].correct_count;
		}
		mean_correct_rate /= GameDataSize * GENE_LENGTH;
		top_correct_rate = (double)genes[0].correct_count / GameDataSize;

		// 선택
		memcpy(genes_last, genes, sizeof(genes_last));
		memset(genes, 0, sizeof(genes));

		// 교차
		for (int i = 0; i < GENE_LENGTH; i++) {
			for (int j = 0; j < 6; j++) {
				genes[i].w[j] = genes_last[random(0, GENE_LIVE_LENGTH - 1)].w[j];
			}
		}

		// 변이
		for (int i = 0; i < GENE_LENGTH; i++) {
			for (int j = 0; j < 6; j++) {
				if (random(0, 5) == 0) {	// rate: 0.20
					genes[i].w[j] = random(-MAX_WEIGHT, MAX_WEIGHT);
				}
			}
		}

		printf("\nPLAY: %d\n", play+1);
		printf(" top_correct_rate: %.4lf\n", top_correct_rate);
		printf("mean_correct_rate: %.4lf\n", mean_correct_rate);
		printf(" ** top %d genes **\n", GENE_PRINT_LENGTH);
		printf(" kill  gold  deal  ward damage   CS\n");
		for (int i = 0; i < GENE_PRINT_LENGTH; i++) {
			printf("%+5d %+5d %+5d %+5d %+5d %+5d", genes_last[i].w[0], genes_last[i].w[1], genes_last[i].w[2], genes_last[i].w[3], genes_last[i].w[4], genes_last[i].w[5]);
			printf("\t%.4lf\n", (double)genes_last[i].correct_count / GameDataSize);
		}

		puts("\n==============================================");
	}
	


	return 0;
}

