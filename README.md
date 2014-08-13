ios-sdk
=======

#Integration

See the sample project and copy all the integration from the **AppDelegate** class

#DeepLinks

Configure your action with your deeplink URL in the Beacon Manager Web interface. For instance
	
	myApp://myDeepLinkName
	
then intercept the **beaconEventsResolveDidFinishWithConfiguration:resolvedBeaconEvents:** method and insert your custom deep link logic as shown in this sample code:

	- (void)beaconEventsResolveDidFinishWithConfiguration:(SBBeaconEventsResolveConfiguration *)configuration resolvedBeaconEvents:(NSArray *)resolvedBeaconEvents {
	    for (SBResolvedBeaconEvent *resolvedBeaconEvent in resolvedBeaconEvents) {
	        NSURL *url = nil;
	        if ([resolvedBeaconEvent.action dataToBody:&body subject:&subject url:&url error:nil]){
	            if ([[url scheme] isEqualToString:@"myApp"]) {
	                //handle the deeplink
	            }
	            else{
	               [[SBBeaconManager sharedBeaconManager].resolvedBeaconEventPresenter presentFromResolvedBeaconEvents:@[ resolvedBeaconEvent ]];
	            }
	        }
	    }
	}
