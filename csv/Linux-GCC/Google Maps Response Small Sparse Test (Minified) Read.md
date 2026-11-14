
----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2234.38 | 0.0905019 | 902.557ms | 4390 | 160 | 460.097 | 1873.73 | 0.0296956 | 2.35333 | 10.6829 | 1.87039 | 0.00174972 | 9.96583e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1908.75 | 0.0513443 | 956.923ms | 4390 | 2560 | 3246.78 | 2193.38 | 0.0211262 | 2.74617 | 11.5507 | 1.92508 | 0.00195339 | 2.18892e-05 | 3.38126e-06 | 2(Loss) | true |
