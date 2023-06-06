open Virtual_dom.Vdom;

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
