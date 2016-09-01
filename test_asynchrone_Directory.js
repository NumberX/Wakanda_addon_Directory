const addon = require('./build/Release/addon');

var DirectoryObject = new addon.DirectorywrapAsynchro("http://localhost:8081", "C:/Users/user/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");

if (DirectoryObject) {
	
	console.log(DirectoryObject);
	
	DirectoryObject.GetGroupwrapNamesAsynchro(function (err, response)
	{
		if (err)
		{ console.console(err); }
		else
		{
			var VectorNameGroup=response;
													
			DirectoryObject.GetGroupwrapIDAsynchro(function (err, response)
			{
			if (err)
			{ console.console(err); }
			else
			{
			 var VectorIdGroup=response;
																	
				console.log("\n Teste GetGroupwrapID  GetGroupwrapName \n");
				for(Iterator in VectorIdGroup)
				{
					console.log("\n Group["+Iterator+"] Name: "+VectorNameGroup[Iterator]+"  Id : "+VectorIdGroup[Iterator]);
				}
			}
														
			});
		}
												
	});
	
	///Test GetUserwrap
	
	DirectoryObject.GetUserwrapAsynchro("Mohammed", "12345678", function (err, response)
    {
		if(err)
        {console.console(err);}	
        else
        {
			var UserWrap = response;
           
            
			
			if (UserWrap != null) 
			{
				//Getname user
			 UserWrap.GetNameAsynchro(function (err, response) 
			 {
                    if (err)
                    { console.console(err); }
                    else
                    {
                        var UserWrapName=response;
						
						DirectoryObject.LogInAsynchro(UserWrap, function (err, response)
						{
						if (err)
						{ console.console(err); }
						else
						{
                         var SessionObject = response;
						
						
                         if (SessionObject != null)
                         {
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
						
											
											console.log(UserWrap);
											
											console.log(SessionObject);
						
											console.log("\n \n Username :" + UserWrapName +" State :"+IsValidAsynchrologin+" Wsid :"+GetWASIDAsynchrologin);
										
											DirectoryObject.GetSessionwrapAsynchro(GetWASIDAsynchrologin,function (err, response){
												if(err)
												{
													console.log(err)
												}
												else
												{
													var SessionObjectclone=response;
													
													if (SessionObjectclone != null)
													{
														SessionObjectclone.IsValidAsynchro(function (err, response)
														{
								
															if(err)
															{
																console.log(err);
															}
															else
															{
																var IsValidAsynchrologinclone=response;
									
																SessionObjectclone.GetWASIDAsynchro(function (err, response){
																	if(err)
																	{
																		console.log(err);
																	}
																	else
																	{
																		GetWASIDAsynchrologinclone=response;
																		
																		console.log(" \n \n state clone :"+IsValidAsynchrologinclone+" Wsid clone :"+GetWASIDAsynchrologinclone);
																		
																		DirectoryObject.LogOutAsynchro(SessionObjectclone,function (err, response){
																			if(err)
																			{
																				console.log(err);
																			}
																			else
																			{
																				
																				SessionObjectclone.IsValidAsynchro(function (err, response)
																				{		
								
																					if(err)
																					{
																						console.log(err);
																					}
																					else
																					{
																						var IsValidAsynchrologoutclone=response;
																						
																						console.log(" \n \n State Session clone after clone :"+IsValidAsynchrologoutclone);
																						
																						SessionObject.IsValidAsynchro(function (err, response)
																						{
																							if(err)
																							{
																								console.log(err);
																							}
																							else
																							{
																								IsValidAsynchrologout=response;
																								console.log("\n \n State SessionObject after logout SessionObjectclone :"+IsValidAsynchrologout);
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
													}
												}
												
												
												
											});
										
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
		}
	});
DirectoryObject.GetUserwrapAsynchro("Mohammed", "12345678", function (err, response)
{
	if(err)
    {console.console(err);}	
    else
    {
		var UserGrouptest=response;
	if(UserGrouptest)
	{
	DirectoryObject.LogInAsynchro(UserGrouptest, function (err, response)
    {
	if(err)
	{console.log(err);}
	else
	{
		var SessionGrouptest=response;
	//	
    UserGrouptest.GetNameAsynchro(function (err, response) 
	{
		if(err)
		{console.log(err);}
	    else
		{
			var UserGrouptestname=response; 
	///Test GetGroupwrap
	DirectoryObject.GetGroupwrapNamesAsynchro(function (err, response)
	{
		
		if (err)
		{ console.console(err); }
		else
			{
			 var VectorNameGroup=response;
													
			 DirectoryObject.GetGroupwrapIDAsynchro(function (err, response)
			{
				if (err)
					{ console.console(err); }
				else
					{
					 var VectorIdGroup12=response;
				      if(VectorIdGroup12)
					  {
					 for (Iterator13 in VectorIdGroup12)
					 {
						var Itaratorboucle=Iterator13;

					 
					    DirectoryObject.UserwrapBelongToAsynchro(UserGrouptest, VectorIdGroup12[Iterator13],function(err,response)
						{
							if(err)
							{
								console.log(err);
							}
							else
							{
								var Belong1=response;
								
								
							   DirectoryObject.UserwrapBelongToAsynchro(SessionGrouptest, VectorIdGroup12[Iterator13],function(err,response)
								{
									if(err)
									{
										console.log(err);
									}
									else
									{
										var Belong2=response;
								        
										DirectoryObject.GetGroupwrapAsynchro(VectorIdGroup12[Iterator13],function (err, response){
										if(err)
										{
											console.log(err);
										}
										else
										{
											var GroupObjecttest12=response;
											
											if(GroupObjecttest12)
											{
												
												DirectoryObject.UserwrapBelongToAsynchro(UserGrouptest, GroupObjecttest12,function(err,response)
												{
													if(err)
													{
														console.log(err);
													}
													else
													{
														var Belong3=response;
															console.log("\n \n Methode 1 Id :"+VectorIdGroup12[Iterator13]+" Username :"+UserGrouptestname+"State :"+Belong1);
							
															console.log("\n \n Methode 2 Id :"+VectorIdGroup12[Iterator13]+" Username :"+UserGrouptestname+"State :"+Belong2);
							
							                                console.log("\n \n Methode 3 Id :"+VectorIdGroup12[Iterator13]+" Username :"+UserGrouptestname+"State :"+Belong3);
							
														
													}
												});		
											}
										}
										});
							
									}
								});
							
							}
							
						}
						)
					 }}
					}
			});
		}
	});
	}});
	}});
	}
	}
})
	}