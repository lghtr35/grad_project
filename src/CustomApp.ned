package src;

import inet.applications.udpapp.UdpBasicApp;

simple CustomApp extends UdpBasicApp
{
    parameters:
        int layer;
	@class(CustomApp);
}
