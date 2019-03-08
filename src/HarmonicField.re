type t =
  Model.HarmonicField.t =
    Triad
  | Tetrad
  | Ninth
  | Eleventh
  | Thirteenth;

let all = [Triad, Tetrad, Ninth, Eleventh, Thirteenth];

let description = fun
  | Triad => "Triad"
  | Tetrad => "Tetrad"
  | Ninth => "Ninth"
  | Eleventh => "Eleventh"
  | Thirteenth => "Thirteenth"

