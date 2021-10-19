<?php
    require 'connection.php';

    $text = $_POST["text"];
    $title = $_POST["title"];
    $producer = $_POST["producer"];
    $date = $_POST["date"];
    $category = $_POST["category"];

    $sql_id = "SELECT MAX(id)+1 id FROM news";
    $id = $connection->query($sql_id)->fetch_assoc()["id"];

    $sql = "INSERT INTO news (id, text, title, producer, date, category) VALUES(?, ?, ?, ?, ?, ?)";

    $stmt = $connection->prepare($sql);

    $stmt->bind_param("isssss", $id, $text, $title, $producer, $date, $category);
    
    $stmt->execute();
    $stmt->close();
?>

