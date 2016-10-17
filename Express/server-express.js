var express = require('express');
var cookieParser = require('cookie-parser')
 
var app = express()
app.use(cookieParser())
var Variable=1;


const addon = require('./../build/Release/addon');
var DirectoryObject=new addon.Directory("http://localhost:8081","C:/Users/Laghzaoui/Documents/Wakanda/Demo/Demo Solution/directory.waDirectory");

	
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

function pagelogin(req,res,next)
{
	res.render('chambre1.ejs');
	res.end();
	
	
}
app.get('/',pagelogin);
function cookies(req,res,next)
{
		var reqwsid=req.cookies.WASID;
	
	//console.log("wsid listes groups :"+reqwsid+"length :"+reqwsid.length);
	if(reqwsid.length>0)
	{
		//console.log("Wsid2");
		
	var cookies1=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies1)
	{
			DirectoryObject.GetSession(cookies1,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
					next();
		}
		
	})
	
	}
	else
	{
		pagelogin(req,res);
	}
	}
	else
	{
		pagelogin(req,res);
		
	}
	
}
function validate(req,res,next)
{
	
		var username=req.param('name') ;
		
		var password1=req.param('Password');
		
			if((username)&&(password1))
		{
			
        var UsrDireObject = DirectoryObject.GetUser(username, password1);
        
		if(UsrDireObject)
        {

            DirectoryObject.LogIn(UsrDireObject,function(err,response){
				
				if(err)
				{
					console.log(err);
				}
				else
				{
					
					var SessionObject=response;
					
					if( SessionObject)
					{
						var wsid = SessionObject.GetWASID1();
						
						res.append('Set-Cookie', 'WASID='+wsid+'; Path=/; HttpOnly');
						var Submenu ="Index";
						 res.render('index.ejs', {
							Submenu:Submenu
						});
						res.end();
						
					}
					else
					{
						
						next();
					}
				}
 
		
			})
		}
		else
		{
			next();
		}
	}
else
		{
			next();
		}
	
} 




app.get('/login', pagelogin);


app.get('/validate', validate,pagelogin);
app.get('/index', cookies,function(req, res) {


	
					res.render('index.ejs', {
							
								});
								res.end();
	
 
});
app.get('/Listes_Groups',cookies, function(req, res) {
	
					var Submenu ="Listes_Groups";
	
					res.render('index.ejs', {
					Submenu:Submenu,
					listegroup:listegroup
					});
					res.end();
		
});

app.get('/Listes_Belongto',cookies, function(req, res) {
	
        var selected=0;
		var selectedliste=0;
		var reqwsid=req.cookies.WASID;
	
	
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
				
				
				
		
	
});

app.get('/Listes_Belongto1',cookies, function(req, res) {
	

        var selected=req.param('groupselected');
		var selectedliste=req.param('listeselected');
		////console.log("/Sub_Groups1 selected"+selected);
		
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
				
				
				
		
		
	
	
});


app.get('/Listes_Belongto2',cookies, function(req, res) {
	
        var selected=0;
		var selectedliste=0;
	
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
				
				
				
	
	
});

app.get('/Listes_Belongto3', function(req, res) {
	

        var selected=req.param('groupselected');
		var selectedliste=req.param('listeselected');
	
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
				
				
				
		
		

	
});


app.get('/User_Roles',cookies, function(req, res) {
	
	
			var Submenu ="User_Roles";
	
				res.render('index.ejs', {
				Submenu:Submenu
				});
				res.end();
		
	
	
	
});

app.get('/Logs',cookies, function(req, res) {
	
	
				var Submenu ="Logs";
	
				res.render('index.ejs', {
				Submenu:Submenu
				});
				res.end();
	
	
});

app.get('/Listes_Users',cookies, function(req, res) {
	
			var Submenu ="Listes_Users";
	
				res.render('index.ejs', {
						Submenu:Submenu,
						Users:Users
					});
					res.end();
				
		
	
});

app.get('/Listes_Belongtouser',cookies, function(req, res) {
	
				var Submenu ="Listes_Belongtouser";
	
				res.render('index.ejs', {
					Submenu:Submenu
				});
				
				res.end();
	
});

app.get('/Sub_Groups1',cookies, function(req, res) {
	
	////console.log("/Sub_Groups1");
        var selected=req.param('groupselected');
		
				var group1=DirectoryObject.GetGroup(groupsId[selected]);
				var listgroup1sub1=group1.GetSubGroupsName();
				var groupresultatliste=[];
				for(Iterator in listgroup1sub1)
				{
					var groupresultat=DirectoryObject.GetGroup(listgroup1sub1[Iterator]);
					groupresultatliste.push(groupresultat);
					
				}
				
					var Submenu ="Sub_Groups";
	
						res.render('index.ejs', {
						Submenu:Submenu,
						Groups:Groups,
						selected:selected,
						groupliste:groupresultatliste
					});
				
		
	
});
app.get('/Listes_loggedin',cookies, function(req, res) {
	
	
	
			    var listmanager=DirectoryObject.getlistmanager();
				
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
				res.end();
				}
				
		
	
});

app.get('/Session_Manager',cookies, function(req, res) {
	

	
						var listmanager=DirectoryObject.getlistmanager();
						
						var Submenu ="Session_Manager";
	
						res.render('index.ejs', {
							Submenu:Submenu,
							listmanager:listmanager
						});
						res.end();
				
		
	
	
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

app.get('/Session_Persistant',cookies, function(req, res) {
	

	
	
					var listsessionlog=DirectoryObject.getsessionlog();
					
					var Submenu ="Session_Persistant";
	
					res.render('index.ejs', {
					
					Submenu:Submenu,
					
					listsessionlog:listsessionlog
					});
					res.end();
				
		
	
	
});

app.get('/logout', function(req, res) {
	

	
			
			    
				var reqwsid=req.cookies.WASID;
	
	//console.log("wsid listes groups :"+reqwsid+"length :"+reqwsid.length);
	if(reqwsid.length>0)
	{
		//console.log("Wsid2");
		
	var cookies1=DirectoryObject.Getcookies(reqwsid);
	
	if(cookies1)
	{
			DirectoryObject.GetSession(cookies1,function(err,response){
		
		if(err)
		{
			
		}
		else
		{
					DirectoryObject.LogOut(response);
					pagelogin(req,res);
		}
		
	})
	
	}
	else
	{
		pagelogin(req,res);
	}
	}
	else
	{
		pagelogin(req,res);
		
	}
				
				
					
				//res.append('Set-Cookie', 'WASID= ; Path=/; HttpOnly');
	
				
				
		
	

	
	

	
	
});

app.get('/Sub_Groups1', cookies,function(req, res) {
	
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
					res.end();
				
	
	
});






app.get('/Sub_Groups',cookies, function(req, res) {
	
        var selected=1;
		
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
					res.end();
				
		
	
});

app.get('/User_Include',cookies, function(req, res)
{
	
	//console.log("/Sub_Groups1");
        var selected=2;
		
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
					res.end();
				
		
});

app.get('/User_Include1', function(req, res) {
	
	//console.log("/Sub_Groups1");
        var selected=req.param('groupselected');
		
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
					res.end();
				
		
});


app.listen(8282);