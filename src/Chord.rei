type t =
  Model.Chord.t = {
    type_: Model.ChordType.t,
    key: Model.Key.t,
    inversion: int,
  };

let equals: (option(t), option(t)) => bool;

let make:
  (
    ~type_: Model.ChordType.t,
    ~key: Model.Key.t,
    ~inversion: int=?,
    unit
  ) =>
  t;

let pitches: (t, ~octave: int, unit) => list(Model.Pitch.t);

let pitchesWithOctaves:
  (t, ~octaves: list(int), unit) => list(Model.Pitch.t);

let keys: t => list(Model.Key.t);

let inversions: t => Belt.List.t(t);

let romanNumeric: (t, ~for_: Model.Scale.t) => option(Js.String.t);

let notation: t => string;

let description: t => string;

