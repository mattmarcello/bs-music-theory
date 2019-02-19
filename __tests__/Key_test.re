open Jest;

testAll(
  "make with string literal",
  [
    (
      Key.make(`StringLiteral("a##b")),
      Key.{type_: A, accidental: Sharps(1)},
    ),
    (
      Key.make(`StringLiteral("a#")),
      Key.{type_: A, accidental: Sharps(1)},
    ),
  ],
  ((actual, expected)) =>
  Expect.(expect(actual) |> toEqual(expected))
);

testAll(
  "equality",
  [
  Key.{type_: C, accidental: Accidental.flat },
  Key.{type_: C, accidental: Sharps(23) },
  Key.{type_: C, accidental: Flats(13) },
  Key.{type_: C, accidental: Flats(25) }
  ],
  actual => {
    let b = Key.{type_: B, accidental: Natural};

    Key.equal(b, actual ) ? pass : fail("")
  },
);
