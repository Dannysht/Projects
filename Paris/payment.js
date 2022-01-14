// JavaScript Document

function payment()
{
	var successMessage;
	var errorMessage;
	var name = document.getElementById("fullName").value;
	var cardNumber = document.getElementById("cardNumber").value;
	var date = new Date(document.getElementById("expirationDate").value);
	var today = new Date();
	document.getElementById("success").style.display = 'block';
	if(name == "" || !name.includes(" "))
	{
		successMessage = document.getElementById("success");
		while(successMessage.firstChild)
		{
			successMessage.removeChild(successMessage.firstChild);
		}
		errorMessage = document.createTextNode("Не сте попълнили полето за име!");
		successMessage.appendChild(errorMessage);		
	}
	else if(isNaN(cardNumber) || cardNumber.length < 8 || cardNumber.length > 19)
	{
		successMessage = document.getElementById("success");
		while(successMessage.firstChild)
		{
			successMessage.removeChild(successMessage.firstChild);
		}
		errorMessage = document.createTextNode("Невалиден номер на карта!");
		successMessage.appendChild(errorMessage);	
	}
	else if(date.getFullYear != today.getFullYear)
	{
		successMessage = document.getElementById("success");
		while(successMessage.firstChild)
		{
			successMessage.removeChild(successMessage.firstChild);
		}
		errorMessage = document.createTextNode("Невалидна дата!");
		successMessage.appendChild(errorMessage);
	}
	else
	{
		successMessage = document.getElementById("success");
		while(successMessage.firstChild)
		{
			successMessage.removeChild(successMessage.firstChild);
		}
		errorMessage = document.createTextNode("Успяхте успешно да резервирате стая в хотел Плаза Атене Париж");
		successMessage.appendChild(errorMessage);
	}
}