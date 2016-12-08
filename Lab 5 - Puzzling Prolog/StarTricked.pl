ufo_enthusiast(ms_barrada).
ufo_enthusiast(ms_gort).
ufo_enthusiast(mr_klatu).
ufo_enthusiast(mr_nikto).

object(balloon).
object(clothesline).
object(frisbee).
object(water_tower).

solve :-
    ufo_enthusiast(TuesdayUFOEnthusiast), ufo_enthusiast(WednesdayUFOEnthusiast),
    ufo_enthusiast(ThursdayUFOEnthusiast), ufo_enthusiast(FridayUFOEnthusiast),
    all_different([TuesdayUFOEnthusiast, WednesdayUFOEnthusiast, ThursdayUFOEnthusiast, FridayUFOEnthusiast]),

    object(TuesdayObject), object(WednesdayObject),
    object(ThursdayObject), object(FridayObject),
    all_different([TuesdayObject, WednesdayObject, ThursdayObject, FridayObject]),

    Triples = [ [tuesday, TuesdayUFOEnthusiast, TuesdayObject],
                [wednesday, WednesdayUFOEnthusiast, WednesdayObject],
                [thursday, ThursdayUFOEnthusiast, ThursdayObject],
                [friday, FridayUFOEnthusiast, FridayObject] ],

    % 1. Mr. Klatu made his sighting at some point earlier in the week than the other who saw the balloon, but at some point later in the week than the one who spotted the Frisbee (who isn't Ms. Gort).
    \+ member([_, mr_klatu, balloon], Triples),
    \+ member([_, mr_klatu, frisbee], Triples),
    earlier(_, _),

    % 2. Friday's sighting was made by either Ms. Barrada or the one who saw a clothesline (or both).
    (member([friday, ms_barrada, _], Triples);
    member([friday, _, clothesline], Triples)),

    % 3. Mr. Nikto did not make his sighting on Tuesday.
    \+ member([tueday, mr_nikto, _], Triples),

    % 4. Mr. Klatu isn't the one whose object turned out to be a water tower.
    \+ member([_, mr_klatu, water_tower], Triples),

    tell(tuesday, TuesdayUFOEnthusiast, TuesdayObject),
    tell(wednesday, WednesdayUFOEnthusiast, WednesdayObject),
    tell(thursday, ThursdayUFOEnthusiast, ThursdayObject),
    tell(friday, FridayUFOEnthusiast, FridayObject).

% Succeeds if all elements of the argument list are bound and different.
% Fails if any elements are unbound or equal to some other element.
all_different([H | T]) :- member(H, T), !, fail.
all_different([_ | T]) :- all_different(T).
all_different([_]).

earlier(tuesday, wednesday).
earlier(tuesday, thursday).
earlier(tuesday, friday).
earlier(wednesday, thursday).
earlier(wednesday, friday).
earlier(thursday, friday).

tell(X, Y, Z) :-
    write('On '), write(X), write(', '), write(Y),
    write(' spotted a '), write(Z), write('.'), nl.
