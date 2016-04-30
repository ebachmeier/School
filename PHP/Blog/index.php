<?php require('includes/config.php'); ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>Blog</title>
    <link rel="stylesheet" href="style/normalize.css">
    <link rel="stylesheet" href="style/main.css">
</head>
<body>

	<div id="wrapper">

		<h1>Blog</h1>
        <ul id='adminmenu'><li>&nbsp;</li></ul>
        <div class='clear'></div>
        <hr />
        
        <div id='main'>

            <?php
			try {
                
                //instantiate the class
                $pages = new Paginator('4','p');

                //collect all records fro the next function
                $stmt = $db->query('SELECT postID FROM blog_posts');

                //determine the total number of records
                $pages->set_total($stmt->rowCount());

				$stmt = $db->query('SELECT postID, postTitle, postSlug, postDesc, postDate FROM blog_posts ORDER BY postID DESC '.$pages->get_limit());
                
				while($row = $stmt->fetch()){
                    
					echo '<div>';
						echo '<h1><a href="'.$row['postSlug'].'">'.$row['postTitle'].'</a></h1>';
						echo '<p>Posted on '.date('F jS, Y', strtotime($row['postDate'])).' at '.date('g:ia', strtotime($row['postDate'])).' in ';
                    
							$stmt2 = $db->prepare('SELECT catTitle, catSlug	FROM blog_cats, blog_post_cats WHERE blog_cats.catID = blog_post_cats.catID AND blog_post_cats.postID = :postID');
							$stmt2->execute(array(':postID' => $row['postID']));

							$catRow = $stmt2->fetchAll(PDO::FETCH_ASSOC);

							$links = array();
							foreach ($catRow as $cat)
							{
							    $links[] = "<a href='c-".$cat['catSlug']."'>".$cat['catTitle']."</a>";
							}
							echo implode(", ", $links);

						echo '</p>';
						echo '<p>'.$row['postDesc'].'</p>';				
						echo '<p><a href="'.$row['postSlug'].'">Read More</a></p>';				
					echo '</div>';

				}
                
                echo $pages->page_links();

			} catch(PDOException $e) {
			    echo $e->getMessage();
			}
		?>

        </div>

        <div id='sidebar'>
            <?php require('includes/sidebar.php'); ?>
        </div>
	</div>
</body>
</html>