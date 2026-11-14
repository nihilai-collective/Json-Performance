
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1968.33 | 0.0434378 | 846.443ms | 2632 | 4890 | 1500.45 | 1275.23 | 0.025215 | 2.69426 | 10.9612 | 1.9905 | 0.000832681 | 4.08687e-05 | 6.68196e-06 | 1(Win) | true |
| simdjson (ondemand) | 1549.74 | 0.128417 | 876.314ms | 2632 | 40 | 173.046 | 1619.67 | 0.0776302 | 3.40956 | 11.7238 | 2.15843 | 0.00384688 | 1.8997e-05 | 0 | 2(Loss) | true |
