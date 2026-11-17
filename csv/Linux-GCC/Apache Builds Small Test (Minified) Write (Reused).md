
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14151.1 | 0.254966 | 737.698ms | 2632 | 2560 | 523.593 | 177.376 | 0.0625047 | 0.442804 | 1.52546 | 0.240502 | 0.000598849 | 1.35057e-05 | 2.96828e-06 | 1(Win) | true |
| simdjson (reflection) | 8109.03 | 0.0615042 | 756.175ms | 2632 | 2560 | 92.7862 | 309.54 | 0.111302 | 0.709398 | 2.52356 | 0.406155 | 0.000379939 | 3.0128e-05 | 1.1131e-05 | 2(Loss) | true |
| Glaze | 5224.62 | 0.235276 | 772.98ms | 2632 | 2560 | 3270.83 | 480.431 | 0.0481107 | 1.05006 | 3.59005 | 0.569529 | 0.000381572 | 2.47851e-05 | 4.60083e-06 | 3(Loss) | true |
