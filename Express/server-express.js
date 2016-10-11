var express = require('express');
var cookieParser = require('cookie-parser')
 
var app = express()
app.use(cookieParser())
var Variable=1;


const addon = require('./../build/Release/addon');
var DirectoryObject=new addon.Directory("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Demo/Demo Solution/directory.waDirectory");

    //console.log("\n Begin Directory Test \n");
	
	var Groups=DirectoryObject.GetGroupsNames();
	
	var Users=DirectoryObject.getusers();
	var listegroup=[];
	var groupsId=DirectoryObject.GetGroupsID();
	for(Iteratorgroup in groupsId)
	{
		var groupresultat=DirectoryObject.GetGroup(groupsId[Iteratorgroup]);
		listegroup.push(groupresultat);
		
	}
	var listeusers=[];
	

	

app.use(express.static(__dirname + '/public'));

app.get('/', function(req, res) {
    res.render('chambre1.ejs');
});

app.get('/login', function(req, res) {
 
 res.render('chambre1.ejs');

 
});


app.get('/validate', function(req, res) {
 
		var username=req.param('name') ;
		
		var password1=req.param('Password');
		
		if((username)&&(password1))
		{
			
		
 
        var UsrDireObject = DirectoryObject.GetUser(username, password1);
        
		if(UsrDireObject)
        {
			//console.log("test");
			
            //console.log("\n Name :" + UsrDireObject.GetName());

            //console.log("\n Test LogIn \n");

            DirectoryObject.LogIn(UsrDireObject,function(err,response){
				
				if(err)
				{
					//console.log(err);
				}
				else
				{
					
					var SessionObject=response;
					
					if( SessionObject)
					{
						////console.log("Session object false");
						var wsid = SessionObject.GetWASID1();
						////console.log("Wsid :"+wsid);
						//res.cookie('WASID', wsid);
						res.append('Set-Cookie', 'WASID='+wsid+'; Path=/; HttpOnly');
						var Submenu ="Index";
						 res.render('index.ejs', {
							Submenu:Submenu
						});
						res.end();
						
					}
					else
					{
						//console.log("Session object false");
						
						res.render('chambre1.ejs');
					}
				}
 
		
			})
		}
		else
		{
			res.render('chambre1.ejs');
		}
	}
else
		{
			res.render('chambre1.ejs');
		}
 
});
app.get('/index', function(req, res) {

var reqwsid=req.cookies.WASID;
	
	//console.log("wsid index :"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
					res.render('index.ejs', {
							
								});
								res.end();
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
 
});
app.get('/Listes_Groups', function(req, res) {
	var reqwsid=req.cookies.WASID;
	
	//console.log("wsid listes groups :"+reqwsid+"length :"+reqwsid.length);
	if(reqwsid.length>0)
	{
		//console.log("Wsid2");
		
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
					var Submenu ="Listes_Groups";
	
					res.render('index.ejs', {
					Submenu:Submenu,
					listegroup:listegroup
					});
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
});

app.get('/Listes_Belongto', function(req, res) {
	
        var selected=0;
		var selectedliste=0;
		var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
				console.log(err);
		}
		else
		{
				var listmanager=DirectoryObject.getlistmanager();
				
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				
				var cookies1=DirectoryObject.Getcookies(listmanager[selectedliste].WSID);
				
				DirectoryObject.GetSession(cookies1,function(err,response){
					if(err)
					{
						console.log(err);
					}
					else
					{
						var listgroup1sub=group1.getsubgroupId();
				
						var listgroup1sub1=group1.GetSubGroupsName();
						
						DirectoryObject.UserBelongTo(response,groupsId[selected],function(err,response)
						{
							
						if(err)
						{
							console.log(err);
						}
						else
						{
						var Submenu ="Listes_Belongto";
						
						var etat=response;
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:listegroup,
						listmanager:listmanager,
						selectedliste:selectedliste,
						etat:etat
					});
						}
						
							
						})
				
				
					
						
					}
					
				})
				
				
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});

app.get('/Listes_Belongto1', function(req, res) {
	

        var selected=req.param('groupselected');
		var selectedliste=req.param('listeselected');
		////console.log("/Sub_Groups1 selected"+selected);
		var reqwsid=req.cookies.WASID;
	
	////console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
	{
				var listmanager=DirectoryObject.getlistmanager();
				
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				
				var cookies1=DirectoryObject.Getcookies(listmanager[selectedliste].WSID);
				
				DirectoryObject.GetSession(cookies1,function(err,response){
					if(err)
					{
						console.log(err);
					}
					else
					{
						var listgroup1sub=group1.getsubgroupId();
				
						var listgroup1sub1=group1.GetSubGroupsName();
						
						DirectoryObject.UserBelongTo(response,groupsId[selected],function(err,response)
						{
							
						if(err)
						{
							
						}
						else
						{
						var Submenu ="Listes_Belongto";
						
						var etat=response;
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:listegroup,
						listmanager:listmanager,
						selectedliste:selectedliste,
						etat:etat
					});
						}
						
							
						})
				
				
					
						
					}
					
				})
				
				
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});


app.get('/Listes_Belongto2', function(req, res) {
	
        var selected=0;
		var selectedliste=0;
		var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
				var listmanager=DirectoryObject.getlistmanager();
				
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				
				var cookies1=DirectoryObject.Getcookies(listmanager[selectedliste].WSID);
				
				DirectoryObject.GetSession(cookies1,function(err,response){
					if(err)
					{
						console.log(err);
					}
					else
					{
						var listgroup1sub=group1.getsubgroupId();
				
						var listgroup1sub1=group1.GetSubGroupsName();
						
						DirectoryObject.UserBelongTo(response,groupsId[selected],function(err,response)
						{
							
						if(err)
						{
							
						}
						else
						{
						var Submenu ="Listes_Belongtouser";
						
						var etat=response;
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:listegroup,
						listmanager:listmanager,
						selectedliste:selectedliste,
						etat:etat
					});
						}
						
							
						})
				
				
					
						
					}
					
				})
				
				
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});

app.get('/Listes_Belongto3', function(req, res) {
	

        var selected=req.param('groupselected');
		var selectedliste=req.param('listeselected');
		////console.log("/Sub_Groups1 selected"+selected);
		var reqwsid=req.cookies.WASID;
	
	////console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
	{
				var listmanager=DirectoryObject.getlistmanager();
				
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				
				var cookies1=DirectoryObject.Getcookies(listmanager[selectedliste].WSID);
				
				DirectoryObject.GetSession(cookies1,function(err,response){
					if(err)
					{
						console.log(err);
					}
					else
					{
						var listgroup1sub=group1.getsubgroupId();
				
						var listgroup1sub1=group1.GetSubGroupsName();
						
						DirectoryObject.UserBelongTo(response,groupsId[selected],function(err,response)
						{
							
						if(err)
						{
							
						}
						else
						{
						var Submenu ="Listes_Belongtouser";
						
						var etat=response;
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:listegroup,
						listmanager:listmanager,
						selectedliste:selectedliste,
						etat:etat
					});
						}
						
							
						})
				
				
					
						
					}
					
				})
				
				
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});


app.get('/User_Roles', function(req, res) {
	
	var reqwsid=req.cookies.WASID;
	
	//console.log("wsid User_Roles:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
			var Submenu ="User_Roles";
	
				res.render('index.ejs', {
				Submenu:Submenu
				});
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
	
});

app.get('/Logs', function(req, res) {
	
	var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Logs:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
				var Submenu ="Logs";
	
				res.render('index.ejs', {
				Submenu:Submenu
				});
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
	
});

app.get('/Listes_Users', function(req, res) {
	var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Listes_Users:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
			var Submenu ="Listes_Users";
	
				res.render('index.ejs', {
						Submenu:Submenu,
						Users:Users
					});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});

app.get('/Listes_Belongtouser', function(req, res) {
	

	
		var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Listes_Belongtouser:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
				var Submenu ="Listes_Belongtouser";
	
				res.render('index.ejs', {
					Submenu:Submenu
				});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});

app.get('/Sub_Groups1', function(req, res) {
	
	////console.log("/Sub_Groups1");
        var selected=req.param('groupselected');
		////console.log("/Sub_Groups1 selected"+selected);
		var reqwsid=req.cookies.WASID;
	
	////console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				var listgroup1sub1=group1.GetSubGroupsName();
				var groupresultatliste=[];
				for(Iterator in listgroup1sub1)
				{
					var groupresultat=DirectoryObject.GetGroup(listgroup1sub1[Iterator]);
					groupresultatliste.push(groupresultat);
					
				}
				
				//console.log()
					var Submenu ="Sub_Groups";
	
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:groupresultatliste
					});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});
app.get('/Listes_loggedin', function(req, res) {
	
	
	var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Listes_loggedin:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	var listmanager=DirectoryObject.getlistmanager();
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
			
				var lenghtlist=listmanager.length;
				for(var i=0;i<lenghtlist;i++)
				{
					var object= listmanager[i];
					
					var userobject=DirectoryObject.GetUser(object.Username,"a");
					
					var cookiessession=DirectoryObject.Getcookies(object.WSID);
					DirectoryObject.GetSession(cookiessession,function(err,response){
						
						if(err)
						{
							//console.log(err);
						}
						// else
						{
						
						
						//console.log("Wsid 1 :"+sessionobject.GetWASID());
						
						userobject.IsLoggedIn(response,function(err,response)
						{
							if(err)
							{
								//console.log(err);
							}
							else
							{
								
							}
							
						})
						}
						
					});
				}
				if(i==lenghtlist)
				{
				var Submenu ="Listes_loggedin";
				
				res.render('index.ejs', {
					Submenu:Submenu,
					listmanager:listmanager
				});
				
				}
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
	
});

app.get('/Session_Manager', function(req, res) {
	

	
	var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Session_Manager:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	var listmanager=DirectoryObject.getlistmanager();
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
						var Submenu ="Session_Manager";
	
						res.render('index.ejs', {
							Submenu:Submenu,
							listmanager:listmanager
						});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
	
});

app.get('/Session_Manager1', function(req, res) {
	
var reqwsid=req.param('wsidsessionmanager');
	
	//console.log("/Session_Manager1 wsid :"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	//console.log("/Session_Manager1 hana cookies :"+cookies);
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err){
		
		if(err)
		{
			
		}
		else
		{
				
				

				//console.log("Session object"+session_object.GetWASID());
				
				DirectoryObject.LogOut();
					
				
				res.redirect('/Session_Manager')
			
				
		}
		
	})
	
	}
		else
	{
		res.redirect('/Session_Manager')
	}
	}
	
	
	
	
});

app.get('/Session_Persistant', function(req, res) {
	

	
	var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Session_Persistant:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
					var listsessionlog=DirectoryObject.getsessionlog();
					
					var Submenu ="Session_Persistant";
	
					res.render('index.ejs', {
					
					Submenu:Submenu,
					
					listsessionlog:listsessionlog
					});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
	
});

app.get('/logout', function(req, res) {
	

	var reqwsid=req.cookies.WASID;
	
	//console.log("wsid logout:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
			
			    
				console.log(cookies);
				
				DirectoryObject.LogOut(response);
					
				//res.append('Set-Cookie', 'WASID= ; Path=/; HttpOnly');
	
				res.render('chambre1.ejs');
				
		}
		
	})
	
	}
		else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	

	
	

	
	
});

app.get('/Sub_Groups1', function(req, res) {
	
	////console.log("/Sub_Groups1");
        var selected=req.param('groupselected');
		////console.log("/Sub_Groups1 selected"+selected);
		var reqwsid=req.cookies.WASID;
	
	////console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				var listgroup1sub1=group1.GetSubGroupsName();
				var groupresultatliste=[];
				for(Iterator in listgroup1sub1)
				{
					var groupresultat=DirectoryObject.GetGroup(listgroup1sub1[Iterator]);
					groupresultatliste.push(groupresultat);
					
				}
				
				//console.log()
					var Submenu ="Sub_Groups";
	
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:groupresultatliste
					});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});






app.get('/Sub_Groups', function(req, res) {
	
        var selected=1;
		var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				var listgroup1sub=group1.getsubgroupId();
				var listgroup1sub1=group1.GetSubGroupsName();
				var groupresultatliste=[];
				for(Iterator in listgroup1sub1)
				{
					var groupresultat=DirectoryObject.GetGroup(listgroup1sub1[Iterator]);
					groupresultatliste.push(groupresultat);
					
				}
				
				//console.log()
					var Submenu ="Sub_Groups";
	
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:groupresultatliste
					});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});

app.get('/User_Include', function(req, res)
{
	
	//console.log("/Sub_Groups1");
        var selected=2;
		//console.log("/Sub_Groups1 selected"+selected);
		var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				var listuser=group1.userinclude();
				var usersultatliste=[];
				for(iter in listuser)
				{
					//console.log("Iduser Include"+listuser[iter]);
					var userresultat=DirectoryObject.GetUser(listuser[iter],"a");
					usersultatliste.push(userresultat);
				}
				
				
				//console.log()
					var Submenu ="User_Include";
	
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:usersultatliste
					});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});

app.get('/User_Include1', function(req, res) {
	
	//console.log("/Sub_Groups1");
        var selected=req.param('groupselected');
		//console.log("/Sub_Groups1 selected"+selected);
		var reqwsid=req.cookies.WASID;
	
	//console.log("wsid Sub_Groups:"+reqwsid);
	if(reqwsid.length>1)
	{
	var cookies=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies)
	{
			DirectoryObject.GetSession(cookies,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				var listuser=group1.userinclude();
				var usersultatliste=[];
				for(iter in listuser)
				{
					//console.log("Iduser Include"+listuser[iter]);
					var userresultat=DirectoryObject.GetUser(listuser[iter],"a");
					usersultatliste.push(userresultat);
				}
				
				//console.log()
					var Submenu ="User_Include";
	
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:usersultatliste
					});
				
		}
		
	})
	
	}
	else
	{
		res.render('chambre1.ejs');
	}
	}
	else
	{
		res.render('chambre1.ejs');
	}
	
});


app.listen(8282);