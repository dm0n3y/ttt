open Virtual_dom.Vdom;

let svg = Node.create_svg("svg");
let attr = Attr.create;

let view = (p: Player.t): Node.t =>
  switch (p) {
  | X =>
    Node.div(
      ~attr=Attr.classes(["player-mark"]),
      [
        svg(
          ~attr=attr("viewBox", "0 0 24 24"),
          [
            Node.create_svg(
              "line",
              ~attr=
                Attr.many([
                  attr("x1", "18"),
                  attr("y1", "6"),
                  attr("x2", "6"),
                  attr("y2", "18"),
                ]),
              [],
            ),
            Node.create_svg(
              "line",
              ~attr=
                Attr.many([
                  attr("x1", "6"),
                  attr("y1", "6"),
                  attr("x2", "18"),
                  attr("y2", "18"),
                ]),
              [],
            ),
          ],
        ),
      ],
    )
  | O =>
    Node.div(
      ~attr=Attr.classes(["player-mark"]),
      [
        svg(
          ~attr=attr("viewBox", "0 0 24 24"),
          [
            Node.create_svg(
              "circle",
              ~attr=
                Attr.many([
                  attr("cx", "12"),
                  attr("cy", "12"),
                  attr("r", "7"),
                ]),
              [],
            ),
          ],
        ),
      ],
    )
  };
