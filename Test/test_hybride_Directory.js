const addon = require('./../build/Release/addon');
var DirectoryObject=new addon.Directory("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");

    console.log("\n Begin Directory Test \n");

    if (DirectoryObject)
    {
        console.log("\n GetGroupwrapID  \n");
        var VectorGroupIdDir = DirectoryObject.GetGroupsID();

        for(IteratorVec in VectorGroupIdDir)
        {
            console.log("\n Vector[" + IteratorVec + "] :" + VectorGroupIdDir[IteratorVec]);
            

        }

        console.log("\n GetGroupwrapName  \n");
        var VectorGroupNameDir = DirectoryObject.GetGroupsNames();

        for (IteratorVecN in VectorGroupNameDir) 
		{
            console.log("\n Vector[" + IteratorVecN + "] :" + VectorGroupNameDir[IteratorVecN]);


        }

        console.log("\n Test GetUserwrap");

        var UsrDireObject = DirectoryObject.GetUser("Mohammed", "12345678");
        if(UsrDireObject)
        {
            console.log("\n Name :" + UsrDireObject.GetName());

            console.log("\n Test LogIn \n");

            DirectoryObject.LogIn(UsrDireObject,function(err,response){
				
				if(err)
				{
					console.log(err);
				}
				else
				{
					var SessionDirLog=response;
					
					    if(SessionDirLog)
            
						{
							SessionDirLog.IsValid(function(err,response){
								
								if(err)
								{
									console.log(err);
								}
								else
								{
									var Isvalid =response;
									
									console.log("\n Wsid :"+SessionDirLog.GetWASID());

							        var wsid = SessionDirLog.GetWASID();
									
									console.log("\n Isvalid :" +Isvalid); 
									
									DirectoryObject.GetSession(function(err,response){ //DirectoryObject.GetSession(wsid,function(err,response)
										if(err)
										{
											console.log(err);
										}
										else
										{
											SessionDirLogclone =response;
											
											if(SessionDirLogclone)
											{

												console.log("\n WSID clone :"+SessionDirLogclone.GetWASID())

												 SessionDirLog.IsValid(function(err,response){
													if(err)
													{
														console.log(err);
													}
													else
													{
														var Isvalidclone=response;
														
														console.log("\n Etat Valid  clone before logout:" +Isvalidclone);
														
														DirectoryObject.LogOut();//LogOut(SessionDirLog)
														
														 SessionDirLog.IsValid(function(err,response){
															if(err)
															{
																console.log(err);
															}
															else
															{
																IsvalidLogout=response;
																
																console.log("\n Etat Valid  clone after logout:" +IsvalidLogout);
																
															}
															
														});
														
														 SessionDirLog.IsValid(function(err,response){
															
															if(err)
															{
																console.log(err);
															}
															else
															{
																console.log("\n Session valid after logout:" +response);
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

        

        }
        console.log("\n Test GetGroupwrap");

        for (IteratorVec in VectorGroupIdDir)
        {
            var ObjectDirectory = DirectoryObject.GetGroup(VectorGroupIdDir[IteratorVec]);

            console.log("\n Vect[" + IteratorVec + "] : ID :" + VectorGroupIdDir[IteratorVec] + " : Name" + ObjectDirectory.GetName());

        }

        console.log(" \n Test Belong to argument UserWrap and Idgroup \n");
        
        for (IteratorVec in VectorGroupIdDir) {
            var ObjectDirectory = DirectoryObject.GetGroup(VectorGroupIdDir[IteratorVec]);

            
			 
            if (UsrDireObject)
            {
				
                 DirectoryObject.UserBelongTo(UsrDireObject, VectorGroupIdDir[IteratorVec],function(err,response){
					
					if(err)
					{
						console.log(err);
					}
					else
					{
						var Resultat =response;
						
						console.log("\n Vect[" + IteratorVec + "] : ID :" + VectorGroupIdDir[IteratorVec] + " : Name :" + ObjectDirectory.GetName());

						console.log("\n User Name: " + UsrDireObject.GetName() + " Belong to :" + Resultat + "\n");
						
					}
					
				});

				
                


            }


        }


        console.log(" \n Test Belong to argument UserWrap and GroupWrap \n");

        for (IteratorVec in VectorGroupIdDir) {
            var ObjectDirectory = DirectoryObject.GetGroup(VectorGroupIdDir[IteratorVec]);


            if (UsrDireObject) {
				
				
                 DirectoryObject.UserBelongTo(UsrDireObject, ObjectDirectory,function(err,response){
					
					if(err)
					{
						console.log(err);
						
					}
					else
					{
						var Resultat =response;
						
						 console.log("\n Vect[" + IteratorVec + "] : ID :" + VectorGroupIdDir[IteratorVec] + " : Name :" + ObjectDirectory.GetName());

						 console.log("\n User Name: " + UsrDireObject.GetName() + " Belong to :" + Resultat + "\n");
						
						
					}
					
				});

               


            }


        }

        console.log(" \n Test Belong to argument SessionWrap and GroupWrap \n");
        if (UsrDireObject) {

             DirectoryObject.LogIn(UsrDireObject,function(err,response){
				
				if(err)
				{
					console.log(err);
				}
				else
				{
					var SessionObject4 =response;
					
					console.log("\n Wsid :" + SessionObject4.GetWASID()+"\n");

					for (IteratorVec in VectorGroupIdDir) 
					{

						var GroupObjectDirectory = DirectoryObject.GetGroup(VectorGroupIdDir[IteratorVec]);


						DirectoryObject.UserBelongTo( VectorGroupIdDir[IteratorVec],function(err,response){//You can you use UserBelongTo( Sessionobject4,VectorGroupIdDir[IteratorVec],function(err,response)
							
							if(err)
							{
								console.log(err);
							}
							else
							{
								var Resultat = response;
								
								console.log("\n Vect[" + IteratorVec + "] : ID :" + VectorGroupIdDir[IteratorVec] + " : Name :" + GroupObjectDirectory.GetName());

					        	console.log("\n User Name: " + UsrDireObject.GetName() + " Belong to :" + Resultat + "\n");
								
							}
							
						});

						


					}
					
				}
				
			});

        


        }


    }

