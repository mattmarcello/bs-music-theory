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
      Accidental.makeWithInteger(3),
    ),
  ],
  ((actual, expected)) =>
  actual == expected ? pass : fail("")
);

testAll(
  "make with string literal",
  [
    (Accidental.makeWithString("#"), Sharps(1)),
    (Accidental.makeWithString("##"), Sharps(2)),
    (Accidental.makeWithString("###"), Sharps(3)),
    (Accidental.makeWithString("b"), Flats(1)),
    (Accidental.makeWithString("bb"), Flats(2)),
    (Accidental.makeWithString("bbb"), Flats(3)),
    /* TODO: Unicode pattern matching not supported */
    /* (Accidental.make(`StringLiteral("♯")), Sharps(1)), */
    /* (Accidental.make(`StringLiteral("♯♯")), Sharps(2)), */
    /* (Accidental.make(`StringLiteral("♯♯♯")), Sharps(3)), */
    (Accidental.makeWithString(""), Natural),
    (Accidental.makeWithString("#b#b"), Natural),
  ],
  ((actual, expected)) =>
  Expect.(expect(actual) |> toEqual(expected))
);
