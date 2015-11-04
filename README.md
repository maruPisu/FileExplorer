# FileExplorer
C++ simple file explorer using Qt
void CacheHandler::readFromSocket(){

    int rc;
    FCGX_Request request;

    if(FCGX_InitRequest(&request, socketId, 0) != 0){
        printf("Can not init request\n");
        return ;
    }

    QString content;
    //loop forever!
    while(1){
        content.clear ();
        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;

        //stay here waiting for an accepted connection
        pthread_mutex_lock(&accept_mutex);
        if(FCGX_Accept_r(&request) == -1){
            printf("Can not accept new request\n");
            break;
        }
        pthread_mutex_unlock(&accept_mutex);

        //From here we are processing a new request
        request_count++;

        if(check_user_agent( FCGX_GetParam("HTTP_USER_AGENT", request.envp))){
            empty_response();
            continue;
        }

        QUrlQuery query;
        query.setQuery (FCGX_GetParam("QUERY_STRING", request.envp));

        content.append ("Content-type: text/html\r\n");
        content.append("\r\n");
        content.append("richiesta: ").append (QString::number (request_count) + "<br>\n");
        int bx, a;
        //Requesting for a banner
        if((query.queryItemValue ("a").toInt () > 0) && (query.queryItemValue ("bx").toInt () > 0)){
        //    content.append (query.toString ());
            a = query.queryItemValue ("a").toInt ();
            bx = query.queryItemValue ("bx").toInt ();
            content.append(requestAffiliate(a)).append("<br>\n");
            if(isAffiliateAuth){
                content.append(requestBanner(bx)).append("<br>\n");
                if(campaignLeftover == -1){
                    content.append("no campaign found").append("<br>\n");
                }else{
                   content.append(requestCampaign(campaignLeftover)).append("<br>\n");
                   campaignLeftover = -1;
                }

                FCGX_PutS(content.toStdString ().c_str (), request.out);
                FCGX_Finish_r(&request);
                qDebug() << "\nNew request: \n"<<content;
                continue;
            }
        }
        else if(!query.queryItemValue ("nagg").isNull()){

            QByteArray cookie_raw= FCGX_GetParam("HTTP_COOKIE", request.envp);
            QHash<QString, QString> cookie;

            foreach(QByteArray line, cookie_raw.split(';')){
                int colon = line.indexOf('=');
                QByteArray headerName = line.left(colon).trimmed();
                QByteArray headerValue = line.mid(colon + 1).trimmed();
                cookie.insertMulti(headerName, headerValue);
            }

            QHashIterator<QString, QString> i(cookie);
            QString afsu = "";
            QString otherCookie = "cookie";
            while (i.hasNext()) {
                i.next();
                if(i.key().compare("afsu") == 0){
                    afsu = i.value();
                }                                                       // *************************************
                if(i.key().compare("nameofthecookie") == 0){            //TODO: INSERT HERE THE NAME OF THE COOKIE
                    otherCookie = i.value();                                   // *************************************
                }
            }

            content.append(requestNugg(afsu.toInt() , query.queryItemValue ("nagg"), otherCookie)).append("<br>\n");

            FCGX_PutS(content.toStdString ().c_str (), request.out);
            FCGX_Finish_r(&request);
            continue;
        }

        content.append("nothing to do here");
        FCGX_PutS(content.toStdString ().c_str (), request.out);
        FCGX_Finish_r(&request);
    }
}
