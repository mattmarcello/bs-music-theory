type t =
  Model.NoteModifier.t =
    Default
  | Dotted
  | Triplet
  | Quintuplet;
let rawValue: t => float;
