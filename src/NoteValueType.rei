type t =
  Model.NoteValueType.t =
    DoubleWhole
  | Whole
  | Half
  | Quarter
  | Eighth
  | Sixteenth
  | Thirtysecond
  | Sixtyfourth;
let makeWithFloat: float => option(t);
let rawValue: t => float;
