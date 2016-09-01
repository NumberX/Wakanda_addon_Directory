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
			
			if (UserWrap != null) 
			{
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
                            UserWrap.IsLoggedInAsynchro(SessionObject, function (err, response) {

                                if (err)
                                { console.console(err); }
                                else
                                {
                                    console.log("\n User isLoggedIn " + response+"\n");

                                }


                            });
							
							
							SessionObject.GetWASIDAsynchro(function (err, response) {
                              if (err) 
							  {
                                 console.console(err);
                              }
                              else 
								{
                                    console.log("\n \n User WSID Session " + response+"\n");

                                    
								}
                              });
							  
							  
							SessionObject.IsValidAsynchro( function (err, response) 
							{

                                        if (err)
                                        { console.console(err); }
                                        else
                                        {
                                            
                                            console.log("\n Session is valid after logout  " + response+"\n");

                                        }

                            });
							
							
							SessionObject.LogOutAsynchro(function (err, response) {
                                if (err) {
                                    console.console(err);
                                }
                                else 
								{
                                    console.log("\n Logout  \n");
									
									
									SessionObject.IsValidAsynchro( function (err, response) 
									{

                                        if (err)
                                        { console.console(err); }
                                        else
                                        {
                                            
                                            console.log("\n Session is valid before logout  " + response+"\n");

                                        }

									});
									
									SessionObject.GetWASIDAsynchro(function (err, response) {
									if (err) 
									{
										console.console(err);
									}
                              
									else 
									{
										
                                    console.log("\n \n User WSID Session after Logout " + response+ "\n");

                                    
									}
									});
								
								}	
							});
							
							
						}
						
					}
			 });
			
			
			 DirectoryObject.LogInAsynchro(UserWrap, function (err, response)
             {
                    if (err)
                    { console.console(err); }
                    else
                    {
						var SessionObject1=response;
						if(SessionObject1!=null)
						{
							console.log("SessionObject1"+SessionObject1);
							UserWrap.GetDirectorywrapAsynchro(function (err, response)
							{
								if (err)
									{ console.console(err); }
								else
								{
									var DirectoryObjectclone=response;
									 if (DirectoryObjectclone == DirectoryObject) 
									 {

										console.log("\n The clone Work");
										 if (DirectoryObjectclone) {
											 DirectoryObjectclone.GetGroupwrapNamesAsynchro(function (err, response)
											 {
												if (err)
													{ console.console(err); }
												else
												{
													var VectorNameGroup=response;
													
													DirectoryObjectclone.GetGroupwrapIDAsynchro(function (err, response)
													{
														if (err)
														{ console.console(err); }
														else
														{
															var VectorIdGroup=response;
															
															
															UserWrap.GetNameAsynchro(function (err, response){
																
																if (err)
																{ console.console(err); }
																else
																{
																	var nameuser=response;
																	console.log("\n Testes des appartenance de user a tous les group ID");
																	for (Iterator in VectorNameGroup) {
																		
																		UserWrap.BelongsToGroupwrapAsynchro(VectorIdGroup[Iterator],function (err, response)
																		{
																			if(err)
																			{
																				console.log(err);
																			}
																		    else{
																				var etat=response;
																				console.log("\n GroupNames [" + Iterator + "]: Names :" + VectorNameGroup[Iterator]);
																				console.log("\n GroupId [" + Iterator + "]: Names :" + VectorIdGroup[Iterator]);
																				console.log("\n names User :"+nameuser+" Etat :"+etat);
																				
																				
																			}
																			
																		});
																		
																		DirectoryObjectclone.GetGroupwrapAsynchro(VectorIdGroup[Iterator],function (err, response){
																			if(err)
																			{
																				console.log(err);
																			}
																		    else{
																				
																				var GroupwrapObject=response;
																				if(GroupwrapObject)
																				{
																					GroupwrapObject.GetNameAsynchro(function (err, response){
																						
																						if(err)
																						{
																							console.log(err);
																						}
																						else{
																							GroupwrapObjectname=response;
																							UserWrap.BelongsToGroupwrapAsynchro(GroupwrapObject,function (err, response)
																							{
																								if(err)
																								{
																									console.log(err);
																								}
																								else{
																									var etat1=response;
																									console.log("\n GroupNames methode 2 [" + Iterator + "]: Names :" + GroupwrapObjectname);
																									console.log("\n GroupId methode 2[" + Iterator + "]: Names :" + VectorIdGroup[Iterator]);
																									console.log("\n names User methode 2 :"+nameuser+" Etat :"+etat1);
																				
																				
																									}
																			
																							});
																							
																							
																						}
																						
																						
																					});
																					
																					
																				}
																				
																			}
																			
																			
																			
																		});

																	
																	}
																}
																
															});
															
														}
														
													}
													);
													
													
												}
												 
												 
												 
											 })
										 
										 
										 
										 }
									 }
								
								
								}
								
								
								
							});
							
						}
						
					}
			 });
			
			
			
			
			}
		
		
		
		
		}
		
	})
	
	
	}