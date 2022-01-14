// JavaScript Document

function calculatePrice()
{
	var roomPrice = {superior: 2347, deluxe: 2641, prestige: 8997, presidential: 10953, appartment: 12713};
	var firstName = document.getElementById("firstName").value;
	var lastName = document.getElementById("lastName").value;
	var phoneNumber = document.getElementById("phoneNumber").value;
	var email = document.getElementById("email").value;
	var numberOfNights = document.getElementById("nights").value;
	var numberOfPeople = document.getElementById("visitors").value;
	var typeOfRoom = document.getElementById("rooms").value;
	var finalPrice;
	var errorMessage;
	var result;
	if(firstName == "")
	{
		finalPrice = document.getElementById("finalPrice");
		while(finalPrice.firstChild)
		{
			finalPrice.removeChild(finalPrice.firstChild);
		}
		errorMessage = document.createTextNode("Не сте попълнили полето за име!");
		finalPrice.appendChild(errorMessage);
			
	}
	else if(lastName == "")
	{
		finalPrice = document.getElementById("finalPrice");
		while(finalPrice.firstChild)
		{
			finalPrice.removeChild(finalPrice.firstChild);
		}
		errorMessage = document.createTextNode("Не сте попълнили полето за фамилия!");
		finalPrice.appendChild(errorMessage);
			
	}
	else if (isNaN(phoneNumber) || phoneNumber == "")
	{
		finalPrice = document.getElementById("finalPrice");
		while(finalPrice.firstChild)
		{
			finalPrice.removeChild(finalPrice.firstChild);
		}
		errorMessage = document.createTextNode("Невалиден телефонен номер!");
		finalPrice.appendChild(errorMessage);
			
	}
	else if(email == "" || !email.includes("@"))
	{
		finalPrice = document.getElementById("finalPrice");
		while(finalPrice.firstChild)
		{
			finalPrice.removeChild(finalPrice.firstChild);
		}
		errorMessage = document.createTextNode("Невалиден имейл!");
		finalPrice.appendChild(errorMessage);
			
	}
	else if(isNaN(numberOfNights) || numberOfNights == "")
	{
		finalPrice = document.getElementById("finalPrice");
		while(finalPrice.firstChild)
		{
			finalPrice.removeChild(finalPrice.firstChild);
		}
		errorMessage = document.createTextNode("Не сте избрали брой нощувки!");
		finalPrice.appendChild(errorMessage);
	}
	else if(isNaN(numberOfPeople) || numberOfPeople == "")
	{
		finalPrice = document.getElementById("finalPrice");
		while(finalPrice.firstChild)
		{
			finalPrice.removeChild(finalPrice.firstChild);	
		}
		errorMessage = document.createTextNode("Не сте избрали брой посетители!")
		finalPrice.appendChild(errorMessage);
	}
	else
	{
		finalPrice = document.getElementById("finalPrice")
		while(finalPrice.firstChild)
		{
			finalPrice.removeChild(finalPrice.firstChild);
		}
		if(numberOfPeople > 2)
		{
			switch(typeOfRoom)
			{
				case "superior":
				{
					result = document.createTextNode(roomPrice.superior*Math.ceil(numberOfPeople/2)*numberOfNights);
					break;
				}
				case "deluxe":
				{
					result = document.createTextNode(roomPrice.deluxe*Math.ceil(numberOfPeople/2)*numberOfNights);
					break;	
				}
				case "prestige":
				{
					result = document.createTextNode(roomPrice.prestige*Math.ceil(numberOfPeople/2)*numberOfNights);
					break;
				}
				case "presidential":
				{
					result  = document.createTextNode(roomPrice.presidential*Math.ceil(numberOfPeople/2)*numberOfNights);
					break;	
				}
				case "apartment":
				{
					result = document.createTextNode(roomPrice.appartment*Math.ceil(numberOfPeople/2)*numberOfNights);
					break;	
				}
			}
			finalPrice.appendChild(result);
		}
		else
		{			
			switch(typeOfRoom)
			{
				case "superior":
				{
					result = document.createTextNode(roomPrice.superior*numberOfNights);
					break;
				}
				case "deluxe":
				{
					result = document.createTextNode(roomPrice.deluxe*numberOfNights);
					break;	
				}
				case "prestige":
				{
					result = document.createTextNode(roomPrice.prestige*numberOfNights);
					break;
				}
				case "presidential":
				{
					result  = document.createTextNode(roomPrice.presidential*numberOfNights);
					break;	
				}
				case "apartment":
				{
					result = document.createTextNode(roomPrice.appartment*numberOfNights);
					break;	
				}
			}
			
			finalPrice.appendChild(result);
			document.getElementById('hidden').style.display = 'block';
		}
	}
}