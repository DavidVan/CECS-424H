% For Problem 1

parent(tom, bob).
parent(bob, pat).
parent(bob, ada).
parent(pat, jim).
parent(ada, michelle).

male(tom).
male(bob).
male(jim).
male(pat).
female(ada).
female(michelle).

sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
brother(X, Y) :- male(X), sibling(X, Y).
aunt(X, Y) :- female(X), parent(Z, Y), sibling(X, Z).

ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(Z, Y), ancestor(X, Z).

% Problem 1 Answer

sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
cousin(X, Y) :- parent(Z, X), parent(W, Y), sibling(Z, W).

% Problem 2 Answer

third([W, X, Y | Z], Y).

% Problem 3 Answer

last([X], X).
last([X|T], Y) :- last(T, Y).

% Problem 4 Answer

sum([], 0).
sum([H|T], S) :- sum(T, D), S is D + H.

mylength([], 0).
mylength([_|T], L) :- length(T, S), L is S + 1.

mean([X], X).
mean([H|T], M) :- sum(T, X), mylength(T, Y), mean(T, D), M is (X + H) / (Y + 1).

% Problem 5 Answer

prefix([], X).
prefix([H1|T1], [H2|T2]) :- H1 = H2, prefix(T1, T2).
