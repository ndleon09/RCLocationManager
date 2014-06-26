/*
 Copyright 2012 Ricardo Caballero (hello@rcabamo.es)
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

extern NSString * const RCLocationManagerUserLocationDidChangeNotification;
extern NSString * const RCLocationManagerNotificationLocationUserInfoKey;

typedef void(^RCLocationManagerLocationUpdateBlock)(CLLocationManager *manager, CLLocation *newLocation);
typedef void (^RCLocationManagerLocationUpdateFailBlock)(CLLocationManager *manager, NSError *error);

typedef void(^RCLocationManagerRegionUpdateBlock)(CLLocationManager *manager, CLRegion *region, BOOL enter);
typedef void(^RCLocationManagerRegionUpdateFailBlock)(CLLocationManager *manager, CLRegion *region, NSError *error);

@protocol RCLocationManagerDelegate;

@interface RCLocationManager : NSObject

@property (nonatomic, assign) id<RCLocationManagerDelegate> delegate;

/**
 * @discussion the most recently retrieved user location.
 */
@property (nonatomic, readonly) CLLocation *location;

#pragma mark - Customization

// Timeout for retrieving an accurate location using blocks, default is 10 seconds
@property (nonatomic, assign) CGFloat defaultTimeout;

@property (nonatomic, assign) CLLocationDistance userDistanceFilter;
@property (nonatomic, assign) CLLocationAccuracy userDesiredAccuracy;

@property (nonatomic, assign) CLLocationDistance regionDistanceFilter;
@property (nonatomic, assign) CLLocationAccuracy regionDesiredAccuracy;

@property (nonatomic, readonly) NSSet *regions;

+ (RCLocationManager *)sharedManager;

- (id)initWithUserDistanceFilter:(CLLocationDistance)userDistanceFilter userDesiredAccuracy:(CLLocationAccuracy)userDesiredAccuracy delegate:(id<RCLocationManagerDelegate>)delegate;

+ (BOOL)locationServicesEnabled;
+ (BOOL)regionMonitoringAvailable;
+ (BOOL)regionMonitoringEnabled;
+ (BOOL)significantLocationChangeMonitoringAvailable;

- (void)startUpdatingLocation;
- (void)startUpdatingLocationWithBlock:(RCLocationManagerLocationUpdateBlock)block errorBlock:(RCLocationManagerLocationUpdateFailBlock)errorBlock;
- (void)retrieveUserLocationWithBlock:(RCLocationManagerLocationUpdateBlock)block errorBlock:(RCLocationManagerLocationUpdateFailBlock)errorBlock;
- (void)updateUserLocation;
- (void)stopUpdatingLocation;

- (void)addCoordinateForMonitoring:(CLLocationCoordinate2D)coordinate;
- (void)addCoordinateForMonitoring:(CLLocationCoordinate2D)coordinate withRadius:(CLLocationDistance)radius;

- (void)addRegionForMonitoring:(CLRegion *)region;
- (void)addRegionForMonitoring:(CLRegion *)region updateBlock:(RCLocationManagerRegionUpdateBlock)block errorBlock:(RCLocationManagerRegionUpdateFailBlock)errorBlock;
- (void)stopMonitoringForRegion:(CLRegion *)region;
- (void)stopMonitoringAllRegions;

@end

@protocol RCLocationManagerDelegate <NSObject>

@optional
- (void)locationManager:(RCLocationManager *)manager didFailWithError:(NSError *)error;
- (void)locationManager:(RCLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation;
- (void)locationManager:(RCLocationManager *)manager didEnterRegion:(CLRegion *)region;
- (void)locationManager:(RCLocationManager *)manager didExitRegion:(CLRegion *)region;
- (void)locationManager:(RCLocationManager *)manager monitoringDidFailForRegion:(CLRegion *)region withError:(NSError *)error;

@end
