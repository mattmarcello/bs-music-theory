type t = {
  type_: NoteValueType.t,
  modifier: NoteModifier.t,
};

let div: (t, NoteValueType.t) => float =
  (noteValue, noteValueType) => {
    noteValue.modifier->NoteModifier.rawValue
	    *. noteValueType -> NoteValueType.rawValue
    /. noteValue.type_ ->NoteValueType.rawValue;
  };
