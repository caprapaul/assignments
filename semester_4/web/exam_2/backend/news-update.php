<?php
    require 'connection.php';

    $id = $_POST["id"];
    $text = $_POST["text"];
    $title = $_POST["title"];
    $producer = $_POST["producer"];
    $date = $_POST["date"];
    $category = $_POST["category"];

    $sql_id = "SELECT * FROM news WHERE id=?";
    $stmt_id = $connection->prepare($sql_id);
    $stmt_id->bind_param("i", $id);
    $stmt_id->execute();
    $stmt_id->store_result();
    $rows = $stmt_id->num_rows;
    $stmt_id->close();


    if ($rows > 0) {
        $sql = "UPDATE news SET text=?, title=?, producer=?, date=?, category=? WHERE id=?";

        $stmt = $connection->prepare($sql);
        $stmt->bind_param("sssssi", $text, $title, $producer, $date, $category, $id);
        
        $stmt->execute();
        $stmt->close();
    }
?>

