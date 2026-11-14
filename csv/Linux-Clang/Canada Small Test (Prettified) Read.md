
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2171.01 | 0.0600945 | 1252.11ms | 11579 | 4890 | 45687.3 | 5086.38 | 0.0982889 | 2.34061 | 11.1648 | 2.03826 | 0.00197927 | 3.01123e-05 | 7.01149e-06 | 1(Win) | true |
| Jsonifier | 1912.35 | 0.0551178 | 1319.55ms | 11579 | 4890 | 49533.8 | 5774.37 | 0.0698278 | 2.65154 | 11.951 | 2.61465 | 0.00426377 | 5.3743e-05 | 2.69333e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1780.55 | 0.054801 | 1363.85ms | 11579 | 4890 | 56483.5 | 6201.8 | 0.0293623 | 2.84503 | 13.006 | 2.16495 | 0.00133202 | 2.53615e-05 | 6.07545e-06 | 3(Loss) | true |
| Glaze | 1469.17 | 0.053134 | 1489.08ms | 11579 | 4890 | 77992.6 | 7516.22 | 0.124521 | 3.44204 | 14.9296 | 2.88825 | 0.004445 | 8.13298e-05 | 3.92608e-05 | 4(Loss) | true |
