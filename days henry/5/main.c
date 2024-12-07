#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "common_structures.h"
#include "files_utils.h"
#include "parsing.h"
#include "utils.h"

/*
@brief see Aoc 2024 problem day 5 do understand what this does.
@param report is an int_list, it's a report
@param rules has an arc from i to j if i mut precede j
@return middle int if it is valid, 0 otherwise. 
*/
int is_valid(int_list report, graph rules){

    int i_index,j_index;
    for (int i = 0; i < report.n; i++)
    {
        for (int j = i; j < report.n; j++)
        {   
            i_index = index((int_list){rules.n,rules.elements},report.l[i]);
            j_index = index((int_list){rules.n,rules.elements},report.l[j]);
            if (rules.adjacency_matrix[j_index][i_index])
            {   
                return 0;
            }
            
        }
        
    }

    return report.l[report.n/2];
    
}

int make_valid(int_list report,graph rules){
    if (is_valid(report, rules) != 0)
    {
        return 0;
    }
    
    int*new_report = malloc(report.n*sizeof(int));
    graph new_rules = sub_graph(rules,report);
    int i = 0;
    int ni = 0;
    while (ni < report.n /2)
    {   
        print_graph(new_rules);
        while (i < new_rules.n && !is_root(new_rules,new_rules.elements[i]))
        {
            i ++;
        }
        if (i >= new_rules.n)
        {
            printf("could not make report valid\n");
            return 0;
        }
        new_rules = rm_elt(new_rules,new_rules.elements[i]);
        new_report[ni++] = new_rules.elements[i];
        i = 0;
    }

    int res;
    for (int j = 0; j < new_rules.n; j++)
    {
        if (is_root(new_rules,new_rules.elements[j]))
        {
            res = new_rules.elements[j];
            free_graph(new_rules);
            free(new_report);
            return res;
        }
        
    }


    /*new_report[report.n-1] = new_rules.elements[0];

    is = is_valid((int_list){report.n,new_report},rules);
    if (!is)
    {
        printf("could not make report valide\n");
        return 0;
    }
    return is;*/
    
}

int main(){
    char* filename = "input.txt";
    //grabing useful info
    graph rules = text_to_graph(filename);
    int_int_list reports = fill_reports(filename);

    //looking over every report
    int n = 0;
    for (int i = 0; i < reports.n; i++)
    {
        n += make_valid(reports.ll[i],rules);
    }

    printf("the answer is : %d\n",n);

    //freeing the rules and reports
    free_ii_list(reports);
    free_graph(rules);

    return 0;
    
}


// answer is 4578


/**
 * to do :
 * add_arc-----------------------------------------------------OK
 * print_graph ------------------------------------------------OK
 * is_arc -- returns yes if its an arc-------------------------OK
 * In File:----------------------------------------------------OK
 * all_numbers_in_file ----------------------------------------OK
 * text_to_graph-----------------------------------------------OK
 * In Parsing:-------------------------------------------------OK
 * number_of_reports-------------------------------------------OK
 * length_of_reports-------------------------------------------OK
 * fill_reports------------------------------------------------OK
 * in MAIN.c---------------------------------------------------OK
 * fetch reports-----------------------------------------------OK
 * grab file make graph----------------------------------------OK
 * is_valid_report == returns middle number if it's valid------OK
 * for i in reports += is_valid--------------------------------OK
 * ============================================================OK
 * part 2 :----------------------------------------------------OK
 * copygraph---------------------------------------------------OK
 * subgraph----------------------------------------------------OK
 * is_root(graph,e)--------------------------------------------OK
 * find_root---------------------------------------------------OK
 * rm_elt------------------------------------------------------OK
 */
