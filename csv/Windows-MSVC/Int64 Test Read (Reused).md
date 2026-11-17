
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1898.19 | 0.141545 | 200.146ms | 3862 | 320 | 2413.7 | 1940.31 | 0.24217 | 1.28657 | 1(Win) | true |
| Glaze | 1017.08 | 0.127096 | 374.798ms | 3862 | 80 | 1694.62 | 3621.25 | 0.309704 | 2.41309 | 2(Loss) | true |
| Jsonifier (two-stage) | 623.196 | 0.145908 | 610.175ms | 3862 | 40 | 2974.36 | 5910 | 0.0564334 | 3.95502 | 3(Loss) | true |
| simdjson (ondemand) | 324.979 | 0.0772391 | 1147.32ms | 3862 | 30 | 2298.85 | 11333.3 | 0.17616 | 7.59959 | 4(Loss) | true |
