clean:
	@powershell if (Test-Path FlightSimulator.zip) { rm FlightSimulator.zip }

build:	clean
	@powershell Compress-Archive -Path '*.h' -DestinationPath 'FlightSimulator.zip'
	@powershell Compress-Archive -Path '*.cpp' -DestinationPath 'FlightSimulator.zip' -Update

test:	build
	@powershell cp *.cpp C:\Users\steve\source\repos\WebSimListener\FlightSimulator\Arduino\libraries\SImListener
	@powershell cp *.h C:\Users\steve\source\repos\WebSimListener\FlightSimulator\Arduino\libraries\SImListener