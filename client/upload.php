<?php
header('Access-Control-Allow-Origin: *');
$data = array();

if(isset($_GET['image']))
{  
    $error = false;
    $files = array();
    
    $dossier = 'images/';
    foreach($_FILES as $file)
    {
          $fichier = basename($file['name']);
          $taille = filesize($file['tmp_name']);
          $extensions = array('.png', '.tiff', '.jpg', '.jpeg');
          $extension = strrchr($file['name'], '.'); 
          $taille_maxi = 52428800;

          if(!in_array($extension, $extensions)) 
          {
               $data = ($error) ? array('error' => 'Only JPG, JPEG, PNG & TIFF files are allowed.') : array('files' => $files);
          }
          if($taille>$taille_maxi)
          {
               $data = ($error) ? array('error' => 'Your image is too large.') : array('files' => $files);
          }
          if(!isset($erreur)) 
          {    
               $fichier = strtr($fichier, 
               'ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ ', 
               'AAAAAACEEEEIIIIOOOOOUUUUYaaaaaaceeeeiiiioooooouuuuyy_');
               $fichier = preg_replace('/([^.a-z0-9]+)/i', '-', $fichier);

               if(move_uploaded_file($file['tmp_name'], $dossier . $fichier))
               {
                 $files[] = $dossier .$file['name'];
               }
               else
               {
                 $error = true;
               }
          }
    }
    $data = ($error) ? array('error' => 'There was an error uploading your files') : array('files' => $files);
}
else
{
    $data = array('success' => 'Form was submitted', 'formData' => $_POST);
}

echo json_encode($data);
?>
