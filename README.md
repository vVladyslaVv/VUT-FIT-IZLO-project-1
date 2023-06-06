# Remember about plagiarism
# VUT-FIT-IZLO-project-1
VUT FIT v Brne IZLO project 1

# IZLO – Projekt 1: SAT solvery
# Úvod

V projektu uvažujeme problém studenta, který se snaží naplánovat pořadí, ve kterém si zapíše předměty během studia. Předměty však mezi sebou mají řadu prerekvizit a není jasné zda vůbec existuje způsob jak si všechny zvolené předměty zapsat tak, aby byly všechny prerekvizity splněny. Problém budeme řešit pomocí převodu na splnitelnost ve výrokové logice a následného využití SAT solveru.
Zadání

Instancí problému je číslo
udávající počet zapsaných předmětů, číslo udávající počet semestrů a množina prerekvizit mezi předměty. Jak předměty, tak semestry jsou reprezentovány pomocí čísel v rozsahu pro předměty a pro semestry. Prerekvizita je dvojice udávající, že pro zapsání předmětu v nějakém semestru je potřeba, aby předmět byl zapsán v semestru , takovém, že

. Dále je potřeba zajistit, že každý předmět je zapsán právě v jednom semestru.

Vaším cílem je vytvořit program, který pro instanci tohoto problému vygeneruje formuli, která je splnitelná právě tehdy, když problém má řešení. Navíc musí platit, že každý model vygenerované formule splňuje tři níže uvedené podmínky. K dispozici již máte kostru (k dispozici níže), která se stará o zpracování vstupu a vygenerování formule ve formátu DIMACS (popis např. zde). Vaším úkolem je doplnit kód tří funkcí v souboru code/add_conditions.c, které se starají o generování následujících podmínek:

    Každý předmět je zapsán alespoň jednou. Generování této formule je potřeba doplnit do funkce each_subject_enrolled_at_least_once(...).

    Každý předmět je zapsán nejvýše jednou. Generování této formule je potřeba doplnit do funkce each_subject_enrolled_at_most_once(...).

    Splnění prerekvizit. Formuli zajišťující, že všechny prerekvizity jsou splněny, je potřeba vygenerovat ve funkci add_prerequisities_to_formula(...). Pole obsahující prerekvizity je jedním z parametrů této funkce. Prerekvizita je struktura obsahující položky earlier_subject a later_subject. Pro splnění prerekvizity je potřeba, aby byl earlier_subject zapsán dříve než later_subject.

Výše zmíněné funkce jsou jediné části kódu, které mají být modifikovány.
