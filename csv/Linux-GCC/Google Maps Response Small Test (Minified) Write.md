
----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11206.5 | 0.103267 | 748.925ms | 4390 | 640 | 95.2563 | 373.591 | 0.0133818 | 0.51558 | 2.01207 | 0.250569 | 0.00022779 | 2.2779e-05 | 7.11845e-07 | 1(Win) | true |
| simdjson (reflection) | 8665.73 | 0.162405 | 765.863ms | 4390 | 40 | 24.625 | 483.125 | 0.101872 | 0.655262 | 2.45854 | 0.375171 | 0.00022779 | 3.41686e-05 | 2.2779e-05 | 2(Loss) | true |
| Glaze | 3854.92 | 0.0978801 | 828.082ms | 4390 | 4890 | 5525.8 | 1086.05 | 0.409777 | 1.38591 | 4.76538 | 0.753075 | 0.000228582 | 7.55575e-05 | 3.54496e-05 | 3(Loss) | true |
