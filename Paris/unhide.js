// JavaScript Document
function unhide(event)
{
	event.preventDefault();

	if(document.getElementById("secondForm").style.display === "none")
	{
		document.getElementById("firstForm").style.display = "none";
		document.getElementById("secondForm").style.display = "block";	
	}
}
