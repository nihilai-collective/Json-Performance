
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1487.93 | 0.103882 | 262.241ms | 3862 | 320 | 2115.89 | 2475.31 | 0.189729 | 1.64616 | 1(Win) | true |
| Glaze | 920.773 | 0.169516 | 413.122ms | 3862 | 30 | 1379.31 | 4000 | 0.249377 | 2.67493 | 2(Loss) | true |
| Jsonifier (two-stage) | 597.298 | 0.0954374 | 767.6ms | 3862 | 80 | 2770.57 | 6166.25 | 0.1417 | 4.12987 | 3(Loss) | true |
| simdjson (ondemand) | 302.72 | 0.0820342 | 1256.8ms | 3862 | 30 | 2988.51 | 12166.7 | 0.32769 | 8.17046 | 4(Loss) | true |
