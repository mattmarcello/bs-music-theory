type t =
  MusicTheory.Model.IntervalQuality.t =
    | Diminished | Perfect | Minor | Major | Augmented;

let notation =
  fun
  | Diminished => "d"
  | Perfect => "P"
  | Minor => "m"
  | Major => "M"
  | Augmented => "A";

let description  =
  fun
  | Diminished => "Diminished"
  | Perfect => "Perfect"
  | Minor => "Minor"
  | Major => "Major"
  | Augmented => "Augmented";
