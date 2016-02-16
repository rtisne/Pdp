$(function() {
    $("#canvas").hide();
    $('.loader').hide();
});

$('#mydropdownmenu > li').click(function(e){
  e.preventDefault();
  var selected = $(this).text();
  $('#mydropwodninput').val(selected);
  $('#mydropdowndisplay').text(selected);
});