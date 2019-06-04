#include <iostream>
#include <type_traits>

class Transport
{
  public:
  void send(int x) {
      std::cout<<"\nTransport class is sending x: "<<x<<'\n';
  }
  
};

template<typename Transport>
class server
{
    Transport _transport;
    
public:
    void send(int x) { _transport.send(x);}
    
    // construct a server from another type that support transport class policy
    template<typename T>
    server(T&& transport) :_transport{std::forward<T>(transport) } { }
    
};

 template<typename T>
 auto make_server(T&& transport)
 {
     return server<T>{transport};   // this function passes return type as T& but we want to own the transport
                                    // therefore we need to remove the reference to create a server with
                                    // type mock_udp; therefore we use alternative make_server_alt
 }
 
  template<typename T>
 auto make_server_alt(T&& transport)
 {
     return server<std::remove_reference_t<T>>{transport};  // remove_reference_t removed the reference from 
 }                                                          // from any that is passed to it so we return a T instead of T&

struct mock_udp 
{ 
    void send(int x) {
    std::cout<<"\nMockup class is sending x: "<<x<<'\n';
    }
};

int main()
{
    mock_udp t, t1;
 //   server<mock_udp> s{t};
   auto s =make_server(t);                          // creates a server<mock_udp&>; this server does not own
   auto s_alt = make_server_alt(t1);                // creates a server<mock_udp>; this server own the passed type
   auto s_new = make_server_alt(mock_udp{});
   
    s.send(10);
    s_alt.send(15);
    s_new.send(105);
    
    auto s_trans =make_server_alt(Transport{});
    
    s_trans.send(20);
    
 
 return 0;
}