open Virtual_dom;

let svg = Vdom.Node.create_svg("svg");
let attr = Vdom.Attr.create;

// Here is an example of how to use grid_view
// let view : Vdom.Node.t = grid_view([square1, square2, square3, square4, square5, square6, square7, square8, square9])
// layout:
// _____ _____ _____
// |_1_| |_2_| |_3_|
// _____ _____ _____
// |_4_| |_5_| |_6_|
// _____ _____ _____
// |_7_| |_8_| |_9_|

// input: a list of 9 square class (can be built by view_of_square)
// output: a class with 3*3 grid layout
let grid_view = (squares: list(Vdom.Node.t)) => {
  Vdom.Node.div(
    ~attr=
      Vdom.Attr.many([
        Vdom.Attr.class_("grid"),
        Vdom.Attr.style(Css_gen.create(~field="display", ~value="grid")),
        Vdom.Attr.style(
          Css_gen.create(
            ~field="grid-template-columns",
            ~value="repeat(3, 1fr)",
          ),
        ),
        Vdom.Attr.style(
          Css_gen.create(~field="grid-auto-flow", ~value="row"),
        ),
      ]),
    squares,
  );
};

let square = (w: bool) =>
  svg(
    ~key="rect",
    ~attr=
      Vdom.Attr.many([
        attr("width", "24"),
        attr("height", "24"),
        attr("stroke", "black"),
        attr("stroke-width", "1"),
        w
          ? attr("fill", "rgba(173, 216, 230, 0.2)")
          : attr("fill", "rgba(0, 0, 0, 0)"),
      ]),
    [],
  );

//view build a virtual dom from a square
let view = (s: Model.square): Vdom.Node.t =>
  switch (s.marked) {
  | Some(X) =>
    Vdom.Node.div(
      ~attr=Vdom.Attr.classes(["player-mark"]),
      [
        svg(
          ~attr=attr("viewBox", "0 0 24 24"),
          [
            Vdom.Node.create_svg(
              "line",
              ~attr=
                Vdom.Attr.many([
                  attr("x1", "18"),
                  attr("y1", "6"),
                  attr("x2", "6"),
                  attr("y2", "18"),
                ]),
              [],
            ),
            Vdom.Node.create_svg(
              "line",
              ~attr=
                Vdom.Attr.many([
                  attr("x1", "6"),
                  attr("y1", "6"),
                  attr("x2", "18"),
                  attr("y2", "18"),
                ]),
              [],
            ),
            square(s.winning),
          ],
        ),
      ],
    )
  | Some(O) =>
    Vdom.Node.div(
      ~attr=Vdom.Attr.classes(["player-mark"]),
      [
        svg(
          ~attr=attr("viewBox", "0 0 24 24"),
          [
            Vdom.Node.create_svg(
              "circle",
              ~attr=
                Vdom.Attr.many([
                  attr("cx", "12"),
                  attr("cy", "12"),
                  attr("r", "7"),
                ]),
              [],
            ),
            square(s.winning),
          ],
        ),
      ],
    )
  | None =>
    Vdom.Node.div(
      ~attr=Vdom.Attr.classes(["player-mark"]),
      [
        Vdom.Node.create_svg(
          "svg",
          ~attr=attr("viewBox", "0 0 24 24"),
          [square(s.winning)],
        ),
      ],
    )
  };
