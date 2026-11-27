
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3635.62 | 0.0986374 | 211.47ms | 7932 | 40 | 168.481 | 2080.68 | 0.0244371 | 0.672683 | 1(Win) | true |
| Jsonifier (two-stage) | 3366.18 | 0.273595 | 227.78ms | 7932 | 2560 | 96771.3 | 2247.22 | 0.128936 | 0.726878 | 2(Loss) | true |
| Glaze | 2137.96 | 0.548642 | 361.032ms | 7932 | 80 | 30146.4 | 3538.21 | 0.017314 | 1.14965 | 3(Loss) | true |
| simdjson (ondemand) | 1035.06 | 0.304218 | 736.757ms | 7932 | 320 | 158180 | 7308.29 | 0.23535 | 2.38326 | 4(Loss) | true |
