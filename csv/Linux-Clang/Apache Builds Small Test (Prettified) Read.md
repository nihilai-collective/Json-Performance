
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3161.28 | 0.333634 | 104.327ms | 3370 | 2560 | 29451.9 | 1016.64 | 0.0060705 | 0.762593 | 1(Win) | true |
| Jsonifier | 2333.02 | 0.0562124 | 139.893ms | 3370 | 80 | 47.9707 | 1377.56 | 0.0899134 | 1.04095 | 2(Loss) | true |
| Glaze | 2296.41 | 0.104801 | 142.54ms | 3370 | 40 | 86.0506 | 1399.53 | 0.114788 | 1.05734 | 3(Loss) | true |
| simdjson (ondemand) | 1919.73 | 0.0753055 | 170.774ms | 3370 | 160 | 254.303 | 1674.13 | 0.0526115 | 1.2696 | 4(Loss) | true |
