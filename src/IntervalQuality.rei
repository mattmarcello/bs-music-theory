type t =
  Model.IntervalQuality.t =
    Diminished
  | Perfect
  | Minor
  | Major
  | Augmented;

let notation: t => string;

let description: t => string;
