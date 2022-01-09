// JavaScript Document
function getRoomType()
{
	var select = document.getElementById('rooms');
	return select.options[select.selectedIndex].value;
}
