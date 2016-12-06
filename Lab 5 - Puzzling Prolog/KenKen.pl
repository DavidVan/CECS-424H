:- use_module(library(clpfd)).

% Based on http://programmablelife.blogspot.co.at/2012/07/adventures-in-declarative-programming.html

% Solution is for http://www.calcudoku.org/en/2016-11-29/6/3/1

kenken(Rows) :-
    % append/2 flattens the first argument into the second,
    % giving a single list of all the squares in the puzzle.
    append(Rows, Values),
    Values ins 1..6,
    % maplist/2 corresponds to "all"; it is true if the given predicate function is true
    % when applied to all elements of the given list.
    maplist(all_different, Rows),

    % transpose/2 does a matrix transpose on the puzzle to give a list of
    % columns instead of rows.
    transpose(Rows, Cols),
    maplist(all_different, Cols),

    % First, give each row a name.
    Rows = [A, B, C, D, E, F],
    % Next, give each item in each row a name.
    [A1, A2, A3, A4, A5, A6] = A,
    [B1, B2, B3, B4, B5, B6] = B,
    [C1, C2, C3, C4, C5, C6] = C,
    [D1, D2, D3, D4, D5, D6] = D,
    [E1, E2, E3, E4, E5, E6] = E,
    [F1, F2, F3, F4, F5, F6] = F,
    % Next, enforce the constraints.
    A1 + B1 + B2 + B3 + C3 #= 24,
    (A2 - A3 #= 1; A3 - A2 #= 1),
    (A4 // A5 #= 2; A5 // A4 #= 2),
    A6 * B4 * B5 * B6 * C4 #= 72,
    C1 + D1 + D2 #= 14,
    C2 #= 5,
    C5 #= 2,
    C6 * D5 * D6 #= 18,
    D3 * D4 * E3 * E4 #= 60,
    E1 * F1 #= 3,
    E2 + E5 + F2 + F3 + F4 + F5 #= 22,
    (E6 - F6 #= 1; F6 - E6 #= 1),

    maplist(label, Rows).

% To solve, enter:
%
% Puzzle = [
%     [_,_,_,_,_,_],
%     [_,_,_,_,_,_],
%     [_,5,_,_,2,_],
%     [_,_,_,_,_,_],
%     [_,_,_,_,_,_],
%     [_,_,_,_,_,_]
% ],
% Puzzle = [A,B,C,D,E,F],
% kenken([A,B,C,D,E,F]).
