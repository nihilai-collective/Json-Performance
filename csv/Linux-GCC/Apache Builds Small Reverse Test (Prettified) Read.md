
----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1528.39 | 0.0373341 | 932.872ms | 3370 | 4890 | 3013.79 | 2102.79 | 0.0726492 | 3.40291 | 13.489 | 2.62849 | 0.00282852 | 4.23562e-05 | 7.94937e-06 | 1(Win) | true |
| simdjson (ondemand) | 915.207 | 0.0551949 | 1075.75ms | 3370 | 2560 | 9617.42 | 3511.65 | 0.153726 | 5.64398 | 23.0407 | 4.61187 | 0.00847482 | 3.18759e-05 | 3.7092e-06 | 2(Loss) | true |
