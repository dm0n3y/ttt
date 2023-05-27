module Vdom = Virtual_dom.Vdom;

let svg = Vdom.Node.create_svg;
let attr = Vdom.Attr.create;

let grid_view = (squares: list(Vdom.Node.t)) => {
  Vdom.Node.div(
    [
      Vdom.Attr.class_("grid"),
      Vdom.Attr.style(Css_gen.create(~field="display", ~value="grid")),
      Vdom.Attr.style(
        Css_gen.create(
          ~field="grid-template-columns",
          ~value="repeat(3, 1fr)",
        ),
      ),
      Vdom.Attr.style(Css_gen.create(~field="grid-auto-flow", ~value="row")),
    ],
    squares,
  );
};

let square = (w: bool) =>
  svg(
    "rect",
    [
      attr("width", "24"),
      attr("height", "24"),
      attr("stroke", "black"),
      attr("stroke-width", "1"),
      w
        ? attr("fill", "rgba(173, 216, 230, 0.2)")
        : attr("fill", "rgba(0, 0, 0, 0)"),
    ],
    [],
  );

let view = (s: Model.square): Vdom.Node.t =>
  switch (s.marked) {
  | Some(X) =>
    Vdom.Node.div(
      [Vdom.Attr.classes(["player-mark"])],
      [
        svg(
          "svg",
          [attr("viewBox", "0 0 24 24")],
          [
            Vdom.Node.create_svg(
              "line",
              [
                attr("x1", "18"),
                attr("y1", "6"),
                attr("x2", "6"),
                attr("y2", "18"),
              ],
              [],
            ),
            Vdom.Node.create_svg(
              "line",
              [
                attr("x1", "6"),
                attr("y1", "6"),
                attr("x2", "18"),
                attr("y2", "18"),
              ],
              [],
            ),
            square(s.winning),
          ],
        ),
      ],
    )
  | Some(O) =>
    Vdom.Node.div(
      [Vdom.Attr.classes(["player-mark"])],
      [
        svg(
          "svg",
          [attr("viewBox", "0 0 24 24")],
          [
            Vdom.Node.create_svg(
              "circle",
              [attr("cx", "12"), attr("cy", "12"), attr("r", "7")],
              [],
            ),
            square(s.winning),
          ],
        ),
      ],
    )
  | None =>
    Vdom.Node.div(
      [Vdom.Attr.classes(["player-mark"])],
      [svg("svg", [attr("viewBox", "0 0 24 24")], [square(s.winning)])],
    )
  };
