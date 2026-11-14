
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2616.81 | 0.113469 | 860.357ms | 3370 | 4890 | 9496.75 | 1228.17 | 0.1769 | 2.00154 | 8.08902 | 1.36499 | 0.000769268 | 5.65558e-05 | 1.32287e-05 | 1(Win) | true |
| Jsonifier | 2094.71 | 0.295118 | 886.302ms | 3370 | 640 | 13121.5 | 1534.28 | 0.0570991 | 2.47942 | 8.80979 | 1.74154 | 0.00137658 | 9.41209e-05 | 1.90096e-05 | 2(Loss) | true |
| Glaze | 2029.23 | 0.0928449 | 914.811ms | 3370 | 4890 | 10573.6 | 1583.79 | 0.0386424 | 2.54144 | 10.7682 | 2.06172 | 0.00214493 | 6.28061e-05 | 1.51705e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1720.64 | 0.101489 | 951.989ms | 3370 | 2560 | 9199.33 | 1867.84 | 0.201296 | 3.0045 | 10.3193 | 1.75312 | 0.00420843 | 7.5459e-05 | 2.3878e-05 | 4(Loss) | true |
