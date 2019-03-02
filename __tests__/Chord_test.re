open Jest;

test("sanity", () => {

	let actual = ChordTypeT.ChordThirdType.make(`Interval(Interval.major3))

	let expected = Some(ChordTypeT.ChordThirdType.Major);

	Expect.( expect( actual) |> toBe(expected))


})
