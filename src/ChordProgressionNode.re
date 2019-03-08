type t = Model.ChordProgressionNode.t = | I | II | III | IV | V | VI | VII;

let next =
  fun
  | I => [I, II, III, IV, V, VI, VII]
  | II => [V, III, VI, VII]
  | III => [II, IV, VI]
  | IV => [I, III, V, VII]
  | V => [I]
  | VI => [II, IV]
  | VII => [VI];

let all = [I, II, III, IV, V, VI, VII];

let description =
  fun
  | I => "I"
  | II => "II"
  | III => "III"
  | IV => "IV"
  | V => "V"
  | VI => "VI"
  | VII => "VII";

let rawValue =
  fun
  | I => 1
  | II => 2
  | III => 3
  | IV => 4
  | V => 5
  | VI => 6
  | VII => 7
