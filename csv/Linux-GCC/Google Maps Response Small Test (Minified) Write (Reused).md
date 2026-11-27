
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12123.3 | 0.183085 | 746.699ms | 4390 | 160 | 63.9608 | 345.337 | 0.489861 | 0.480662 | 1.89818 | 0.224374 | 0.00022779 | 1.42369e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 9028.77 | 0.634764 | 763.397ms | 4390 | 2560 | 22178.8 | 463.699 | 0.211639 | 0.621605 | 2.34487 | 0.348975 | 0.00022868 | 5.62358e-05 | 1.91308e-05 | 2(Loss) | true |
| Glaze | 4226.76 | 0.232074 | 814.717ms | 4390 | 1280 | 6763.57 | 990.505 | 0.12019 | 1.26851 | 4.36743 | 0.663098 | 0.000229392 | 4.21768e-05 | 1.92198e-05 | 3(Loss) | true |
