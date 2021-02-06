/*
 * 2. Are given n points in a plan (represented using its coordinates). 
 * Write a predicate to determine all subsets of collinear points.
*/

/*
 * collinear_triple(a, b, c) = 
 * 	True, a1 = b1 = c1
 *  True, a2 = b2 = c2
 *  True, (b2 - a2) * (c1 - b1) = (b1 - a1) * (c2 - b2)
 * 				; equivalent to (b2 - a2) / (b1 - a1) = (c2 - b2) / (c1 - b1)
 * 	False, otherwise
 * 
 * collinear_triple(A: list, B: list, C: list)
 * collinear_triple(i,i,i)
*/
collinear_triple([X, _], [X, _], [X, _]).
collinear_triple([_, Y], [_, Y], [_, Y]).
collinear_triple([A1, A2], [B1, B2], [C1, C2]):-
    (B2 - A2) * (C1 - B1) =:= (B1 - A1) * (C2 - B2).

/*
 * collinear(l1...ln) =
 * 	False, n < 2
 * 	True, n = 2
 * 	collinear_triple(l1, l2, l3), collinear(l2...ln)
 * 	False, otherwise
 * 
*/
collinear([]):- false.
collinear([_]):- false.
collinear([_, _]):-!.
collinear([A, B, C | T]):-
    collinear_triple(A, B, C),
    collinear([B, C | T]).

/*
 * is_subset(s1...sm, l1...ln) =
 * 	True, m = 0, n = 0
 * 	is_subset(s2...sm, l2...ln), s1 = l1
 * 	is_subset(s1...sm, l2...ln), otherwise
 * 
 * is_subset(Subset: list, List: list)
 * is_subset(o, i)
 * 
*/
is_subset([], []).
is_subset([H | T1], [H | T2]):-
    is_subset(T1, T2).
is_subset(Subset, [_ | T]):-
    is_subset(Subset, T).

/*
 * collinear_subset(s1...sm, l1...ln) =
 * 	True, m = 0, n = 0
 * 	is_subset(s1...sm, l1...ln),
 * 	is_subset(s1...sm, l2...ln), otherwise
 * 
 * is_subset(Subset: list, List: list)
 * is_subset(o, i)
 * 
*/
collinear_subset([], []).
collinear_subset(Subset, List):-
    is_subset(Subset, List),
    collinear(Subset).

/*
 * collinear_subsets(List: list, Subsets: list)
 * collinear_subsets(i, o)
*/

collinear_subsets(Subsets, List) :- 
    findall(CurrentSubsets, collinear_subset(CurrentSubsets, List), Subsets).

start:-
    collinear_subsets(Subsets, [[1, 1], [2, 2], [3, 3], [0, 2], [-1, 3]]),
	print(Subsets).