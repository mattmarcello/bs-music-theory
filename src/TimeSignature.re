include Model.TimeSignature;

let make = (~beats=4, ~noteValue=NoteValueType.Quarter, ()) => {
  beats,
  noteValue,
};

let makeWithBeatsAndDivision = (beats, division) => {
  let noteValue = NoteValueType.makeWithFloat(division);
  switch (noteValue) {
  | Some(noteValue) => Some({beats, noteValue})
  | None => None
  };
};

let description = ts =>
  ts.beats->string_of_int
  ++ "/"
  ++ ts.noteValue->NoteValueType.rawValue->string_of_float;
