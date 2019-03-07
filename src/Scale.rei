type t =
  MusicTheory.Model.Scale.t = {
  type_: MusicTheory.Model.ScaleType.t,
  key: MusicTheory.Model.Key.t,
};
let make:
  (~type_: MusicTheory.Model.ScaleType.t, ~key: MusicTheory.Model.Key.t) => t;
let pitches:
  (t, ~octaves: list(int), unit) => Belt.List.t(MusicTheory.Model.Pitch.t);
let keys: t => list(MusicTheory.Model.Key.t);
let harmonicField:
  (t, ~for_: MusicTheory.Model.HarmonicField.t, ~inversion: int=?, unit) =>
  list(MusicTheory.Model.Chord.t);
let description: t => string;
