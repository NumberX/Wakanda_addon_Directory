const addon = require('./build/Release/addon');

var DirectoryObject=new addon.Directorywrap("http://localhost:8081","C:/Users/user/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");

//var DirectoryObject1 = new addon.Directorywrap();

if (DirectoryObject) {

    console.log(DirectoryObject);

    //create User

    var UserWrap = DirectoryObject.GetUserwrap("Mohammed", "12345678");

    if (UserWrap != null) {
        //Test Functionaliter of UserWrap


        var SessionObject = DirectoryObject.LogIn(UserWrap);


        if (SessionObject) {
            //Obtain Session from login withn argument User

            //test User.IsLoggedIn(const v8::FunctionCallbackInfo<v8::Value>& args);


            console.log("\n User isLoggedIn " + UserWrap.IsLoggedIn(SessionObject));

            console.log("\n Session Wsid" + SessionObject.GetWASID());

            //deconnectes  Session

            SessionObject.LogOut();

            console.log("\n User isLoggedIn " + UserWrap.IsLoggedIn(SessionObject));

            console.log("\n Etat Session"+SessionObject.IsValid());

            console.log("\n Wsid after logout"+SessionObject.GetWASID());

            var SessionObject1 = DirectoryObject.LogIn(UserWrap);

            if (SessionObject1) {
                //Test Get Directory
                var DirectoryObjectclone = UserWrap.GetDirectorywrap();

                if (DirectoryObjectclone == DirectoryObject) {

                    console.log("\n The clone Work");

                    if (DirectoryObjectclone) {

                        var VectorNameGroup = DirectoryObjectclone.GetGroupwrapNames();

                        var VectorIdGroup = DirectoryObjectclone.GetGroupwrapID();

                        console.log("\n Testes Belongto");

                        console.log("\n Testes des appartenance de user a tous les group ID");
                        for (Iterator in VectorIdGroup) {

                            console.log("\n Group [" + Iterator + "]: ID :" + VectorIdGroup[Iterator]);
                            console.log("\n Username :" + UserWrap.GetName() + " Etat :" + UserWrap.BelongsToGroupwrap(VectorIdGroup[Iterator]));
                        }

                        console.log("\n Testes des appartenance de user a tous les groupwrap");

                        for (Iterator in VectorIdGroup) {

                            var GroupwrapObject = DirectoryObjectclone.GetGroupwrap(VectorIdGroup[Iterator]);

                            if (GroupwrapObject) {
                                console.log("\n Name: " + GroupwrapObject.GetName());

                                console.log("\n Username :" + UserWrap.GetName() + " Etat :" + UserWrap.BelongsToGroupwrap(GroupwrapObject));

                            }

                        }

                        console.log("\n Fin Test UserWrap \n ");

                    }

                }

            }


        }
    }

    console.log("\n \n Test Group");

    if (DirectoryObject)
    {

        var VectorNameGroup = DirectoryObject.GetGroupwrapNames();

        var VectorIdGroup21 = DirectoryObject.GetGroupwrapID();

        

       
        for (Iterator in VectorIdGroup21)
        {
            //Testes create group byid;
            var GroupWrapobject1 = DirectoryObject.GetGroupwrap(VectorIdGroup21[Iterator]);
            if (GroupWrapobject1)
            {
                console.log("\n ID :" + VectorIdGroup21[Iterator]);
                //Testes create group;
                console.log("\n Name :" + GroupWrapobject1.GetName());

                var Subgroup = GroupWrapobject1.GetSubGroupwrapName();

                console.log("\n SubGroup");

                if (Subgroup)
                {

                    for (Iterator1 in Subgroup)
                    {
                        console.log("\n Subgroup[" + Iterator1 + "] :" + Subgroup[Iterator1] + "\n");
                    }


                }
                
      


            }

        }

        console.log("\n Test GetDirectory ");
        var GroupWrapObject2 = DirectoryObject.GetGroupwrap("609AEC500800264DA73D02932FF3648F");
        var DirectoryGroupclone = GroupWrapobject1.GetDirectorywrap();
        if (DirectoryGroupclone == DirectoryObject) {
            console.log(" \n Test GetDirectory True ");

        }

        console.log("\n Test GetUserwrapByName");

        var UserGroupObject = GroupWrapobject1.GetUserwrapByName("Mohammed", "12345678");
        if (UserGroupObject) {
            console.log("\n Create User");
            console.log("\n Name :" + UserGroupObject.GetName());
        }
    }

    console.log("\n \n End Test Group \n");
    
    console.log("\n Begin Session Test \n");

    if(DirectoryObject)
    {
        var UserWrapObject3 = DirectoryObject.GetUserwrap("Mohammed", "12345678");
        if(UserWrapObject3)
        {
            var SessionObject3 = DirectoryObject.LogIn(UserWrapObject3);
            
            if(SessionObject3)
            {
                console.log(" \n Session was create \n");

                console.log("\n WSID :" + SessionObject3.GetWASID());

                console.log("\n valid :" + SessionObject3.IsValid());

                var UserObjectSession = SessionObject3.GetUserwrap();

                if (UserObjectSession)
                {
                    console.log("\n Username :" + UserObjectSession.GetName());
                }

                console.log("\n Logout :" + SessionObject3.LogOut());

                console.log("\n valid :" + SessionObject3.IsValid());

            }

        }

    }

    console.log("\n \n End Test Session \n");

    console.log("\n Begin Directory Test \n");

    if (DirectoryObject)
    {
        console.log("\n GetGroupwrapID  \n");
        var VectorGroupIdDir = DirectoryObject.GetGroupwrapID();

        for(IteratorVec in VectorGroupIdDir)
        {
            console.log("\n Vector[" + IteratorVec + "] :" + VectorGroupIdDir[IteratorVec]);
            

        }

        console.log("\n GetGroupwrapName  \n");
        var VectorGroupNameDir = DirectoryObject.GetGroupwrapNames();

        for (IteratorVecN in VectorGroupNameDir) {
            console.log("\n Vector[" + IteratorVecN + "] :" + VectorGroupNameDir[IteratorVecN]);


        }

        console.log("\n Test GetUserwrap");

        var UsrDireObject = DirectoryObject.GetUserwrap("Mohammed", "12345678");
        if(UsrDireObject)
        {
            console.log("\n Name :" + UsrDireObject.GetName());

            console.log("\n Test LogIn \n");

            var SessionDirLog = DirectoryObject.LogIn(UsrDireObject);

            if(SessionDirLog)
            {
                console.log("\n Isvalid :" + SessionDirLog.IsValid());

                console.log("\n Wsid :"+SessionDirLog.GetWASID());

                var wsid = SessionDirLog.GetWASID();

                SessionDirLogclone = DirectoryObject.GetSessionwrap(wsid);

                if(SessionDirLogclone)
                {

                    console.log("\n WSID clone :"+SessionDirLogclone.GetWASID())

                    console.log("\n Etat Valid  clone before logout:" + SessionDirLog.IsValid());
                    DirectoryObject.LogOut(SessionDirLog);

                    console.log("\n Etat Valid  clone after logout:" + SessionDirLog.IsValid());
                }

                console.log("\n Session valid after logout:" + SessionDirLog.IsValid());
            }

        }
        console.log("\n Test GetGroupwrap");

        for (IteratorVec in VectorGroupIdDir)
        {
            var ObjectDirectory = DirectoryObject.GetGroupwrap(VectorGroupIdDir[IteratorVec]);

            console.log("\n Vect[" + IteratorVec + "] : ID :" + VectorGroupIdDir[IteratorVec] + " : Name" + ObjectDirectory.GetName());

        }

        console.log(" \n Test Belong to argument UserWrap and Idgroup \n");
        
        for (IteratorVec in VectorGroupIdDir) {
            var ObjectDirectory = DirectoryObject.GetGroupwrap(VectorGroupIdDir[IteratorVec]);

           
            if (UsrDireObject)
            {
                var Resultat = DirectoryObject.UserwrapBelongTo(UsrDireObject, VectorGroupIdDir[IteratorVec]);

                console.log("\n Vect[" + IteratorVec + "] : ID :" + VectorGroupIdDir[IteratorVec] + " : Name :" + ObjectDirectory.GetName());

                console.log("\n User Name: " + UsrDireObject.GetName() + " Belong to :" + Resultat + "\n");


            }


        }


        console.log(" \n Test Belong to argument UserWrap and GroupWrap \n");

        for (IteratorVec in VectorGroupIdDir) {
            var ObjectDirectory = DirectoryObject.GetGroupwrap(VectorGroupIdDir[IteratorVec]);


            if (UsrDireObject) {
                var Resultat = DirectoryObject.UserwrapBelongTo(UsrDireObject, ObjectDirectory);

                console.log("\n Vect[" + IteratorVec + "] : ID :" + VectorGroupIdDir[IteratorVec] + " : Name :" + ObjectDirectory.GetName());

                console.log("\n User Name: " + UsrDireObject.GetName() + " Belong to :" + Resultat + "\n");


            }


        }

        console.log(" \n Test Belong to argument SessionWrap and GroupWrap \n");
        if (UsrDireObject) {

            var SessionObject4 = DirectoryObject.LogIn(UsrDireObject);

            console.log("\n Wsid :" + SessionObject4.GetWASID()+"\n");

        for (IteratorVec in VectorGroupIdDir) {

            var GroupObjectDirectory = DirectoryObject.GetGroupwrap(VectorGroupIdDir[IteratorVec]);


            var Resultat = DirectoryObject.UserwrapBelongTo(SessionObject4, VectorGroupIdDir[IteratorVec]);

                console.log("\n Vect[" + IteratorVec + "] : ID :" + VectorGroupIdDir[IteratorVec] + " : Name :" + GroupObjectDirectory.GetName());

                console.log("\n User Name: " + UsrDireObject.GetName() + " Belong to :" + Resultat + "\n");


            }


        }


    }

}