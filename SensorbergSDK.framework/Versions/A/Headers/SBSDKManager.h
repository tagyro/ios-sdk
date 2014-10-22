//
//  SBSDKManager.h
//  SensorbergSDK
//
//  Created by Max Horvath on 09/09/2014.
//  Copyright (c) 2014 Sensorberg GmbH. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import <Availability.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "SBSDKNetworkManager.h"

@protocol SBSDKManagerDelegate;

#pragma mark -

/**
 SBSDKManagerAvailabilityStatus

 Represents the app’s overall iBeacon readiness, like Bluetooth being turned on,
 Background App Refresh enabled and authorization to use location services.
 */
typedef NS_ENUM(NSInteger, SBSDKManagerAvailabilityStatus) {
    /**
     Background App Refresh is enabled, the app is authorized to use location services and
     Bluetooth is turned on.
     */
    SBSDKManagerAvailabilityStatusFullyFunctional NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     Bluetooth is turned off. The specific status can be found in bluetoothStatus.
     */
    SBSDKManagerAvailabilityStatusBluetoothRestricted NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     This application is not enabled to use Background App Refresh. The specific status can be
     found in backgroundAppRefreshStatus.
     */
    SBSDKManagerAvailabilityStatusBackgroundAppRefreshRestricted NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     This application is not authorized to use location services. The specific status can be
     found in authorizationStatus.
     */
    SBSDKManagerAvailabilityStatusAuthorizationRestricted NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     This application is not connected to the Sensorberg Beacon Management Platform. The
     specific status can be found in connectionState.
     */
    SBSDKManagerAvailabilityStatusConnectionRestricted NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     This application cannot reach the Sensorberg Beacon Management Platform. The specific
     status can be found in reachabilityState.
     */
    SBSDKManagerAvailabilityStatusReachabilityRestricted NS_ENUM_AVAILABLE(NA, 7_0)
};

/**
 SBSDKManagerBluetoothStatus

 Represents the device’s Bluetooth status.
 */
typedef NS_ENUM(NSInteger, SBSDKManagerBluetoothStatus) {
    /**
     Bluetooth is not known yet. As soon as the state is known,
     beaconManager:didChangeBluetoothStatus: will be called.
     */
    SBSDKManagerBluetoothStatusUnknown NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     Bluetooth is turned on.
     */
    SBSDKManagerBluetoothStatusPoweredOn NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     Bluetooth is turned off.
     */
    SBSDKManagerBluetoothStatusPoweredOff NS_ENUM_AVAILABLE(NA, 7_0)
};

/**
 SBSDKManagerBackgroundAppRefreshStatus

 Represents the app’s Background App Refresh status.
 */
typedef NS_ENUM(NSInteger, SBSDKManagerBackgroundAppRefreshStatus) {
    /**
     Background App Refresh is enabled, the app is authorized to use location services and
     Bluetooth is turned on.
     */
    SBSDKManagerBackgroundAppRefreshStatusAvailable NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     This application is not enabled to use Background App Refresh. Due
     to active restrictions on Background App Refresh, the user cannot change
     this status, and may not have personally denied availability.
     
     Do not warn the user if the value of this property is set to 
     SBSDKManagerBackgroundAppRefreshStatusRestricted; a restricted user does not have
     the ability to enable multitasking for the app.
     */
    SBSDKManagerBackgroundAppRefreshStatusRestricted NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     User has explicitly disabled Background App Refresh for this application, or
     Background App Refresh is disabled in Settings.
     */
    SBSDKManagerBackgroundAppRefreshStatusDenied NS_ENUM_AVAILABLE(NA, 7_0)
};

/**
 SBSDKManagerAuthorizationStatus

 Represents the app’s authorization status for using location services.
 */
typedef NS_ENUM(NSInteger, SBSDKManagerAuthorizationStatus) {
    /**
     User has not yet made a choice with regards to this application
     */
    SBSDKManagerAuthorizationStatusNotDetermined NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     Authorization procedure has not been fully implemeneted in app.
     NSLocationAlwaysUsageDescription is missing from Info.plist.
     */
    SBSDKManagerAuthorizationStatusUnimplemented NS_ENUM_AVAILABLE(NA, 8_0),

    /**
     This application is not authorized to use location services. Due
     to active restrictions on location services, the user cannot change
     this status, and may not have personally denied authorization.

     Do not warn the user if the value of this property is set to
     SBSDKManagerAuthorizationStatusRestricted; a restricted user does not have
     the ability to enable multitasking for the app.
     */
    SBSDKManagerAuthorizationStatusRestricted NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     User has explicitly denied authorization for this application, or
     location services are disabled in Settings.
     */
    SBSDKManagerAuthorizationStatusDenied NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     User has granted authorization to use their location at any time,
     including monitoring for regions, visits, or significant location changes.
     */
    SBSDKManagerAuthorizationStatusAuthorized NS_ENUM_AVAILABLE(NA, 7_0)
};

/**
 SBSDKManagerConnectionState
 
 Represents the current connection state of the SBSDKManager object to the 
 Sensorberg Beacon Management Platform.
 */
typedef NS_ENUM(NSInteger, SBSDKManagerConnectionState) {
    /**
     The SBSDKManager object is not connected to the Sensorberg Beacon Management Platform.
     */
    SBSDKManagerConnectionStateDisconnected NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     The SBSDKManager object is trying to connect to the Sensorberg Beacon Management Platform.
     */
    SBSDKManagerConnectionStateConnecting NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     The SBSDKManager object is connected to the Sensorberg Beacon Management Platform.
     */
    SBSDKManagerConnectionStateConnected NS_ENUM_AVAILABLE(NA, 7_0)
};

/**
 SBSDKManagerReachabilityState

 Represents the current reachability state of the SBSDKManager object to the
 Sensorberg Beacon Management Platform.
 */
typedef NS_ENUM(NSInteger, SBSDKManagerReachabilityState) {
    /**
     The Sensorberg Beacon Management Platform is reachable.
     */
    SBSDKManagerReachabilityStateReachable NS_ENUM_AVAILABLE(NA, 7_0),

    /**
     The Sensorberg Beacon Management Platform is not reachable.
     */
    SBSDKManagerReachabilityStateNotReachable NS_ENUM_AVAILABLE(NA, 7_0)
};

#pragma mark -

/**
 The SBSDKManager object is your entry point for handling the interaction with beacons
 that are managed via the Sensorberg Beacon Management Platform.
 */
NS_CLASS_AVAILABLE(NA, 7_0)
@interface SBSDKManager : NSObject <CLLocationManagerDelegate, CBCentralManagerDelegate, SBSDKNetworkManagerDelegate>

/**
 Delegate for SBSDKManager.
 */
@property(assign, nonatomic) id <SBSDKManagerDelegate> delegate;

/**
 Holds a list of regions to listen for iBeacon advertisements.

 Each regions object holds a string of the proximityUUID of a beacon id.
 */
@property (nonatomic, readonly) NSArray *regions __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Holds a list of all detected Beacons.
 */
@property (nonatomic, readonly) NSArray *detectedBeacons;

/**
 The SBSDKNetworkManager object used by the SBSDKManager object.
 */
@property (nonatomic, readonly) SBSDKNetworkManager *networkManager __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 The CLLocationManager object used by the SBSDKManager object.
 */
@property (nonatomic, readonly) CLLocationManager *locationManager __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 The CBCentralManager object used by the SBSDKManager object.
 */
@property (nonatomic, readonly) CBCentralManager *bluetoothManager __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Indicates the app’s overall iBeacon readiness.
 */
@property (nonatomic, readonly) SBSDKManagerAvailabilityStatus availabilityStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Indicates the device’s Bluetooth status.
 */
@property (nonatomic, readonly) SBSDKManagerBluetoothStatus bluetoothStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Indicates the app’s Background App Refresh status.
 */
@property (nonatomic, readonly) SBSDKManagerBackgroundAppRefreshStatus backgroundAppRefreshStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Indicates the app’s authorization status for using location services.
 */
@property (nonatomic, readonly) SBSDKManagerAuthorizationStatus authorizationStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Indicates if the SBSDKManager object is connected to the Sensorberg Beacon Management Platform.
 */
@property (nonatomic, readonly) SBSDKManagerConnectionState connectionState __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Indicates if the Sensorberg Beacon Management Platform is reachable via the current
 network connection.
 */
@property (nonatomic, readonly) SBSDKManagerReachabilityState reachabilityState __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

///---------------------
/// @name Initialization
///---------------------

/**
 Designated initializer of the SBSDKManager object.

 @param delegate Delegate for SBSDKManager.

 @return SBSDKManager object.
 */
- (instancetype)initWithDelegate:(id<SBSDKManagerDelegate>)delegate __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Initializer of the SBSDKManager object, if you want to re-use a CLLocationManager object.

 @param locationManager CLLocationManager object to be used.

 @return SBSDKManager object.
 */
- (instancetype)initWithDelegate:(id<SBSDKManagerDelegate>)delegate locationManager:(CLLocationManager *)locationManager __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

///----------------------------------
/// @name Accessing location services
///----------------------------------

/**
 When authorizationStatus == SBSDKManagerAuthorizationStatusNotDetermined, calling this method will
 trigger a prompt to request "always" authorization from the user.
 
 If possible, perform this call in response to direct user request for a location-based service
 so that the reason for the prompt will be clear.
 
 Any authorization change as a result of the prompt will be reflected via the
 delegate callback beaconManager:didChangeAuthorizationStatus:.

 When authorizationStatus != SBSDKManagerAuthorizationStatusNotDetermined, (i.e. generally
 after the first call) this method will do nothing.

 If the NSLocationAlwaysUsageDescription key is not specified in your Info.plist, this method
 will do nothing, as your app will be assumed not to support Always authorization.
 
 When running on iOS 7, this method will do nothing.
 */
- (void)requestAuthorization __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

///--------------------------------------------------------------
/// @name Connecting to the Sensorberg Beacon Management Platform
///--------------------------------------------------------------

/**
 Actively connects the SBSDKManager object to the Sensorberg Beacon Management Platform
 in order to resolve detected beacon advertisments.

 This is done asynchronously.

 @param apiKey  API key to use.
 @param error   If an error occurs, upon return contains an `NSError` object
                that describes the problem.

 @return `YES` if the connection request was initiated, otherwise `NO`.
 */
- (BOOL)connectToBeaconManagementPlatformUsingApiKey:(NSString *)apiKey
                                               error:(NSError * __autoreleasing *)error __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Disconnects the SBSDKManager object from the Sensorberg Beacon Management Platform.

 Can savely be called even if SBSDKManager object wasn't connected to the Sensorberg
 Beacon Management Platform, yet.
 */
- (void)disconnectFromBeaconManagementPlatform __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

///----------------------
/// @name Beacon handling
///----------------------

/**
 Monitors all beacons that are managed via the Sensorberg Beacon Management Platform.

 If Sensorberg Beacon Management Platform is not reachable, the default set of
 Sensorberg Proximity UUIDs will be used.

 This is done asynchronously.

 Delegate method manager:didRangeBeacons:inRegion: is used to retrieve found beacons.

 @see manager:didRangeBeacons:inRegion:
 */
- (void)startMonitoringBeacons __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Stops monitoring all beacons that are managed via the Sensorberg Beacon Management Platform.

 This is done asynchronously.
 */
- (void)stopMonitoringBeacons __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

///----------------
/// @name Constants
///----------------

/**
 Domain used for beacon region identifiers.
 */
extern NSString *const SBSDKManagerBeaconRegionIdentifier;

/**
 Error domain used in Sensorberg SDK.
 */
extern NSString *const SBSDKManagerErrorDomain;

/**
 Error codes used in Sensorberg SDK
 */
typedef NS_ENUM(NSInteger, SBSDKManagerErrorCode) {
    SBSDKManagerErrorNotAuthorized = -100,
    SBSDKManagerErrorAuthorizationUnimplemented = -99,
    SBSDKManagerErrorApiKeyMissing = -98,
    SBSDKManagerErrorAlreadyConnected = -97
};

@end

#pragma mark - 

/**
 The SBSDKManager protocol defines the delegate methods to respond to related events.
 */
@protocol SBSDKManagerDelegate <NSObject>

@optional

/**
 Tells the delegate that the Bluetooth status for the device changed.

 This method is called whenever the device's ability to use Bluetooth changes.
 Changes can occur because the user enabled or disabled the Bluetooth radio
 for the system as a whole.

 @param manager                    Beacon manager.
 @param backgroundAppRefreshStatus New backgroundAppRefreshStatus.
 */
- (void)beaconManager:(SBSDKManager *)manager didChangeBluetoothStatus:(SBSDKManagerBluetoothStatus)bluetoothStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Tells the delegate that the Background App Refresh status for the application changed.

 This method is called whenever the application’s ability to use Background App Refresh changes.
 Changes can occur because the user allowed or denied the use of Background App Refresh for your
 application or for the system as a whole.

 @param manager                    Beacon manager.
 @param backgroundAppRefreshStatus New backgroundAppRefreshStatus.
 */
- (void)beaconManager:(SBSDKManager *)manager didChangeBackgroundAppRefreshStatus:(SBSDKManagerBackgroundAppRefreshStatus)backgroundAppRefreshStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Tells the delegate that the authorization status for the application changed.

 This method is called whenever the application’s ability to use location services changes.
 Changes can occur because the user allowed or denied the use of location services for your
 application or for the system as a whole.

 @param manager             Beacon manager.
 @param authorizationStatus New authorizationStatus.
 */
- (void)beaconManager:(SBSDKManager *)manager didChangeAuthorizationStatus:(SBSDKManagerAuthorizationStatus)authorizationStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when the connection status to the Sensorberg Beacon Management
 Platform changes.

 @param manager         Beacon manager
 @param connectionState Indicates if the application is connected to the Sensorberg
                        Beacon Management Platform.
 */
- (void)beaconManager:(SBSDKManager *)manager didChangeSensorbergPlatformConnectionState:(SBSDKManagerConnectionState)connectionState __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when the reachability status to the Sensorberg Beacon Management
 Platform changes.

 @param manager           Beacon manager
 @param reachabilityState Indicates if the Sensorberg Beacon Management Platform is reachable.
 */
- (void)beaconManager:(SBSDKManager *)manager didChangeSensorbergPlatformReachabilityState:(SBSDKManagerReachabilityState)reachabilityState __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when beacon monitoring started.

 This delegate method is being called for each single region to be monitored.

 @param manager Beacon manager.
 @param region  Beacon region to be monitored.
 */
- (void)beaconManager:(SBSDKManager *)manager didStartMonitoringForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a region monitoring error has occurred.
 
 Error types are defined in "CLError.h".

 @param manager Beacon manager.
 @param region  Beacon region that failed.
 @param error   An error object containing the error code that indicates why region monitoring failed.
 */
- (void)beaconManager:(SBSDKManager *)manager monitoringDidFailForRegion:(CLRegion *)region withError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when beacon ranging started.

 This delegate method is being called for each single region to be ranged.

 @param manager Beacon manager.
 @param region  Beacon region to be ranged.
 */
- (void)beaconManager:(SBSDKManager *)manager didStartRangingForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when beacon ranging stopped.

 This delegate method is being called for each single region where ranged did stop.

 @param manager Beacon manager.
 @param region  Beacon region where ranging stopped.
 */
- (void)beaconManager:(SBSDKManager *)manager didStopRangingForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a region ranging error has occurred.

 Error types are defined in "CLError.h".

 @param manager Beacon manager.
 @param region  Beacon region that failed.
 @param error   An error object containing the error code that indicates why region ranging failed.
 */
- (void)beaconManager:(SBSDKManager *)manager rangingDidFailForRegion:(CLRegion *)region withError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when Bluetooth is turned off.

 @param manager             Beacon manager.
 @param authorizationStatus Bluetooth status that caused the failure.
 */
- (void)beaconManager:(SBSDKManager *)manager bluetoothDidFailWithBluetoothStatus:(SBSDKManagerBluetoothStatus)bluetoothStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when using Background App Refresh is unavailable.

 @param manager             Beacon manager.
 @param authorizationStatus Background App Refresh status that caused the failure.
 */
- (void)beaconManager:(SBSDKManager *)manager backgroundAppRefreshDidFailWithBackgroundAppRefreshStatus:(SBSDKManagerBackgroundAppRefreshStatus)backgroundAppRefreshStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when accessing the location services is unavailable.

 @param manager             Beacon manager.
 @param authorizationStatus Authorization status that caused the failure.
 */
- (void)beaconManager:(SBSDKManager *)manager authorizationDidFailWithAuthorizationStatus:(SBSDKManagerAuthorizationStatus)authorizationStatus __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a beacon region has been entered and is about to be resolved.

 This delegate method is being called for each single detected beacon that is part of the
 beacons regions.
 
 It will only resolve into a beacon action if the specific beacon has an active campaign
 at the Sensorberg Beacon Management Platform.

 @param manager Beacon manager.
 @param beacon  Detected beacon.
 */
- (void)beaconManager:(SBSDKManager *)manager didDetectBeaconEnterEventForBeacon:(CLBeacon *)beacon __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a beacon region has been left and is about to be resolved.

 This delegate method is being called for each single detected beacon that is part of the
 beacons regions.

 It will only resolve into a beacon action if the specific beacon has an active campaign
 at the Sensorberg Beacon Management Platform.

 @param manager Beacon manager.
 @param beacon  Detected beacon.
 */
- (void)beaconManager:(SBSDKManager *)manager didDetectBeaconExitEventForBeacon:(CLBeacon *)beacon __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when the array holding detected beacon objects has been updated.

 @param manager         Beacon manager.
 @param detectedBeacons Array holding detected beacons.
 */
- (void)beaconManager:(SBSDKManager *)manager didUpdateDetectedBeacons:(NSArray *)detectedBeacons __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a beacon action has been resolved.

 This delegate method is being called when the app is active, for each single action
 and it asks to display an in app message.

 @param manager  Beacon manager.
 @param actionId Id of the beacon action.
 @param title    Title of the beacon action.
 @param message  Message of the beacon action.
 */
- (void)beaconManager:(SBSDKManager *)manager didResolveBeaconActionWithId:(NSString *)actionId displayInAppMessageWithTitle:(NSString *)title message:(NSString *)message __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a beacon action has been resolved.

 This delegate method is being called when the app is active, for each single action
 and it asks to display an in app message and open an URL.

 @param manager  Beacon manager.
 @param actionId Id of the beacon action.
 @param title    Title of the beacon action.
 @param message  Message of the beacon action.
 @param url      URL to be visited.
 */
- (void)beaconManager:(SBSDKManager *)manager didResolveBeaconActionWithId:(NSString *)actionId displayInAppMessageWithTitle:(NSString *)title message:(NSString *)message url:(NSURL *)url __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a beacon action has been resolved.

 This delegate method is being called when the app is in the background, for each single action
 and it asks to display a local notification.
 
 As local notification do not have a title property, the title is omitted.

 @param manager  Beacon manager.
 @param actionId Id of the beacon action.
 @param message  Message of the beacon action.
 */
- (void)beaconManager:(SBSDKManager *)manager didResolveBeaconActionWithId:(NSString *)actionId displayLocalNotificationWithMessage:(NSString *)message __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a beacon action has been resolved.

 This delegate method is being called when the app is in the background, for each single action
 and it asks to display a local notification and open an URL.

 As local notification do not have a title property, the title is omitted.

 @param manager  Beacon manager.
 @param actionId Id of the beacon action.
 @param message  Message of the beacon action.
 @param url      URL to be visited.
 */
- (void)beaconManager:(SBSDKManager *)manager didResolveBeaconActionWithId:(NSString *)actionId displayLocalNotificationWithMessage:(NSString *)message url:(NSURL *)url __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

/**
 Delegate method invoked when a beacon action could not be resolved.

 @param manager Beacon manager.
 @param error   If an error occurs it contains an `NSError` object
                that describes the problem.
 */
- (void)beaconManager:(SBSDKManager *)manager resolveBeaconActionsDidFailWithError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_TBD, __IPHONE_7_0);

@end
