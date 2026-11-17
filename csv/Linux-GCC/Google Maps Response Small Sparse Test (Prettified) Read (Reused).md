
----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4169.11 | 0.117249 | 972.581ms | 9378 | 640 | 4048.82 | 2145.2 | 0.144353 | 1.25794 | 5.64865 | 0.891875 | 0.00107182 | 9.33035e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3926.19 | 0.0545829 | 950.32ms | 9378 | 4890 | 7559.63 | 2277.92 | 0.113006 | 1.33335 | 5.95745 | 0.894114 | 0.00113281 | 2.17844e-05 | 9.20224e-06 | 2(Loss) | true |
