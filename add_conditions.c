#include <stddef.h>
#include "cnf.h"

//
// LOGIN: xyerom00 - Vladyslav Yeroma
//

// Tato funkce je prikladem pouziti funkci create_new_clause, add_literal_to_clause a add_clause_to_formula
// Vysvetleni, co dela, naleznete v zadani
void example_condition(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {
        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {
            // vytvori novou klauzuli
            Clause *example_clause = create_new_clause(num_of_subjects, num_of_semesters);
            // vlozi do klauzule literal x_{i,j}
            add_literal_to_clause(example_clause, true, subject_i, semester_j);
            // vlozi do klauzule literal ~x_{i,j}
            add_literal_to_clause(example_clause, false, subject_i, semester_j);
            // prida klauzuli do formule
            add_clause_to_formula(example_clause, formula);
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku a)
// Predmety jsou reprezentovany cisly 0, 1, ..., num_of_subjects-1
// Semestry jsou reprezentovany cisly 0, 1, ..., num_of_semesters-1
void each_subject_enrolled_at_least_once(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    // ZDE PRIDAT KOD

    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {
        // Vytvorim novou klauzule a chceme zapsat v klazuli disjunktni literaly z jednym predmetem pro kazdy semestr
        // Tymto postupem abych splnit podminku klauzle, musime splnit alespon jeden disjinktni literal, co bude znamenat, ze predmet existuje alespon v jednem semestru
        
        Clause* enrolled_atl_once_clause = create_new_clause(num_of_subjects, num_of_semesters);

        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {
            
            // vlozi do klauzule literal x_{i,j} 
            add_literal_to_clause(enrolled_atl_once_clause, true, subject_i, semester_j);
            
        }
        // pridame klauzule do formule
        add_clause_to_formula(enrolled_atl_once_clause, formula);
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku b)
// Predmety jsou reprezentovany cisly 0, 1, ..., num_of_subjects-1
// Semestry jsou reprezentovany cisly 0, 1, ..., num_of_semesters-1
void each_subject_enrolled_at_most_once(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    // ZDE PRIDAT KOD
    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {
        
        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {

            for (unsigned semesters_left = semester_j+1; semesters_left < num_of_semesters; ++semesters_left) {

                // Vytvorim novou klauzule a chceme zapsat v klazule disjunktni literaly z jednym predmetem a dvema semestry - j and j+1, pak v novu klauzule j and j+2 a tak dal...
                // Tymto postupem vytvorime klauzuli, kde pro kazdy semester bude disjunktni para se vsemi semestrami po j. 
                // para bude typu ~x_{i,j} \/ ~x_{i,j+1}, pak ~x_{i,j} \/ ~x_{i,j+2} a tak dal... . Ce zajistuje, ze predmety nebudou se duplicovat ve nekolikach semestrech

                Clause* enrolled_atm_once_clause = create_new_clause(num_of_subjects, num_of_semesters);

                // vlozi do klauzule literal ~x_{i,j}
                add_literal_to_clause(enrolled_atm_once_clause, false, subject_i, semester_j);
                // vlozi do klauzule literal ~x_{i,j}
                add_literal_to_clause(enrolled_atm_once_clause, false, subject_i, semesters_left);
                // pridame klauzule do formule
                add_clause_to_formula(enrolled_atm_once_clause, formula);
            }
 

        }
        
    }



    
}


// Tato funkce by mela do formule pridat klauzule predstavujici podminku c)
// Promenna prerequisities obsahuje pole s poctem prvku rovnym num_of_prerequisities
// Predmety jsou reprezentovany cisly 0, 1, ..., num_of_subjects-1
// Semestry jsou reprezentovany cisly 0, 1, ..., num_of_semesters-1
void add_prerequisities_to_formula(CNF *formula, Prerequisity* prerequisities, unsigned num_of_prerequisities, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(prerequisities != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned i = 0; i < num_of_prerequisities; ++i) {
        // prerequisities[i].earlier_subject je predmet, ktery by si mel student zapsat v nekterem semestru pred predmetem prerequisities[i].later_subject

        // ZDE PRIDAT KOD
        unsigned earlier_subject = prerequisities[i].earlier_subject;
        unsigned later_subject = prerequisities[i].later_subject;

        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {

              for (unsigned semesters_left = 0; semesters_left < semester_j+1; ++semesters_left) {
                // pro kazdy semester j vygenerujeme klauzuli tak, aby byla od nuly do semestu j (tj pro vsechi predchozi a taky tento semestr) later_subject nemohl byt vybran
                // klauzule zajistuje, ze pokud je predmet earlier_subject zapsan v semestru semester_j, tak nemusi byt take zapsan predmet later_subject v nejakem predchozim a tento semestru
                // para bude typu ~x_{earlier_subject,j} \/ ~x_{later_subject,0} ... ~x_{earlier_subject,j} \/ ~x_{later_subject,j}
                      Clause* prerequisity_clause = create_new_clause(num_of_subjects, num_of_semesters);
                      add_literal_to_clause(prerequisity_clause, false, earlier_subject, semester_j);
                      add_literal_to_clause(prerequisity_clause, false, later_subject, semesters_left);
                      add_clause_to_formula(prerequisity_clause, formula);
            }
        }
    }
}
