type t =
  Model.TimeSignature.t = {
  beats: int,
  noteValue: Model.NoteValueType.t,
};
let make:
  (~beats: int=?, ~noteValue: NoteValueType.t=?, unit) => t;
let makeWithBeatsAndDivision: (int, float) => option(t);
let description: t => string;
