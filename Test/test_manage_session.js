const addon = require('./../build/Release/addon');

var DirectoryObject=new addon.Directory("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");

//var DirectoryObject1 = new addon.Directorywrap();

if (DirectoryObject) {

    console.log(DirectoryObject);

    //create User

    var UserWrap = DirectoryObject.GetUser("Mohammed", "12345678");
	var UserWrap1 = DirectoryObject.GetUser("Ayoub", "12345678");

    if (UserWrap != null) {
        //Test Functionaliter of UserWrap


         DirectoryObject.LogIn(UserWrap,function(err,response){
			if(err)
			{
				
			}
			else
			{
				console.log("Session");
				var SessionObject =response;

				
				if (SessionObject) 
				{
    
					

					console.log("\n Session Wsid" + SessionObject.GetWASID());
					
					 DirectoryObject.LogIn(UserWrap,function(err,response){
						 if(err)
						 {
							 console.log(err);
						 }
						 else
						 {
							 var SessionObject2=response;
							 UserWrap.IsLoggedIn(function(err,response){
								 if(err)
								 {
									 
								 }
								 else
								 {
									var isloggedin=response;
									 
									console.log("\n User isLoggedIn 2 " + isloggedin);
					
									console.log("\n Session 2 Wsid" + SessionObject2.GetWASID());
									
									DirectoryObject.LogIn(UserWrap1,function(err,response){
										if(err)
										{
											console.log(err);
										}
										else
										{
											var SessionObject1 =response;

											if (SessionObject1) {

											 UserWrap1.IsLoggedIn(function(err,response){
												if(err)
												{
													console.log(err);
												}
												else
												{
											       console.log("\n User isLoggedIn " +	response);	

											       console.log("\n Session 1 Wsid" + SessionObject1.GetWASID());
												   
												   DirectoryObject.LogOut();
												   
												   console.log("Userbelong");
												   
												   
												   DirectoryObject.UserBelongTo(SessionObject2,"1BB0E9B628EAF843AFBE9531D3C982C5",function(err,response)
												   {
													   if(err)
													   {
														   console.log(err);
													   }
													   else
													   {
														   Resultat=response;
														   
														   console.log("\n User isBelong to " +	response+"Name :" +UserWrap.GetName());	
														   
													   }
													   
													   
												   });
												 }
												
												
											});

											}
											
										}
										
										
										
									});
		

								 }
								 
								 
							 });
						 }
						 
						 
					 })
			}
			}				
			
		});


		
		
		
	}
	
	
/*	  if (UserWrap1 != null) {
        //Test Functionaliter of UserWrap


        var SessionObject = DirectoryObject.LogIn(UserWrap1);


        if (SessionObject) {
            //Obtain Session from login withn argument User
           
            //test User.IsLoggedIn(const v8::FunctionCallbackInfo<v8::Value>& args);


            console.log("\n User isLoggedIn " + UserWrap.IsLoggedIn(SessionObject));

            console.log("\n Session Wsid" + SessionObject.GetWASID());

            //deconnectes  Session
			
			SessionObject.LogOut();

		}
	  }
*/

}