const addon = require('./build/Release/addon');

var DirectoryObject = new addon.DirectorywrapAsynchro("http://localhost:8081", "C:/Users/user/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");

if (DirectoryObject) {
	
	console.log(DirectoryObject);
	
	DirectoryObject.GetUserwrapAsynchro("Mohammed", "12345678", function (err, response)
    {
		if(err)
        {console.console(err);}	
        else
        {
			
			var UserWrap = response;
           
            console.log(UserWrap);
			
				//Getname user
			 UserWrap.GetNameAsynchro(function (err, response) 
			 {
                    if (err)
                    { console.console(err); }
                    else
                    {
                        console.log("\n \n Username :" + response);
                    }

             });
			 
			 
			 //Get Session after login
			 
			  DirectoryObject.LogInAsynchro(UserWrap, function (err, response)
             {
                    if (err)
                    { console.console(err); }
                    else
                    {
                        var SessionObject = response;
						
						console.log(SessionObject);
                        if (SessionObject != null)
                        {
                            ////
							
							SessionObject.IsValidAsynchro(function (err, response)
							{
								
								if(err)
								{
									console.log(err);
								}
								else
								{
									var IsValidAsynchrologin=response;
									
									SessionObject.GetWASIDAsynchro(function (err, response)
									{
										if(err)
										{
											console.log(err);
										}
										else
										{
											
											var GetWASIDAsynchrologin=response;
											
											
											
											SessionObject.GetUserwrapAsynchro(function (err, response){
												if(err)
												{
													console.log(err);
												}
												else
												{
													var UserwrapAsynchrologin=response;
													
													 UserwrapAsynchrologin.GetNameAsynchro(function (err, response) 
													{
													if (err)
													{ console.console(err); }
													else
														{
															
														var NameAsynchrologin=response;
																
														console.log("State :"+IsValidAsynchrologin+" WSID :"+GetWASIDAsynchrologin+" Username "+NameAsynchrologin);
														
														SessionObject.LogOutAsynchro(function (err, response){
															if(err)
															{
																console.log(err);
															}
															else
															{
															   SessionObject.IsValidAsynchro(function (err, response){
																   if(err)
																   {
																	   console.log(err);
																   }
																   else
																   {
																	   console.log("State Session after logout :"+response);
																   }
																   
																   
															   });
															}
															
															
														});
														}

													});
													
													
												}
												
												
											});
											
										}
										
										
									});
									
									SessionObject.GetDirectorywrapAsynchro(function (err, response) {
										if(err)
										{
											
											
										}
										else
										{
											var Directorywrapclone=response;
											
											if(Directorywrapclone!=null)
											{
												if(DirectoryObject==Directorywrapclone)
												{
													console.log("Clone works");
													
												}
												else
												{
													console.log("clone don't work");
												}
												
											}
											
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