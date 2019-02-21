type t = 
  | DoubleWhole
  | Whole
  | Half
  | Quarter
  | Eighth
  | Sixteenth
  | Thirtysecond
  | Sixtyfourth


  let rawValue = fun
  | DoubleWhole => 0.5
  | Whole => 1.
  | Half => 2.
  | Quarter => 4.
  | Eighth => 8.
  | Sixteenth => 16.
  | Thirtysecond => 32.
  | Sixtyfourth => 64.
