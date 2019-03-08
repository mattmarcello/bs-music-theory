type t =
  Model.NoteModifier.t =
    Default
  | Dotted
  | Triplet
  | Quintuplet;

let rawValue =
  fun
  | Default => 1.
  | Dotted => 1.5
  | Triplet => 0.6667
  | Quintuplet => 0.8;
