type t =
  MusicTheory.Model.NoteValue.t = {
  type_: MusicTheory.Model.NoteValueType.t,
  modifier: MusicTheory.Model.NoteModifier.t,
};
let makeWithType: MusicTheory.Model.NoteValueType.t  => t;
let div: (t, MusicTheory.Model.NoteValueType.t) => float;
