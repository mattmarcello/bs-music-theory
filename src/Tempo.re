include Model.Tempo;

let make = (~timeSignature=TimeSignature.make(), ~bpm=120.,()) => {
  timeSignature,
  bpm,
};

let duration = (tempo, ~of_ as noteValue: NoteValue.t, ()) => {
  let secondsPerBeat = 60.0 /. tempo.bpm;
  secondsPerBeat
  *. tempo.timeSignature.noteValue->NoteValueType.rawValue
  /. noteValue.type_->NoteValueType.rawValue
  *. noteValue.modifier->NoteModifier.rawValue;
};

let sampleLength =
    (tempo, ~of_ as noteValue: NoteValue.t, ~sampleRate=44100., ()) => {
  let secondsPerBeat = 60.0 /. tempo.bpm;
  secondsPerBeat
  *. sampleRate
  *. (4. /. noteValue.type_->NoteValueType.rawValue)
  *. noteValue.modifier->NoteModifier.rawValue;
};

let hertz = (tempo, ~of_ as noteValue: NoteValue.t, ()) => {
  1. /. tempo->duration(~of_=noteValue, ());
};

let description = t => t.bpm->string_of_float;
