#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct vector;

typedef struct {
	struct vector* vector;
	struct list* next;
	struct list* prev;
} list;

typedef struct {
	list vectors;
	struct vector* center;
} S;

typedef struct {
	S* S;
	float* vector;
	int size;
} vector;

vector* vector_init(float* vals, int N) {
      if (vals == NULL) {
      	return NULL;
      }
      vector* v = (vector*)malloc(sizeof(vector));
      assert(v != NULL);
      v->vector = (float*)malloc(sizeof(float)*N);
      assert (v->vector != NULL);
      memcpy(v->vector, vals, sizeof(float)*N);
      v->size = N;
      v->S = NULL;
      return v;
}

void vector_free(vector* v){
		assert(v != NULL);
		if (v->vector != NULL){
			free(v->vector);
		}
		free(v);
	}

vector* add(vector* v1, vector* v2) {
	assert (v1 != NULL && v2 != NULL);
	float vals[v1->size];
	for (int i=0; i<v1->size; i++) {
		vals[i] = v1->vector[i] + v2->vector[i];
	}
	vector* sum = vector_init(vals, v1->size);	
	return sum;
}

void divide(vector* v, float c) {
	assert (v != NULL);
	for (int i=0; i<v->size; i++) {
		v->vector[i] = v->vector[i]/c;
	}
}

void printVec(vector* v) {
	int i = 0;
	for (i; i<v->size -1; i++) {
		printf("%.4f, ", v->vector[i]);
	}
	printf("%.4f\n ", v->vector[i]);
}

int getN(char* filename) {

	FILE* fp;
	char buff[255];
	int N = 0;
	char* token;

	fp = fopen(filename, "r");

	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}
	
	fgets(buff, 255, fp);
	token = strtok(buff, ",");
	while (token != NULL) {
		N++;
		token = strtok(NULL, ",");
	}
	fclose(fp);
	return N;
}

list* read_vectors(char* filename){

	list* head = (list*)malloc(sizeof(list));
	assert(head != NULL);
	head->prev = NULL;
	list* now = head;
	list* tmp;
	FILE* fp;
	int N;
	char* token;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	float* vals;
	int i = 0;
	vector* v;

	N = getN(filename);

	fp = fopen(filename, "r");
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}

	vals = (float*)malloc(N*sizeof(float));
	assert(vals != NULL);

	while (read = getline(&line, &len, fp) != -1) {
		i=0;
		token = strtok(line, ",");
		while (token != NULL) {
			float num = atof(token);
			vals[i] = num;
			i++;
			token = strtok(NULL, ",");
		}
		v = vector_init(vals, N);
		now->vector = (struct vector*)v;
		tmp = now;
		now = (list*)malloc(sizeof(list));
		now->prev = (struct list*)tmp;
		tmp->next = (struct list*)now;
	}

	now = (list*)now->prev;
	free(now->next);
	now->next = NULL;
	free(vals);
	free(line);
	fclose(fp);
	return head;
}

int free_vectors(list* head){

	list* now = head;
	list* tmp;
	vector* vec;

	while(now->next != NULL){
		tmp = now;
		now = now->next;
		
		free(tmp);
	}
	vector_free(now->vector);
	free(now);
	return 0;
}

int main () {

	list* vectors;

	vectors = read_vectors("tests/input_1.txt");
	printVec(vectors->vector);
	return free_vectors(vectors);
} 