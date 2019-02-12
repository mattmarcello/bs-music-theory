open Jest;

open Accidental;




testAll(
  "accidentals",
  [
    (flat->multiplyInt(2), doubleFlat),
    (doubleFlat->divideInt(2), flat),
    (Accidental.sharps(2)->subtractInt(2), Accidental.natural),
    (Accidental.flats(2) -> addInt(2), Accidental.natural),
    (Accidental.sharps(2)->add(Accidental.sharps(1)), Accidental.initializeWithInteger(3)),
  ],
  ((actual, expected)) =>
  actual == expected ? pass : fail("")
);
