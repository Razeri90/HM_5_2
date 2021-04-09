Action1()
{
	/* Itinerary */
	
	//Цена 3-х билетов
	web_reg_save_param_ex(
    	"ParamName=TotalCost", 
    	"LB/IC=Total Charge: $ ", 				//Ограничение слева
    	"RB/IC= <BR/>",							//Ограничение справа
    	"Ordinal=All", 							//Какое значение взять
	LAST); 
		

	web_url("Itinerary Button", 
		"URL={Host}/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={Host}/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	
		//Вывод цены 3 х билетов
	lr_output_message("Price ticket 1=%d",atoi(lr_eval_string("{TotalCost_1}")));
	lr_output_message("Price ticket 2=%d",atoi(lr_eval_string("{TotalCost_2}")));
	lr_output_message("Price ticket 3=%d",atoi(lr_eval_string("{TotalCost_3}")));
	
	
	if((atoi(lr_eval_string("{TotalCost_1}"))<atoi(lr_eval_string("{TotalCost_2}"))) && (atoi(lr_eval_string("{TotalCost_2}"))<atoi(lr_eval_string("{TotalCost_3}")))){
		min=atoi(lr_eval_string("{TotalCost_1}"));
		lr_save_string("1","flightcount");   //Сохранение в переменную flightnum значение 1. Для подстановки в web_submit_form
	}
	if((atoi(lr_eval_string("{TotalCost_2}"))<atoi(lr_eval_string("{TotalCost_1}"))) && (atoi(lr_eval_string("{TotalCost_2}"))<atoi(lr_eval_string("{TotalCost_3}")))){
		min=atoi(lr_eval_string("{TotalCost_2}"));
		lr_save_string("2","flightcount");
	}
	if((atoi(lr_eval_string("{TotalCost_3}"))<atoi(lr_eval_string("{TotalCost_1}"))) && (atoi(lr_eval_string("{TotalCost_3}"))<atoi(lr_eval_string("{TotalCost_2}")))){
		min=atoi(lr_eval_string("{TotalCost_3}"));
		lr_save_string("3","flightcount");
	}
	
	lr_output_message("Minimum=%d",min);
	
	/* cancel flight */
	
	//Запрос на отмену
	web_submit_form("itinerary.pl",ITEMDATA,
       "Name={flightcount}", "Value=on",ENDITEM,          //Постановка значения       
       "Name=removeFlights.x","Value=36",ENDITEM,
       "Name=removeFlights.y","Value=5",ENDITEM,
       LAST);
	

	web_submit_data("itinerary.pl", 
		"Action=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=2", "Value=on", ENDITEM, 
		"Name=flightID", "Value={flightID}", ENDITEM, 
		"Name=flightID", "Value={flightID}", ENDITEM, 
		"Name=.cgifields", "Value=1", ENDITEM, 
		"Name=.cgifields", "Value=2", ENDITEM, 
		"Name=removeFlights.x", "Value=34", ENDITEM, 
		"Name=removeFlights.y", "Value=11", ENDITEM, 
		LAST);
		
	return 0;
}