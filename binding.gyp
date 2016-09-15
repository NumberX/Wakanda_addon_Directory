{
  "targets": [
    {
      "target_name": "addon",
            'defines':[
              'CURL_STATICLIB',
			     
      
            ]
    
        ,
		  
	
      "sources": [ "./Src/*.cc","./Src/*.cpp","./Src/*.h", ]
	  ,"include_dirs": [
        "./Library/include"
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
        "./Library/Lib/"
      ],
	  "link_settings":{
		"libraries":[ "-lcurl.lib","-llibssh2.lib","-llibcurl.lib","-lopenssl.lib","-lzlib.lib"
	  
		],
		  "ldflags": [
            "./Library/obj/curl",
			"./Library/obj/libssh2",
			"./Library/obj/libcurl",
			"./Library/obj/openssl.x64",
			"./Library/obj/zlib",
            
        ]
	  }
	  
  
    }
  ]
}