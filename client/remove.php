<?php
if(isset($_GET['restart']))
{  
  $fichier = $_POST['file'];
  $chemindudossier = dirname($fichier);
  $nomdudossier = basename ($chemindudossier);
  $nomdufichier = basename ($fichier);
  $slash = "/";

  $cheminRelatif = $nomdudossier.$slash.$nomdufichier;

  if(unlink($cheminRelatif))
  {
    $fichier = true;
  }
  else
  {
    $fichier = false; 
  }
}

echo json_encode($fichier);
?>
