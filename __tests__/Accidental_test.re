open Jest;

open Accidental;

testAll(
  "accidentals",
  [
    (flat->multiplyInt(2), doubleFlat),
    (doubleFlat->divideInt(2), flat),
    (Accidental.sharps(2)->subtractInt(2), Accidental.natural),
    (Accidental.flats(2)->addInt(2), Accidental.natural),
    (
      Accidental.sharps(2)->add(Accidental.sharps(1)),
      Accidental.initializeWithInteger(3),
    ),
  ],
  ((actual, expected)) =>
  actual == expected ? pass : fail("")
);

testAll(
  "make with string literal",
  [
    (Accidental.make(`StringLiteral("#")), Sharps(1)),
    (Accidental.make(`StringLiteral("##")), Sharps(2)),
    (Accidental.make(`StringLiteral("###")), Sharps(3)),
    (Accidental.make(`StringLiteral("b")), Flats(1)),
    (Accidental.make(`StringLiteral("bb")), Flats(2)),
    (Accidental.make(`StringLiteral("bbb")), Flats(3)),
    /* TODO: Unicode pattern matching not supported */
    /* (Accidental.make(`StringLiteral("♯")), Sharps(1)), */
    /* (Accidental.make(`StringLiteral("♯♯")), Sharps(2)), */
    /* (Accidental.make(`StringLiteral("♯♯♯")), Sharps(3)), */
    (Accidental.make(`StringLiteral("")), Natural),
    (Accidental.make(`StringLiteral("#b#b")), Natural),
  ],
  ((actual, expected)) =>
  Expect.(expect(actual) |> toEqual(expected))
);
