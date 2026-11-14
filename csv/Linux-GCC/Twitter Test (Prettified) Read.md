
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2470.59 | 0.0567294 | 7496.17ms | 360584 | 1280 | 7.98067e+06 | 139190 | 0.0844581 | 2.04707 | 7.99867 | 1.40003 | 0.00415084 | 0.000354663 | 7.64602e-06 | 1(Win) | true |
| simdjson (ondemand) | 2151.23 | 0.058334 | 8577.25ms | 360584 | 1280 | 1.11299e+07 | 159852 | 0.218381 | 2.36275 | 8.22613 | 1.3562 | 0.0102339 | 0.00183731 | 1.29131e-05 | 2(Loss) | true |
