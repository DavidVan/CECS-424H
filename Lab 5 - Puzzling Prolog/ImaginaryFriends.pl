imaginary_friend(grizzly_bear).
imaginary_friend(moose).
imaginary_friend(seal).
imaginary_friend(zebra).

adventure(circus).
adventure(rock_band).
adventure(spaceship).
adventure(train).

solve :-
    imaginary_friend(JoanneImaginaryFriend), imaginary_friend(LouImaginaryFriend),
    imaginary_friend(RalphImaginaryFriend), imaginary_friend(WinnieImaginaryFriend),
    all_different([JoanneImaginaryFriend, LouImaginaryFriend, RalphImaginaryFriend, WinnieImaginaryFriend]),

    adventure(JoanneAdventure), adventure(LouAdventure),
    adventure(RalphAdventure), adventure(WinnieAdventure),
    all_different([JoanneAdventure, LouAdventure, RalphAdventure, WinnieAdventure]),

    Triples = [ [joanne, JoanneImaginaryFriend, JoanneAdventure],
                [lou, LouImaginaryFriend, LouAdventure],
                [ralph, RalphImaginaryFriend, RalphAdventure],
                [winnie, WinnieImaginaryFriend, WinnieAdventure] ],

    % 1. The seal (who isn't the creation of either Joanne or Lou) neither rode to the moon in a spaceship nor took a trip around the world on a magic train.
    \+ member([joanne, seal, _], Triples),
    \+ member([lou, seal, _], Triples),
    \+ member([_, seal, spaceship], Triples),
    \+ member([_, seal, train], Triples),

    % 2. Joanne's imaginary friend (who isn't the grizzly bear) went to the circus.
    \+ member([joanne, grizzly_bear, _], Triples),
    member([joanne, _, circus], Triples),

    % 3. Winnie's imaginary friend is a zebra.
    member([winnie, zebra, _], Triples),

    % 4. The grizzly bear didn't board the spaceship to the moon.
    \+ member([_, grizzly_bear, spaceship], Triples),

    tell(joanne, JoanneImaginaryFriend, JoanneAdventure),
    tell(lou, LouImaginaryFriend, LouAdventure),
    tell(ralph, RalphImaginaryFriend, RalphAdventure),
    tell(winnie, WinnieImaginaryFriend, WinnieAdventure).

% Succeeds if all elements of the argument list are bound and different.
% Fails if any elements are unbound or equal to some other element.
all_different([H | T]) :- member(H, T), !, fail.
all_different([_ | T]) :- all_different(T).
all_different([_]).

tell(X, Y, Z) :-
    write(X), write('\'s imaginary friend is '), write(Y),
    write(', and their adventure involved a '), write(Z), write('.'), nl.

