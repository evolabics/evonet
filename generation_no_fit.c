#include "generation_no_fit.h"

extern int curr_num_of_groups;
int **sensitivity_array;

R1_R2_auxiliary *choose_random_father_dependencies_combined_R1R2_swapping(int num_of_gen,gsl_rng *r,FILE *f,FILE *d){
    int id_patera1,id_patera2;
    int genes_from_first_parent;
    int i,k;
    int group_counter1,person_counter1,group_counter2,person_counter2;
    group *temp1=generation_array[num_of_gen-1]->groups_list;
    group *temp2=generation_array[num_of_gen-1]->groups_list;
   /* printf("random PLUS combinations\n"); */

    R1_R2_auxiliary *new_auxiliary;

   /* printf("Random fathers R1R2 swapping\n"); */

    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    id_patera1=gsl_rng_uniform_int(r,(curr_num_of_groups*persons_per_group));
    id_patera2=gsl_rng_uniform_int(r,(curr_num_of_groups*persons_per_group));

    if (extr_fat_id){
        extract_father_id(f,id_patera1,id_patera2);
    /* printf("Counter2= %d\n",counter1); */
    }

    group_counter1=id_patera1/persons_per_group;
    person_counter1=id_patera1%persons_per_group;
    /*printf("Group Counter1 %d person_counter1 %d \n",group_counter1,person_counter1); */
    group_counter2=id_patera2/persons_per_group;
    person_counter2=id_patera2%persons_per_group;


    for(i=0;i<group_counter1;i++){
        if(temp1->next!=NULL){
            temp1=temp1->next;
        }
    }

    for(i=0;i<group_counter2;i++){
        if(temp2->next!=NULL){
            temp2=temp2->next;
       }
    }

    extract_mutation_array(d,temp1->person_in_group[person_counter1],temp2->person_in_group[person_counter2]);

   /* printf("ID patera %d ID patera %d \n",generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->id,generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->id);
*/
    genes_from_first_parent=gsl_rng_uniform_int(r,genes_per_person);

   /* extract_mutation_array(d,temp1->person_in_group[person_counter1],temp2->person_in_group[person_counter2]); */

    for(i=0;i<genes_per_person;i++){
        if(i<genes_from_first_parent){
            new_auxiliary->R1[i]=temp1->person_in_group[person_counter1]->gene_R1[i];
            new_auxiliary->R2[i]=temp1->person_in_group[person_counter1]->gene_R2[i];
            /*NEW CODE*/
            for(k=0;k<neutRegionLength;k++){
                    new_auxiliary->neutRegion1[i][k]=temp2->person_in_group[person_counter2]->neutRegion1[i][k];
            }
        }
        else{
            new_auxiliary->R1[i]=temp2->person_in_group[person_counter2]->gene_R1[i];
	        new_auxiliary->R2[i]=temp2->person_in_group[person_counter2]->gene_R2[i];
            /*NEW CODE*/
            for(k=0;k<neutRegionLength;k++){
                    new_auxiliary->neutRegion1[i][k]=temp2->person_in_group[person_counter2]->neutRegion1[i][k];
            }
        }
    }

    /* for(i=0;i<genes_per_person;i++){ */
    /*     if(i<genes_from_first_parent){ */
    /* 	  new_auxiliary->R2[i]=temp2->person_in_group[person_counter2]->gene_R2[i]; */
    /*     } */
    /*     else{ */
    /* 	  new_auxiliary->R2[i]=temp1->person_in_group[person_counter1]->gene_R2[i]; */
    /*     } */
    /* } */
    /*
    printf("Pira apo prwto patera %d gonidia\n", genes_from_first_parent);
    for(i=0;i<max_genes_per_person;i++){
        printf("R1:%d R2: %d\n", new_auxiliary->R1[i],new_auxiliary->R2[i]);
    }
*/
 /*
    for (i = 0; i < max_genes_per_person; i++){
        for(j=0;j<max_genes_per_person;j++){
            printf("%d ",new_auxiliary->dependancies[i][j]);
        }
        printf("\n");
    }
    */
    /*create_mutations(new_dependancies);*/
    return new_auxiliary;
}

R1_R2_auxiliary *choose_random_father_dependencies_combined_row_swapping(int num_of_gen,gsl_rng *r,FILE *f,FILE *d){
    int group_counter1=0;
    int person_counter1=0;
    int id_patera1;

    int i,j,k;

    int group_counter2=0;
    int person_counter2=0;
    int id_patera2;

    R1_R2_auxiliary *new_auxiliary;
    group *temp2,*temp1;

    int which_parent;

    /*printf("Random fathers row_swapping\n");*/


    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    temp1=generation_array[num_of_gen-1]->groups_list;
    temp2=generation_array[num_of_gen-1]->groups_list;
    /*printf("No fitness PLUS combined");*/

    id_patera1=gsl_rng_uniform_int(r,(curr_num_of_groups*persons_per_group));
    id_patera2=gsl_rng_uniform_int(r,(curr_num_of_groups*persons_per_group));

    
    if (extr_fat_id){
        extract_father_id(f,id_patera1,id_patera2);
    /* printf("Counter2= %d\n",counter1); */
    }

    group_counter1=id_patera1/persons_per_group;
    person_counter1=id_patera1%persons_per_group;
/*    printf("Group_of_father %d Person_on_group %d \n",group_counter,person_counter); */

    group_counter2=id_patera2/persons_per_group;
    person_counter2=id_patera2%persons_per_group;

    for(i=0;i<group_counter1;i++){
        temp1=temp1->next;
    }

    for(i=0;i<group_counter2;i++){
        temp2=temp2->next;
    }

    extract_mutation_array(d,temp1->person_in_group[person_counter1],temp2->person_in_group[person_counter2]);

    for(i=0;i<genes_per_person;i++){
        which_parent=gsl_rng_uniform_int(r,2);
        /*row_swapping*/
        if(which_parent==0){
            /*printf("Apo prwto theseis+euros:%d thesi_neutral:%d euros:%d\n",thesi_neutral+euros,thesi_neutral,euros);*/
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R1[j]=temp1->person_in_group[person_counter1]->gene_R1[j];
                /*NEW CODE*/
                for(k=0;k<neutRegionLength;k++){
                    new_auxiliary->neutRegion1[i][k]=temp1->person_in_group[person_counter1]->neutRegion1[i][k];
                }
                /*++++++*/
            }
        }
        else{
            /*printf("Apo deutero theseis+euros:%d thesi_neutral:%d euros:%d\n",thesi_neutral+euros,thesi_neutral,euros);*/
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R1[j]=temp2->person_in_group[person_counter2]->gene_R1[j];
                /*NEW CODE*/
                for(k=0;k<neutRegionLength;k++){
                    new_auxiliary->neutRegion1[i][k]=temp1->person_in_group[person_counter1]->neutRegion1[i][k];
                }
                /*++++++*/
            }
        }
    }

    for(i=0;i<genes_per_person;i++){
        which_parent=gsl_rng_uniform_int(r,2);
        /*row_swapping*/
        if(which_parent==0){
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R2[j]=temp1->person_in_group[person_counter1]->gene_R2[j];
            }
        }
        else{
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R2[j]=temp2->person_in_group[person_counter2]->gene_R2[j];
            }
        }

    }

    return new_auxiliary;
    /*create_mutations(new_dependancies); */
}


R1_R2_auxiliary *choose_random_father_dependencies_no_combinations(int num_of_gen,gsl_rng *r,FILE *f,FILE *d){
    int group_counter=0;
    int person_counter=0;
    int id_patera,i, j;
    R1_R2_auxiliary *new_auxiliary;


    group *temp=generation_array[num_of_gen-1]->groups_list;
    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    id_patera=gsl_rng_uniform_int(r,(curr_num_of_groups*persons_per_group));
    /*printf("ID_patera:%d \n",id_patera); */

    if (extr_fat_id){
        extract_father_id(f,id_patera,-1);
    /* printf("Counter2= %d\n",counter1); */
    }

    group_counter=id_patera/persons_per_group;
    person_counter=id_patera%persons_per_group;
    /* printf("Group_of_father %d Person_on_group %d \n",group_counter,person_counter); */
    for(i=0;i<group_counter;i++){
        temp=temp->next;
    }

    extract_mutation_array(d,temp->person_in_group[person_counter],NULL);

    for(i=0;i<genes_per_person;i++){
        new_auxiliary->R1[i]=temp->person_in_group[person_counter]->gene_R1[i];
    }

    for(i=0;i<genes_per_person;i++){
        new_auxiliary->R2[i]=temp->person_in_group[person_counter]->gene_R2[i];
    }

    for(i=0; i<genes_per_person; ++i)
        for(j = 0; j < neutRegionLength; ++j)
	       new_auxiliary->neutRegion1[i][j] = temp->person_in_group[person_counter]->neutRegion1[i][j];

    /*create_mutations(new_dependancies);*/
    return new_auxiliary;
}


person *gen_create_person_no_fit(int id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,
                    double mutation_rate,gsl_rng *r,float recomb_rate,FILE *f,FILE *d){
    int i,j;
    R1_R2_auxiliary *auxiliary;
    person *new_person;
    float recomb_chance;

    new_person = (person*)calloc(1, sizeof(person));

    new_person->id=id;


    for (i=0;i<genes_per_person;i++){
        new_person->gene_counts[i]=rand_interval(min_count,max_count);
	/* pavlos 25.11.2016 */
	if (new_person->gene_counts[i]>0)
	  new_person->vector_of_signs[i]=1;
    }
    
    recomb_chance=gsl_ran_flat(r,0,1);

/*    printf("Creating Inheritance\n");*/
    if(num_of_parents && recomb_chance<=recomb_rate){
        /*printf("diplos\n");*/
        if(row_swapping){
            auxiliary=choose_random_father_dependencies_combined_row_swapping(num_of_gen,r,f,d);
        }
        else{
            auxiliary=choose_random_father_dependencies_combined_R1R2_swapping(num_of_gen,r,f,d);
        }
    }
    else{
        auxiliary=choose_random_father_dependencies_no_combinations(num_of_gen,r,f,d);
    }

    for(i=0;i<genes_per_person;i++){
      new_person->gene_R1[i]=auxiliary->R1[i];
      new_person->gene_R2[i]=auxiliary->R2[i];
      /* printf("R1: %d R2: %d \n",new_person->gene_R1[i],new_person->gene_R2[i]); */

    }

    for(i=0; i<genes_per_person; ++i){
        for(j = 0; j < neutRegionLength; ++j){
           new_person-> neutRegion1[i][j] = auxiliary-> neutRegion1[i][j];
        }
    }

    
    for(i=0; i<genes_per_person; ++i){
        for(j = 0; j < neutRegionLength; ++j){
           if( new_person-> neutRegion1[i][j] == 1 ){
               mutatedSites[i][j] = 1;
            }
        }
    }

 
    /* printf("\n"); */
    /* for (i = 0; i < max_genes_per_person; i++){ */
    /*     for(j=0;j<max_genes_per_person;j++){ */
    /*         printf("%f ",new_person->gene_interactions[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    
    /*new_person=create_mutations(new_person,mutation_rate,r);*/


    
    /* for(i=0;i<genes_per_person;i++){ */
    /*   printf("neo R1[%d]=%d, ... %d (%d)\n",i,new_person->gene_R1[i], auxiliary->R1[i], new_person->gene_R1[i] == auxiliary->R1[i]); */
    /* } */
    /* for(i=0;i<genes_per_person;i++){ */
    /*   printf("neo R2[%d]=%d, ... %d (%d)\n",i,new_person->gene_R2[i], auxiliary->R2[i], new_person->gene_R2[i] == auxiliary->R2[i]);  */
    /* } */

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            /*new_person->gene_interactions[i][j]=random_normal_distrubution(0,sqrt(10));*/
            new_person->gene_interactions[i][j]=create_gene_interactions(new_person->gene_R1[i],new_person->gene_R2[j]);
          /*  printf("%f ",create_gene_interactions(new_auxiliary->R1[i],new_auxiliary->R2[j]));
            extract_person(R1[i],R2[j]);*/
            /*if (new_person->gene_interactions[i][j]<0) printf("Arnitiko gene interaction %f\n",new_person->gene_interactions[i][j]);
            */
        }
   /*     printf("\n"); */
    }
    free(auxiliary);
    return(new_person);
}

group *gen_create_group_no_fit(int starting_id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,
                gsl_rng *r,float recomb_rate,FILE *f,FILE *d){
    int i;
    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));
             /*printf("Creating Atomo %d\n",i);*/
    #pragma omp parallel for 
    for(i=0;i<persons_per_group;i++){
        new_group->person_in_group[i]=gen_create_person_no_fit(i,num_of_gen, num_of_parents,row_swapping,min_count,max_count,mutation_rate,r,recomb_rate,f,d);
    /*printf("Atomo created %d\n",i); */
    }
    return new_group;
}

population *create_gen_population_no_fit(int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,
            gsl_rng *r,float recomb_rate,FILE *f,FILE *d){
    int i;
    group *temp;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));
    /*printf("No fit population\n"); */

    apos=0;
    total_mutations=0;

    for(i=0;i<curr_num_of_groups;i++){
        if(i==0){
            /*printf("Head on the group_list of the generation 0"); */
            new_population->groups_list=gen_create_group_no_fit(i,num_of_gen,num_of_parents,row_swapping,min_count,max_count,mutation_rate,r,recomb_rate,f,d); /*create pointer to group_list, save on the population array*/
            new_population->groups_list->next=NULL;
            new_population->groups_list->prev=NULL;
        }
        else{
            temp=new_population->groups_list;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=gen_create_group_no_fit(i,num_of_gen,num_of_parents,row_swapping,min_count,max_count,mutation_rate,r,recomb_rate,f,d);
            temp->next->next=NULL;
            temp->next->prev=temp;
        }
    }

    /*gia to extract_fathers_id*/
    fprintf(f, "\n");
   /* printf("Generation Created\n");*/
    return new_population;
}
