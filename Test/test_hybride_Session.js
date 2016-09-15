console.log("\n \n Test Group");

const addon = require('./../build/Release/addon');

var DirectoryObject=new addon.Directory("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");
   

   console.log("\n Begin Session Test \n");

    if(DirectoryObject)
    {
        var UserWrapObject3 = DirectoryObject.GetUser("Mohammed", "12345678");
        if(UserWrapObject3)
        {
            var SessionObject3 = DirectoryObject.LogIn(UserWrapObject3,function(Err,Response)
			{
				if(Err)
				{
					
				}
				else
				{
			
				var SessionObject3= Response;
				
				if(SessionObject3)
				{
                console.log(" \n Session was create \n");

				SessionObject3.IsValid(function(err,response)
				{
					
					if(err)
					{
						
					}
					else
					{
						
						var Statevalid=response;
						
						console.log("\n WSID :" + SessionObject3.GetWASID());
						
						console.log("\n valid :" + Statevalid);
						
						SessionObject3.GetUser(function(err,response){
							
							if(err)
							{
								console.err(err);
							}
							else
							{
								var UserObjectSession=response;
								
								console.log(UserObjectSession);
								
								 if (UserObjectSession)
									{
									
									console.log("\n Username :" + UserObjectSession.GetName());
									}
									
									 console.log("\n Logout :" + SessionObject3.LogOut());
									 
									 SessionObject3.IsValid(function(err,response){
										 
										 if(err)
										 {
											 console.log(err);
										 }
										 else
										 {
											 
											    console.log("\n valid after logout :" + response);
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

    }

    console.log("\n \n End Test Session \n");