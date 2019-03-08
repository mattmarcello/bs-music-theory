type t =
  Model.Tempo.t = {
    timeSignature: Model.TimeSignature.t,
    bpm: float,
  };
let make: (~timeSignature: Model.TimeSignature.t=?, ~bpm: float=?, unit) => t;
let duration: (t, ~of_: Model.NoteValue.t, unit) => float;
let sampleLength:
  (t, ~of_: Model.NoteValue.t, ~sampleRate: float=?, unit) => float;
let hertz: (t, ~of_: Model.NoteValue.t, unit) => float;
let description: t => string;
