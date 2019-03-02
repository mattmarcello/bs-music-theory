//TODO: should this really be in its own file?

type t =
  | Triad
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

