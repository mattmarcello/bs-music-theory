type t =
  Model.Scale.t = {
  type_: Model.ScaleType.t,
  key: Model.Key.t,
};
let make:
  (~type_: Model.ScaleType.t, ~key: Model.Key.t) => t;
let pitches:
  (t, ~octaves: list(int), unit) => Belt.List.t(Model.Pitch.t);
let keys: t => list(Model.Key.t);
let harmonicField:
  (t, ~for_: Model.HarmonicField.t, ~inversion: int=?, unit) =>
  list(Model.Chord.t);
let description: t => string;
