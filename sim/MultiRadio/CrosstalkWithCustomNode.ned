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
import inet.node.inet.Router;
//import src.MyWirelessHost;
//import src.MyAdHoc;
import inet.node.inet.AdhocHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import inet.visualizer.integrated.IntegratedMultiCanvasVisualizer;


network MultiRadioShowcase
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
        host2: AdhocHost {
            parameters:
                @display("p=1232.1238,264.42");
        }
        host3: AdhocHost {
            parameters:
                @display("p=563.72876,264.42");
        }
        host1: AdhocHost {
            parameters:
                @display("p=217,489");
        }

}
