type t =
  MusicTheory.Model.Chord.t = {
    type_: MusicTheory.Model.ChordType.t,
    key: MusicTheory.Model.Key.t,
    inversion: int,
  };

let equals: (option(t), option(t)) => bool;

let make:
  (
    ~type_: MusicTheory.ChordType.t,
    ~key: MusicTheory.Key.t,
    ~inversion: int=?,
    unit
  ) =>
  t;

let pitches: (t, ~octave: int, unit) => list(MusicTheory.Model.Pitch.t);

let pitchesWithOctaves:
  (t, ~octaves: list(int), unit) => list(MusicTheory.Pitch.t);

let keys: t => list(MusicTheory.Key.t);

let inversions: t => Belt.List.t(t);

let romanNumeric: (t, ~for_: MusicTheory.Scale.t) => option(Js.String.t);

let notation: t => string;

let description: t => string;

module Infix: {let (==): (option(t), option(t)) => bool;};
