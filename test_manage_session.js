const addon = require('./build/Release/addon');

var DirectoryObject=new addon.Directorywrap("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");

//var DirectoryObject1 = new addon.Directorywrap();

if (DirectoryObject) {

    console.log(DirectoryObject);

    //create User

    var UserWrap = DirectoryObject.GetUserwrap("Mohammed", "12345678");
	var UserWrap1 = DirectoryObject.GetUserwrap("Ayoub", "12345678");

    if (UserWrap != null) {
        //Test Functionaliter of UserWrap


        var SessionObject = DirectoryObject.LogIn(UserWrap);


        if (SessionObject) {
            //Obtain Session from login withn argument User
           
            //test User.IsLoggedIn(const v8::FunctionCallbackInfo<v8::Value>& args);


            console.log("\n User isLoggedIn " + UserWrap.IsLoggedIn(SessionObject));

            console.log("\n Session Wsid" + SessionObject.GetWASID());

            //deconnectes  Session

		}
		var SessionObject1 = DirectoryObject.LogIn(UserWrap);
		
		if (SessionObject) {
            //Obtain Session from login withn argument User
           
            //test User.IsLoggedIn(const v8::FunctionCallbackInfo<v8::Value>& args);


            console.log("\n User isLoggedIn " + UserWrap.IsLoggedIn(SessionObject));

            console.log("\n Session Wsid" + SessionObject.GetWASID());

            //deconnectes  Session

		}
		
		
	}
	
	
	  if (UserWrap1 != null) {
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
}