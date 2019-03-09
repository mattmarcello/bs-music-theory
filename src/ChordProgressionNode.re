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
  | I => 0
  | II => 1
  | III => 2
  | IV => 3
  | V => 4
  | VI => 5
  | VII => 6
