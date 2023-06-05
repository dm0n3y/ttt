open Virtual_dom.Vdom;
//here is an example of building a Node.t with attributes and children
//
// Node.div(
//   [Attr.id("board")],// a list of attributes, like id, class, style, etc
//   [
//     Node.div([Attr.classes(["row"])], []),// a list of children
//   ],
// );

// the code above would generate html like this
// <div id="board">
//   <div class="row"></div>
// </div>

// build a Node.t for each square
// The click handler will call the inject function, which will send an action to the update function
// You can define the type of index with any other format, but remember to synchronize the type with the update.re(i)
let view_of_square = (~inject, ~index: int, square: Model.square): Node.t =>
  switch (square.marked) {
  | None =>
    let click_handlers = [
      Attr.on_click(_ => inject(Update.Action.Mark(index))),
    ];
    Node.div(
      ~attr=Attr.many([Attr.classes(["square"]), ...click_handlers]), //only empty square can be clicked
      [PlayerMark.view(square)],
    );
  | Some(_) =>
    Node.div(
      ~attr=Attr.many([Attr.classes(["square"])]),
      [PlayerMark.view(square)],
    )
  };

// function squares and player_turn in Model.re might be helpful to gather information from Model.t
// use view_of_square to build a list of Node.t
// use PlayerMark.grid_view to transfer the list of Node.t to a Node.t with proper layout
let view = (~inject, model: Model.t) => {
  //TODO
  Node.div(~attr=Attr.id("board"), []);
};
