
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1516.82 | 0.0451219 | 1014.09ms | 4390 | 2560 | 3970.76 | 2760.13 | 0.156331 | 3.4459 | 16.2403 | 2.97062 | 0.00153234 | 3.63041e-05 | 6.58457e-06 | 1(Win) | true |
| simdjson (ondemand) | 1181.05 | 0.0475024 | 1091.3ms | 4390 | 1280 | 3629.4 | 3544.84 | 0.0358484 | 4.40916 | 18.2064 | 3.31458 | 0.00431983 | 3.00755e-05 | 5.33884e-07 | 2(Loss) | true |
