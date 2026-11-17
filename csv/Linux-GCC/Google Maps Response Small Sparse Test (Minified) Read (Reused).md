
----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2316.01 | 0.0405298 | 899.25ms | 4390 | 640 | 343.539 | 1807.69 | 0.000605058 | 2.27406 | 10.3913 | 1.80091 | 0.00200847 | 1.60165e-05 | 3.55923e-07 | 1(Win) | true |
| simdjson (ondemand) | 2040.6 | 0.0783277 | 924.773ms | 4390 | 1280 | 3305.62 | 2051.67 | 0.0873526 | 2.57225 | 11.2289 | 1.84579 | 0.00225602 | 1.67284e-05 | 5.33884e-07 | 2(Loss) | true |
