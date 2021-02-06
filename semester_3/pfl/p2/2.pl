/* 
 * P2.
 * a. Sort a list with keeping double values in resulted list. 
 * E.g.: [4 2 6 2 3 4] --> [2 2 3 4 4 6]
*/

/*
 * insertion(l1...ln, e) =
 *	[e], n=0
 *  e U l1 U l2...ln, e < l1
 * 	l1 U insertion(l2...ln), otherwise
 * 
 * insertion(List: list, NewElement: int, NewList: list)
 * insertion(i, i, o)
*/

insertion([], NewElement, [NewElement]).
insertion([H | T], NewElement, [NewElement, H | T]):-
    NewElement < H, !.
insertion([H | T], NewElement, [H | Remaining]):-
    insertion(T, NewElement, Remaining).

/*
 * For a heterogeneous list, formed from integer numbers and list of numbers, 
 * write a predicate to sort every sublist, keeping the doubles. 
 * Eg.: [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
 * [1, 2, [1, 4, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1, 1, 1], 7].
*/ 

/* 	
 * sort_list(l1...ln) =
 * 	[], n=0
 * 	insertion(sort_list(l2...ln), l1), otherwise
 * 
 * sort_list(List: list, SortedList: list)
 * sort_list(i, o)
*/

sort_list([], []).
sort_list([H|T], SortedList):- 
    sort_list(T, NewList), !,
    insertion(NewList, H, SortedList).

/* 	
 * sort_list_hetero(l1...ln) =
 * 	[], n=0
 * 	r1_1...r1_n, r2=0 ; where [r1, r2] = bubble(l1...ln)
 * 	sort_list(r1_1...r1_n), r2=1 ; where [r1, r2] = bubble(l1...ln)
 * 
 * sort_list(List: list, SortedList: list)
 * sort_list(i, o)
*/

sort_list_hetero([], []).
sort_list_hetero([H | T], [SortedH | Remaining]):- 
    is_list(H),
    sort_list(H, SortedH), !,
    sort_list_hetero(T, Remaining).
sort_list_hetero([H | T], [H | Remaining]):-
    sort_list_hetero(T, Remaining).

start1:-
    sort_list([4, 5, 2, 6, 2, 3, 4], Sorted),
    print(Sorted).

start2:-
    sort_list_hetero([1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7], Sorted),
    print(Sorted).
    
