type t =
  MusicTheory.Model.HarmonicField.t =
    Triad
  | Tetrad
  | Ninth
  | Eleventh
  | Thirteenth;
let all: list(t);
let description: t => string;
