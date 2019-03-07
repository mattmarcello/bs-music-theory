type t =
  MusicTheory.Model.NoteValueType.t =
    DoubleWhole
  | Whole
  | Half
  | Quarter
  | Eighth
  | Sixteenth
  | Thirtysecond
  | Sixtyfourth;

let makeWithFloat = fun 
  | 0.5 => Some(DoubleWhole)
  | 1. => Some(Whole)
  | 2. => Some(Half)
  | 4. => Some(Quarter)
  | 8. => Some(Eighth)
  | 16. => Some(Sixteenth)
  | 32. => Some(Thirtysecond)
  | 64. => Some(Sixtyfourth)
  | _ => None

let rawValue =
  fun
  | DoubleWhole => 0.5
  | Whole => 1.
  | Half => 2.
  | Quarter => 4.
  | Eighth => 8.
  | Sixteenth => 16.
  | Thirtysecond => 32.
  | Sixtyfourth => 64.;


