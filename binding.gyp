{
  "targets": [
    {
      "target_name": "addon",
            'defines':[
              'CURL_STATICLIB',
			     
      
            ]
    
        ,
		  
	
      "sources": [ "*.cc","*.cpp","*.h", ]
	  ,"include_dirs": [
        "./include"
      ],
	  'conditions':[
        ['OS=="win"',
          {
            'link_settings': {
              'libraries': [
                '-lws2_32.lib',
                '-lwldap32.lib',
                '-ladvapi32.lib',
				'-lwsock32.lib',
              ],
            },
          }
        ]  ],
	  "library_dirs": [
        "./Lib/"
      ],
	  "link_settings":{
		"libraries":[ "-lcurl.lib","-llibssh2.lib","-llibcurl.lib","-lopenssl.lib","-lzlib.lib"
	  
		],
		  "ldflags": [
            "./obj/curl",
			"./obj/libssh2",
			"./obj/libcurl",
			"./obj/openssl.x64",
			"./obj/zlib",
            
        ]
	  }
	  
  
    }
  ]
}