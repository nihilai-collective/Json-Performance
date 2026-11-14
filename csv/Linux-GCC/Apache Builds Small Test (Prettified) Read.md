
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2357.97 | 0.160038 | 866.41ms | 3370 | 640 | 3045.17 | 1362.99 | 0.0135254 | 2.25605 | 9.0276 | 1.58012 | 0.000532734 | 0.000197515 | 0.000135386 | 1(Win) | true |
| simdjson (ondemand) | 1952.05 | 0.07106 | 882.995ms | 3370 | 4890 | 6693.25 | 1646.41 | 0.0489484 | 2.70111 | 9.39021 | 1.68338 | 0.00226648 | 5.29149e-05 | 1.02553e-05 | 2(Loss) | true |
