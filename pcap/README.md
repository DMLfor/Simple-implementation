## pcap - 包解析器

在 Linux C 环境编写的 pcap 解析器，暂时只能解析TCP包。

## Compille and Run

```
make

./pcap filename

```
## Performance
`
Magic : 0xa1b2c3d4
Major : 0x0002
Minor : 0x0004
ThisZone : 0x00000000
SigFigs ：0x00000000
SapLen : 0x00040000
LinkType : 0x00000001

time : 1499998587
caplen : 74
len : 74

ETH dst macIP :00:50:56:ef:a5:21
ETH src macIP :00:0c:29:02:db:c7
ETH type :08

IP version : 4
IP header\_len : 5
IP diff serciece: 0x00
IP package len : 60
IP ident : 58272
IP flags : 0x02
IP offset : 0
IP ttl : 64
IP protocol : TCP
IP checksum : 0x1612
IP src ip : 192.168.234.128
IP dst ip : 123.206.26.18

The IPpack check sum is :  0x1612

TCP src port : 42102
TCP dst prot : 80
TCP seq : 3795169034
TCP ack : 0
TCP header len : 5
TCP flags : 0x002
TCP window size : 29200
TCP check sum: 0x4138
TCP surgent point: 0
`

