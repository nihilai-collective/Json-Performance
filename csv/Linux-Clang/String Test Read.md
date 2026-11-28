
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1394.37 | 0.0546889 | 291.457ms | 4215 | 160 | 397.701 | 2882.83 | 0.168738 | 1.76039 | 1(Win) | true |
| Glaze | 1013.29 | 0.0576528 | 390.757ms | 4215 | 40 | 209.231 | 3967 | 0.159396 | 2.42709 | 2(Loss) | true |
| simdjson (ondemand) | 834.27 | 0.118621 | 492.541ms | 4215 | 30 | 979.995 | 4818.27 | 0.00830243 | 2.9528 | 3(Loss) | true |
