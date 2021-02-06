% Write a predicate to determine the lowest common multiple of a list formed from integer numbers
% lcm(A:number, B:number, R:number)
lcm(A, B, R) :-
	R is abs(A * B) / gcd(A, B).

% lcm_list(L:List, R:Number)
lcm_list([], 0).
lcm_list([H], H).
lcm_list([H1|[H2]], R):- 
    lcm(H1, H2, R).
lcm_list([H|T], R):-
    lcm_list(T,R1),
    lcm(H, R1, R).

% check_power_2(X:number)
check_power_2(X):- check_power_2(X, 1).
% check_power_2(X:number, C:number)
check_power_2(X, C):- X = C.
check_power_2(X, C):- X > C,
    C1 is C * 2,
    check_power_2(X, C1).

% add_value(L:list, E:number, R:list)
add_value(L, E, R):- add_value(L, E, 1, R).
% add_value(L:list, E:number, C:number, R:list)
add_value([], _, _, []).
add_value([H1|T], E, C, [H1|[E|R]]):- check_power_2(C),!,
    C1 is C + 1,
    add_value(T, E, C1, R).
add_value([H1|T], E, C, [H1|R]):-
    C1 is C + 1,
    add_value(T, E, C1, R).
    

start1:-
    lcm_list([2,3,4,5],X),
    print(X).

start2:-
    add_value([2,3,4,5], 9, 1, X),
    print(X).
