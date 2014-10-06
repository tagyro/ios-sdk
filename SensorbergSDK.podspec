Pod::Spec.new do |s|
  s.name                    = "SensorbergSDK"
  s.version                 = "0.7.0"
  s.summary                 = "iOS SDK for handling iBeacon technology via the Sensorberg Beacon Management Platform."
  s.homepage                = "http://www.sensorberg.com"
  s.social_media_url        = 'https://twitter.com/sensorberg'
  s.authors                 = { "Max Horvath" => "max@sensorberg.com" }
  s.license                 = { :type => "Copyright",
                                :text => "Copyright 2013-2014 Sensorberg GmbH. All rights reserved." }
  s.source                  = { :git => "https://github.com/sensorberg-dev/ios-sdk.git",
                                :tag => s.version.to_s }

  s.ios.deployment_target   = '7.0'
  s.requires_arc            = true

  s.ios.vendored_frameworks = 'SensorbergSDK.framework'

  s.frameworks              = 'CoreBluetooth', 'CoreGraphics', 'CoreLocation', 'Foundation', 'MobileCoreServices', 'Security', 'SystemConfiguration'
end
