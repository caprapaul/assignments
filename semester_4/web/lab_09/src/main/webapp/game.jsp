<%@ page import="model.Board" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta http-equiv="refresh" content="1" />
    <style>
        .cell {
            width: 100px;
            height: 100px;
            border-style: solid;
            display: flex;
            justify-content: center;
            align-items: center;
            float: left;
        }

        #game {
            width: 430px;
            height: 430px;
            margin: 0 auto;
            overflow: hidden;
        }

        #status {
            font-weight: bold;
            font-size: 30px;
            margin-left: 30px;
        }
    </style>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script>
        $(() => {
            var values = [];
            var size = { x: 3, y: 3 };

            init(values, size);
            console.log(${board});
        });

        function posToId(x, y, size) {
            return x + size.x * y;
        }

        function init(values, size) {
            $("#game").width(110 * size.x)
                .height(110 * size.y);

            for (j = 0; j < size.y; j++) {
                for (i = 0; i < size.x; i++) {
                    const id = posToId(i, j, size);

                    var cell = $("<div></div>")
                        .attr({
                            id: id,
                            class: "cell"
                        })
                        .text("");


                    values.push(cell);
                }
            }

            values[0].text(" ");

            //console.log(empty);
            showGame(values);
        }

        function showGame(values) {
            $("#game").html("");
            var board = ${board};
            var winner = "${winner}";

            for (let i = 0; i < values.length; i++) {

                var text = board[i] == 0 ? "O" : board[i] == 1 ? "X" : "";

                values[i].text(text);

                values[i].on("click", function () {
                    $.post(
                        "game?cell=" + i,
                        () => location.reload()
                    );
                });

                $("#game").append(values[i]);
            }

            if (winner != "null") {
                var winner_type = ${winner_type};
                var type = winner_type == 0 ? "O" : winner_type == 1 ? "X" : "";
                $("#status").text("Winner: " + winner);
            }
        }
    </script>
    <title>TicTacToe</title>
</head>
<body>
<div id="game">
</div>

</br>
<p id="status">
</p>

</body>
</html>
