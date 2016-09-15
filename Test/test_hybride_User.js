const addon = require('./../build/Release/addon');
var DirectoryObject=new addon.Directory("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");

if (DirectoryObject) {

    console.log(DirectoryObject);
	
	var UserWrap =DirectoryObject.GetUser("Mohammed", "12345678");
		   
	console.log(UserWrap);	

	if (UserWrap != null) {
        //Test Functionaliter of UserWrap


        DirectoryObject.LogIn(UserWrap,function(err,response){
			
			if(err)
			{
				console.log(err);
			}
			else
			{
				var SessionObject=response;
				
				console.log(SessionObject);
				
				console.log("\n Session Wsid" + SessionObject.GetWASID());
				
				UserWrap.IsLoggedIn(function(err,response){
					
					if(err)
					{
						console.log(err);
					}
					else
					{
						var statelogged=response;
						
						console.log("\n User isLoggedIn " + statelogged);

						console.log("\n Session Wsid" + SessionObject.GetWASID());
						
						 //deconnectes  Session

						SessionObject.LogOut();
						
						SessionObject.IsValid(function(err,response)
						{
						if(err)
						{
							console.log(err);
						}							
						else
						{
						var Uservalid=response;
						
						UserWrap.IsLoggedIn(SessionObject,function(err,response){
							
						if(err)
						{
							console.log(err);
						}
						else
						{
							
							console.log("\n Session Wsid after logout" + SessionObject.GetWASID());
							
							console.log("\n Session is valid after logout"+Uservalid);
							
							console.log("\n User isLoggedIn after logout " +response);
							
							DirectoryObject.LogIn(UserWrap,function(err,response)
							{
							if(err)
							{
								console.log(err);
							}
							else{
							
							var SessionObject1 =response;
							
							//Test Get Directory
							
							var DirectoryObjectclone = UserWrap.GetDirectory();

							if (DirectoryObjectclone == DirectoryObject) {

							console.log("\n The clone Work");
							
							if (DirectoryObjectclone) {

							var VectorNameGroup = DirectoryObjectclone.GetGroupsNames();

							var VectorIdGroup = DirectoryObjectclone.GetGroupsID();
							
							 console.log("\n Testes Belongto");

                             console.log("\n Testes des appartenance de user a tous les group ID");
                             var Iterator=0;
							
							for (Iterator in VectorIdGroup) {

                           
						    
							console.log(Iterator);
							UserWrap.BelongsToGroup(VectorIdGroup[Iterator],function(err,response){
								
								if(err)
								{
									
								}
								else
								{
									console.log("\n Group 1 [" + Iterator + "]: ID :" + VectorIdGroup[Iterator]);
									
									console.log("\n Username :" + UserWrap.GetName() + " Etat :" +response);
									
								
								}
								
							})
							
							
							}
							
							console.log("\n Testes des appartenance de user a tous les groupwrap");
							
							for (Iterator in VectorIdGroup) {

                               var GroupwrapObject = DirectoryObjectclone.GetGroup(VectorIdGroup[Iterator]);
							   if (GroupwrapObject) {
                               UserWrap.BelongsToGroup(GroupwrapObject,function(err,response){
								   
								   if(err)
								   {
									   
								   }
								   else
								   {
									      console.log("\n Name: " + GroupwrapObject.GetName());

									      console.log("\n Username :" + UserWrap.GetName() + " Etat :" + response);

								   }
								   
								   
								   
							})};
							}
							}
							}
							}
							
							})
						}
							
						})	
						}
							
						}
						);
						
					}
					
					
				});
			}
			
			
			
		});
	}	

}