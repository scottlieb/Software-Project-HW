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
      vector* v;

      if (vals == NULL) {
      	return NULL;
      }
      v = (vector*)malloc(sizeof(vector));
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

void add(vector* v1, vector* v2) {
	float* vals;
	int i;
	vector* sum;

	assert (v1 != NULL && v2 != NULL);

	vals = malloc((v1->size)*sizeof(float));

	for (i=0; i<v1->size; i++) {
		v1->vector[i] = v1->vector[i] + v2->vector[i];
	}
	free(vals);	
	return;
}

void divide(vector* v, float c) {
	int i;

	assert (v != NULL);
	for (i=0; i<v->size; i++) {
		v->vector[i] = v->vector[i]/c;
	}
}

void recenter(S* S){
	list* current;
	int n = 0;

	assert(S!=NULL);
	current = S->vectors;

	zero(S->center);
	if(current == NULL){
		return;
	}
	while(current!=NULL){
		n++;
		u = add(u,current->vector);
		current = current->next;
	}
	u = divide(u,n);
}

void printVec(vector* v) {
	int i;
	int vec_size;

	vec_size = v->size;
	for (i=0; i<vec_size-1; i++) {
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

	list* head;
	list* now;
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

	head = (list*)malloc(sizeof(list));
	assert(head != NULL);
	head->prev = NULL;

	now = head;
	N = getN(filename);

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("%s\n", "Not a valid filename!");
		exit(EXIT_FAILURE);
	}

	vals = (float*)malloc(N*sizeof(float));
	assert(vals != NULL);

	while ((read = getline(&line, &len, fp)) != -1) {
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

	while(now->next != NULL){
		tmp = now;
		now = (list*)now->next;
		
		free(tmp);
	}
	vector_free((vector*)now->vector);
	free(now);
	return 0;
}

int main () {

	/*
	char filename[100];
	*/
	list* vectors;
	list* current;

/*
	printf("%s\n", "Please enter filename:");
	scanf("%s", &filename);

*/
	vectors = read_vectors("tests/input_1.txt");
	current = vectors;

	while(current != NULL){
		printVec((vector*)current->vector);
		current = (list*)current->next;
	}

	return free_vectors(vectors);
} 