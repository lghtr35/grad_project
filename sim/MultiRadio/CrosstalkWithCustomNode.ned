//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
package sim.MultiRadio;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth10G;
import inet.node.inet.Router;
import inet.node.inet.AdhocHost;
import inet.node.inet.WirelessHost;
import inet.node.inet.StandardHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import inet.visualizer.integrated.IntegratedMultiCanvasVisualizer;


network NodeTestEnvironment
{
    parameters:
        @display("bgb=1465,555");
    submodules:
        visualizer: IntegratedMultiCanvasVisualizer {
            parameters:
                @display("p=50,50");
        }
        radioMedium: Ieee80211DimensionalRadioMedium {
            parameters:
                @display("p=50,100");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=50,150");
        }
        host0: AdhocHost {
            parameters:
                @display("p=217,28");
        }
        host3: AdhocHost {
            parameters:
                @display("p=1232.1238,264.42");
        }
        host4: AdhocHost {
            parameters:
                @display("p=563.72876,264.42");
        }
        host1: AdhocHost {
            parameters:
                @display("p=217,489");
        }
        host2: AdhocHost {
            @display("p=91,264");
        }

}

network CampusLikeEnvironment
{
    parameters:
        @display("bgb=3313.076,1581.84");
    submodules:
        visualizer: IntegratedMultiCanvasVisualizer {
            parameters:
                @display("p=611.61255,49.437504");
        }
        radioMedium: Ieee80211DimensionalRadioMedium {
            parameters:
                @display("p=731.67505,48.025005");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=468.95004,49.437504");
        }
        EndDevice0: AdhocHost {
            parameters:
                @display("p=2794,548;i=device/device");
        }
        EndDevice1: AdhocHost {
            parameters:
                @display("p=2309,191;i=device/device");
        }
        EndDevice2: AdhocHost {
            parameters:
                @display("p=428.41498,369.09598;i=device/device");
        }
        EndDevice3: AdhocHost {
            parameters:
                @display("p=939.65686,1493.7402;i=device/device");
        }
        EndDevice4: AdhocHost {
            parameters:
                @display("p=308.45877,1216.6985;i=device/device");
        }
        EndDevice5: AdhocHost {
            parameters:
                @display("p=2245.334,1467.596;i=device/device");
        }
        MiddleDevice0: AdhocHost {
            parameters:
                @display("p=902.5275,916.80804;i=abstract/accesspoint");
        }
        MiddleDevice1: AdhocHost {
            parameters:
                @display("p=1565.1427,416.99057;i=abstract/accesspoint");
        }
        MiddleDevice2: AdhocHost {
            parameters:
                @display("p=2316.2969,916.80804;i=abstract/accesspoint");
        }
        ServerRadio: AdhocHost {
            parameters:
                @display("p=1602,858;i=device/pc2");
        }
        NoiseServer: AdhocHost {
            parameters:
                @display("p=1602,758;i=device/router");
        }
        NoiseDevice0: AdhocHost {
            @display("p=2913,1103");
        }
        NoiseDevice1: AdhocHost {
            @display("p=964.483,173.56299");
        }
        NoiseDevice2: AdhocHost {
            @display("p=166.97198,692.05493");
        }
}
