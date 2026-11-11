
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

void Send(Ptr<Socket> s, Address a) { s->SendTo(Create<Packet>(100), 0, a); }

int main()
{
  NodeContainer n(5);                    
  InternetStackHelper().Install(n);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  p2p.SetChannelAttribute("Delay", StringValue("10ms"));

  Ipv4AddressHelper ip;
  ip.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer ifc;
  for (int i = 1; i <= 4; i++)           
  {
    ifc = ip.Assign(p2p.Install(n.Get(0), n.Get(i)));
    ip.NewNetwork();
  }
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  Ptr<Socket> s = Socket::CreateSocket(n.Get(1), UdpSocketFactory::GetTypeId());
  Ptr<Socket> r = Socket::CreateSocket(n.Get(4), UdpSocketFactory::GetTypeId());
  r->Bind(InetSocketAddress(Ipv4Address::GetAny(), 9000));
  Address dest = InetSocketAddress(ifc.GetAddress(1), 9000);

  AnimationInterface anim("star.xml");
  Simulator::Schedule(Seconds(1), &Send, s, dest);
  Simulator::Run();
  Simulator::Destroy();
}