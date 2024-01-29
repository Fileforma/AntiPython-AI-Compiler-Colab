#include "mongoose.h"
#include "cJSON.h" 
#include "LanguageServer_Java.h"

static const char *s_listen_on = "ws://localhost:8000";
static const char *s_web_root = ".";


static void ServerHandler(struct mg_connection *connection, int event, void *eventData)
{
	if(event == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *hm = (struct mg_http_message *) eventData;
		if(mg_http_match_uri(hm, "/api/hi"))
		{
			mg_http_reply(connection, 200, "", "{%m:%m,%m:%m}\n", MG_ESC("uri"), mg_print_esc, hm->uri.len, hm->uri.ptr,MG_ESC("body"), mg_print_esc, hm->body.len, hm->body.ptr);
		}
		else if (mg_http_match_uri(hm, "/websocket"))
		{
			mg_ws_upgrade(connection, hm, NULL);
		}
		else
		{
			struct mg_http_serve_opts opts = {.root_dir = "dist"};
			mg_http_serve_dir(connection, hm, &opts);
		}
	}
	else if(event == MG_EV_WS_MSG) 
	{
		struct mg_ws_message *wm = (struct mg_ws_message *) eventData;
		int messageType = wm->flags & 0x0F;
		if(messageType == WEBSOCKET_OP_TEXT)
		{
			//printf("ReceivedS %s\n",wm->data.ptr);
			cJSON *json = cJSON_Parse(wm->data.ptr);
			if(json == NULL)
			{
				const char *errorMessage = cJSON_GetErrorPtr();
				if(errorMessage != NULL)
				{
					printf("JSON Error : %s\n", errorMessage);
				}
				cJSON_Delete(json);
			}
			cJSON *parsedMessage = cJSON_GetObjectItemCaseSensitive(json, "message");
			cJSON *parsedPing    = cJSON_GetObjectItemCaseSensitive(json, "ping");
			if(cJSON_IsString(parsedPing) && (parsedPing->valuestring != NULL))
			{
				char *pong = "pong";
				mg_ws_send(connection, pong, 5, WEBSOCKET_OP_TEXT);
			}
			else if(cJSON_IsString(parsedMessage) && (parsedMessage->valuestring != NULL))
			{ 
				//printf("Code :  %s\n", parsedMessage->valuestring); 
				printf("\n");
				ParseCode(strlen(parsedMessage->valuestring),parsedMessage->valuestring);
				mg_ws_send(connection, wm->data.ptr, wm->data.len, WEBSOCKET_OP_TEXT);
			}

			cJSON_Delete(json);
		}
		
		
	}
}

int main()
{
	javaParser= ts_parser_new();
	ts_parser_set_language(javaParser, tree_sitter_java());
	
	struct mg_mgr eventManager;mg_mgr_init(&eventManager);
	//mg_log_set(MG_LL_DEBUG);
	mg_http_listen(&eventManager, "http://0.0.0.0:8000", ServerHandler, NULL);for (;;) mg_mgr_poll(&eventManager, 1000); 
	
	mg_mgr_free(&eventManager);
	ts_parser_delete(javaParser);
  	return 0;
}
/*
clear && gcc main.c mongoose.c cJSON.c ../SupportedLanguages/tree-sitter-java/src/parser.c ../TreeSitterLibrary/libtree-sitter.a -o main.o && ./main.o
*/
