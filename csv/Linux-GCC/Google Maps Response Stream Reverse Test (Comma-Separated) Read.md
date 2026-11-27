
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 788.067 | 0.489513 | 8043.83ms | 4203058 | 80 | 4.95934e+10 | 5.08631e+06 | 0.715849 | 6.43303 | 28.9071 | 5.85404 | 0.0265158 | 0.0878439 | 0.00826147 | 1(Win) | true |
| simdjson (ondemand) | 627.597 | 0.491469 | 9946.24ms | 4203058 | 80 | 7.88227e+10 | 6.38682e+06 | 0.43944 | 8.06609 | 31.6824 | 6.63862 | 0.0279044 | 0.102578 | 0.014133 | 2(Loss) | true |
