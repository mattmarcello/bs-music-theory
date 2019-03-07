type t =
  MusicTheory.Model.NoteValue.t = {
  type_: MusicTheory.Model.NoteValueType.t,
  modifier: MusicTheory.Model.NoteModifier.t,
};

let makeWithType = noteValueType => {type_: noteValueType, modifier: Default};

let div: (t, NoteValueType.t) => float =
  (noteValue, noteValueType) => {
    noteValue.modifier->NoteModifier.rawValue
    *. noteValueType->NoteValueType.rawValue
    /. noteValue.type_->NoteValueType.rawValue;
  };
