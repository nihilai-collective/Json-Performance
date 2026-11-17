
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2259.14 | 0.0457809 | 1301.73ms | 11579 | 4890 | 24486.9 | 4887.97 | 0.0368717 | 2.29851 | 11.4185 | 1.89006 | 0.000620738 | 2.96531e-05 | 1.53652e-05 | 1(Win) | true |
| Jsonifier (generic) | 1934.07 | 0.0598014 | 1389.8ms | 11579 | 1280 | 14922.1 | 5709.51 | 0.0594049 | 2.67857 | 11.6483 | 2.18689 | 0.00317493 | 2.1051e-05 | 8.02908e-06 | 2(Loss) | true |
