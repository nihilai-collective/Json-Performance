
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3047.12 | 0.0588469 | 844.064ms | 3770 | 4890 | 2357.54 | 1179.92 | 0.302255 | 1.75149 | 6.81061 | 1.12016 | 0.000266825 | 7.10051e-05 | 2.6254e-05 | 1(Win) | true |
| simdjson (ondemand) | 2801.03 | 0.122567 | 856.758ms | 3770 | 160 | 396.019 | 1283.58 | 0.0170451 | 1.8981 | 7.14881 | 1.09814 | 0.00028183 | 5.30504e-05 | 8.28912e-06 | 2(Loss) | true |
