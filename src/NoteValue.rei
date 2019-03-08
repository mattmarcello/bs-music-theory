type t =
  Model.NoteValue.t = {
  type_: Model.NoteValueType.t,
  modifier: Model.NoteModifier.t,
};
let makeWithType: Model.NoteValueType.t  => t;
let div: (t, Model.NoteValueType.t) => float;
