open Virtual_dom.Vdom;

// Here is an example of how to use grid_view
// let view : Node.t = grid_view([square1, square2, square3, square4, square5, square6, square7, square8, square9])
// layout:
// _____ _____ _____
// |_1_| |_2_| |_3_|
// _____ _____ _____
// |_4_| |_5_| |_6_|
// _____ _____ _____
// |_7_| |_8_| |_9_|

// input: a list of 9 square class (can be built by view_of_square)
// output: a class with 3*3 grid layout
let grid_view = (squares: list(Node.t)) => {
  Node.div(
    ~attr=
      Attr.many(
        Attr.[
          class_("grid"),
          style(Css_gen.create(~field="display", ~value="grid")),
          style(
            Css_gen.create(
              ~field="grid-template-columns",
              ~value="repeat(3, 1fr)",
            ),
          ),
          style(Css_gen.create(~field="grid-auto-flow", ~value="row")),
        ],
      ),
    squares,
  );
};

let square = (w: bool) =>
  Node.create_svg(
    "rect",
    ~attr=
      Attr.many(
        Attr.[
          create("width", "24"),
          create("height", "24"),
          create("stroke", "black"),
          create("stroke-width", "1"),
          w
            ? create("fill", "rgba(173, 216, 230, 0.2)")
            : create("fill", "rgba(0, 0, 0, 0)"),
        ],
      ),
    [],
  );

//view build a virtual dom from a square
let view = (s: Model.square): Node.t =>
  switch (s.marked) {
  | Some(X) =>
    Node.div(
      ~attr=Attr.classes(["player-mark"]),
      [
        Node.create_svg(
          "svg",
          ~attr=Attr.create("viewBox", "0 0 24 24"),
          [
            Node.create_svg(
              "line",
              ~attr=
                Attr.many(
                  Attr.[
                    create("x1", "18"),
                    create("y1", "6"),
                    create("x2", "6"),
                    create("y2", "18"),
                  ],
                ),
              [],
            ),
            Node.create_svg(
              "line",
              ~attr=
                Attr.many(
                  Attr.[
                    create("x1", "6"),
                    create("y1", "6"),
                    create("x2", "18"),
                    create("y2", "18"),
                  ],
                ),
              [],
            ),
            square(s.winning),
          ],
        ),
      ],
    )
  | Some(O) =>
    Node.div(
      ~attr=Attr.classes(["player-mark"]),
      [
        Node.create_svg(
          "svg",
          ~attr=Attr.create("viewBox", "0 0 24 24"),
          [
            Node.create_svg(
              "circle",
              ~attr=
                Attr.many(
                  Attr.[
                    create("cx", "12"),
                    create("cy", "12"),
                    create("r", "7"),
                  ],
                ),
              [],
            ),
            square(s.winning),
          ],
        ),
      ],
    )
  | None =>
    Node.div(
      ~attr=Attr.classes(["player-mark"]),
      [
        Node.create_svg(
          "svg",
          ~attr=Attr.create("viewBox", "0 0 24 24"),
          [square(s.winning)],
        ),
      ],
    )
  };
