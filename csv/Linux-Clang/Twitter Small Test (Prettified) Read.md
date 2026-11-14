
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2646.51 | 0.240618 | 870.741ms | 3808 | 4890 | 53310.4 | 1372.22 | 0.0522222 | 1.97039 | 6.81828 | 1.02574 | 0.000586592 | 4.44656e-05 | 1.18682e-05 | 1(Win) | true |
| Glaze | 2507.93 | 0.193002 | 880.481ms | 3808 | 2560 | 19995.3 | 1448.05 | 0.12033 | 2.07289 | 8.39995 | 1.49133 | 0.000516491 | 5.27262e-05 | 2.15418e-05 | 2(Loss) | true |
| Jsonifier | 1853.81 | 0.264581 | 934.719ms | 3808 | 2560 | 68773.9 | 1958.99 | 0.231903 | 2.78163 | 7.09743 | 1.35163 | 0.000554035 | 8.86292e-05 | 4.35965e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1309.62 | 0.0789125 | 1015.3ms | 3808 | 4890 | 23415.4 | 2773 | 0.102798 | 3.91608 | 13.1767 | 2.19984 | 0.000555874 | 5.0534e-05 | 1.05257e-05 | 4(Loss) | true |
