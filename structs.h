#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#define max_generations 2
#define persons_per_group 10
#define num_of_groups 1000
#define max_genes_per_person 10
#define rate_of_mutation 1
#define size_of_maturity_array 1024
#define neutRegionLength 1000
#define number_of_threads 10
#define neut_flag 0
#define extr_fat_id 0
#define LAST_BIT_PERCENTAGE 0.01


typedef struct auxiliary_genotype_data{
    int array_genotype_occ[10000];
    float genotype_fitness[10000];
}auxiliary_genotype_data;

typedef struct thread_auxialiary{
    FILE *f;
    int num_of_gen;
    int index_of_gene;
}thread_auxialiary;

typedef struct R1_R2_auxiliary{
  int R1[max_genes_per_person];
  int R2[max_genes_per_person];
  bool neutRegion1[max_genes_per_person][neutRegionLength];
  float father_fitness;
  char *father_genotype;

}R1_R2_auxiliary;

typedef struct person{

    int periodos;   /*maturity steps needed */
    int id;         /*personal UNIQUE id */
    bool mature;
    float fitness;

    float father_fitness;
    int mutated_from_last_gen;
    int num_of_mutations_carried;
    char *father_genotype;

    int gene_counts[max_genes_per_person];
    float gene_interactions[max_genes_per_person][max_genes_per_person];

    int vector_of_signs[max_genes_per_person];
    int maturity_array[size_of_maturity_array]; /*if max_genes_per_person change, change this also to 2^max_genes_per_person */

    int gene_R1[max_genes_per_person]; /*gia ka8e gonidio, to [10] einai oti 8a paw mexri ton 2^10 san max integer*/
    int gene_R2[max_genes_per_person];

    bool neutRegion1[max_genes_per_person][neutRegionLength]; /* for each gene create a neutral region of length neutRegionLength */

}person;

typedef struct group{
    person *person_in_group[persons_per_group];
    struct group *next;
    struct group *prev;
    int group_number;
}group;

typedef struct population{
    group *groups_list;
    float sum_of_fitness;
}population;

population *generation_array[max_generations];

int genes_per_person, backmutations;

bool mutatedSites[max_genes_per_person][neutRegionLength];

int apos, total_mutations;

#endif
