var session = new Session();


$('#mydropdownmenu > li').click(function(e){
  e.preventDefault();
  var selected = $(this).text();
  $('#mydropwodninput').val(selected);
  $('#mydropdowndisplay').text(selected);
});

//$('#baseline_modal').modal();