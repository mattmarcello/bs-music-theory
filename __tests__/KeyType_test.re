open Jest;
open KeyType;

testAll(
  "atDistance",
  [
    (D, (-2), B),
    (D, (-19), F),
    (D, 12, B),
    (D, 0, D),
    (D, 1, E),
    (D, 2, F),
    (D, (-3), A),
    (D, (-301), D),
    (F, (-3), C),
  ],
  ((key, distance, expectedKey)) =>
  KeyType.key(key, ~at=distance) == expectedKey ? pass : fail("")
);

testAll(
  "distanceFrom",
  [
    (D, B, 5),
    (D, F, 2),
    (D, D, 0),
    (D, E, 1),
    (D, F, 2),
    (D, A, 4),
    (F, C, (-3)),
  ],
  ((key', key'', distance)) =>
  KeyType.distance(key', ~from=key'') == distance ? pass : fail("")
);

Skip.test("octaveDiff");
