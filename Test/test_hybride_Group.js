console.log("\n \n Test Group");

const addon = require('./../build/Release/addon');

var DirectoryObject=new addon.Directory("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");


    if (DirectoryObject)
    {

        var VectorNameGroup = DirectoryObject.GetGroupsNames();

        var VectorIdGroup21 = DirectoryObject.GetGroupsID();

        

       
        for (Iterator in VectorIdGroup21)
        {
            //Testes create group byid;
            var GroupWrapobject1 = DirectoryObject.GetGroup(VectorIdGroup21[Iterator]);
            if (GroupWrapobject1)
            {
                console.log("\n ID :" + VectorIdGroup21[Iterator]);
                //Testes create group;
                console.log("\n Name :" + GroupWrapobject1.GetName());

                var Subgroup = GroupWrapobject1.GetSubGroupsName();

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
        var GroupWrapObject2 = DirectoryObject.GetGroup("04AE851D785A2043AF2AFC0B209A3316");
		var DirectoryGroupclone = GroupWrapobject1.GetDirectory();
        if (DirectoryGroupclone == DirectoryObject) {
            console.log(" \n Test GetDirectory True ");

        }

        console.log("\n Test GetUserwrapByName");

        var UserGroupObject = GroupWrapobject1.GetUserByName("Mohammed", "12345678");
        if (UserGroupObject) {
            console.log("\n Create User");
            console.log("\n Name :" + UserGroupObject.GetName());
        }
    }

    console.log("\n \n End Test Group \n");
