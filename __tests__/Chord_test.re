open Jest;

test("sanity", () => {

	let actual = ChordType.ChordThirdType.make(`Interval(Interval.major3))

	let expected = Some(ChordType.ChordThirdType.Major);

	Expect.( expect( actual) |> toBe(expected))


})
