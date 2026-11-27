
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1613.4 | 0.0959455 | 1014.81ms | 4390 | 160 | 991.778 | 2594.91 | 0.0712426 | 3.24318 | 15.326 | 2.84897 | 0.00106777 | 3.84396e-05 | 9.96583e-06 | 1(Win) | true |
| simdjson (ondemand) | 1228.57 | 0.0364231 | 1092.65ms | 4390 | 2560 | 3943.87 | 3407.72 | 0.0695367 | 4.21681 | 17.7255 | 3.22779 | 0.00306262 | 4.42234e-05 | 2.00206e-05 | 2(Loss) | true |
