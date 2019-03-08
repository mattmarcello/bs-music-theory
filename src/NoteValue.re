type t =
  Model.NoteValue.t = {
    type_: Model.NoteValueType.t,
    modifier: Model.NoteModifier.t,
  };
let makeWithType = noteValueType => {type_: noteValueType, modifier: Default};
let div: (t, NoteValueType.t) => float =
  (noteValue, noteValueType) => {
    noteValue.modifier->NoteModifier.rawValue
    *. noteValueType->NoteValueType.rawValue
    /. noteValue.type_->NoteValueType.rawValue;
  };
