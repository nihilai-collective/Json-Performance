
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3091.16 | 0.135798 | 837.267ms | 3370 | 30 | 59.8034 | 1039.7 | 0.0224373 | 1.69834 | 6.87389 | 1.33947 | 0.000613254 | 9.8912e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2365.26 | 0.0890974 | 871.471ms | 3370 | 4890 | 7167.08 | 1358.79 | 0.127622 | 2.19848 | 9.03353 | 1.46469 | 0.000899553 | 6.42018e-05 | 1.49278e-05 | 2(Loss) | true |
| Glaze | 2043.58 | 0.113575 | 899.189ms | 3370 | 2560 | 8167.33 | 1572.67 | 0.0361528 | 2.54051 | 10.7683 | 2.06172 | 0.0015523 | 4.52059e-05 | 4.75241e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1712.52 | 0.0991983 | 931.375ms | 3370 | 2560 | 8872.28 | 1876.69 | 0.148357 | 3.02745 | 10.5119 | 1.77181 | 0.00370514 | 8.65866e-05 | 3.80193e-05 | 4(Loss) | true |
