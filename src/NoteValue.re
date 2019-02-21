type t = {
  type_: NoteValueType.t,
  modifier: NoteModifier.t,
};

let make = fun
 | `Type(noteValueType) => { 
   type_: noteValueType,
   modifier: Default,

 } 

let div: (t, NoteValueType.t) => float =
  (noteValue, noteValueType) => {
    noteValue.modifier->NoteModifier.rawValue
	    *. noteValueType -> NoteValueType.rawValue
    /. noteValue.type_ ->NoteValueType.rawValue;
  };
