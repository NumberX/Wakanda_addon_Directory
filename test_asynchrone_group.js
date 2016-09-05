const addon = require('./build/Release/addon');

var DirectoryObject = new addon.DirectorywrapAsynchro("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");

if (DirectoryObject) {
	
	console.log(DirectoryObject);
	
	DirectoryObject.GetGroupwrapNamesAsynchro(function (err, response)
	{
		if (err)
		{ console.console(err); }
		else
		{
			
			var VectorNameGroup=response;
			
				console.log("test");
				
			DirectoryObject.GetGroupwrapIDAsynchro(function (err, response)
			{
				if (err)
				{ console.console(err); }
				else
				{
				var VectorIdGroup=response;
				
					for (Iterator in VectorIdGroup)
					{
						DirectoryObject.GetGroupwrapAsynchro(VectorIdGroup[Iterator],function (err, response){
							if(err)
							{
								console.log(err);
							}
							else
							{
								var GroupObject=response;
								if(GroupObject)
								{
									GroupObject.GetNameAsynchro(function (err, response){
										
										if(err)
										{
											console.log(err);
										}
										else
										{
											var GroupObjectname=response;
											GroupObject.GetSubGroupwrapNameAsynchro(function (err, response){
												if(err)
												{
													console.log(err);
												}
												else
												{
													var VectorsubGroup=response
												    
													console.log("Group["+Iterator+"] name :"+ VectorNameGroup[Iterator]+" ID :"+ VectorIdGroup[Iterator])
													
													for(Iteratorsub in VectorsubGroup)
													{
													console.log("\n Subgroup[" + Iteratorsub + "] :" + VectorsubGroup[Iteratorsub] + "\n");	
													}
													
												}
												
												
												
											});
											
										}
										
										
									})
									
								}
								
							}
							
						})
					
					}
					}
			});
		}
	});
	
	DirectoryObject.GetGroupwrapAsynchro("04AE851D785A2043AF2AFC0B209A3316",function (err, response){
		
		if(err)
		{console.log(err)}
		else{
			console.log("True");
			var GroupObject=response;
			
			if(GroupObject)
			{
				GroupObject.GetNameAsynchro(function (err, response){
					
					if(err)
					{
						console.log(err);
					}
					else{
						
						var GroupObjectName=response;
						console.log("Name group"+GroupObjectName)
						GroupObject.GetDirectorywrapAsynchro(function (err, response){
							if(err)
							{console.log(err);}
							else
							{
								var DirectoryObjectclone=response;
								if(DirectoryObjectclone==DirectoryObject)
								{
									console.log("Clone work Directory Group"+GroupObjectName);
									
								}
							}
							
						})
					}
					
				})
				
				
				GroupObject.GetUserwrapByNameAsynchro("Mohammed", "12345678",function (err, response){
					
					if(err)
					{console.log(err);}
					else
					{
						
						var UserObject12=response;
						if(UserObject12)
						{
							console.log(UserObject12);
							UserObject12.GetNameAsynchro(function (err, response){
								
								if(err)
								{console.log(err)}
								else
								{
									var UserObjectName1=response;
									
									console.log(UserObjectName1);
								}
								
								
							});
							
						}
						
					}
					
					
					
				});
				
				
			}
			
		}
		
		
	})
	
}