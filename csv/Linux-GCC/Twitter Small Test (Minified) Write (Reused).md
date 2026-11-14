
----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10293 | 0.144711 | 746.202ms | 2963 | 640 | 101.01 | 274.531 | 0.00683029 | 0.586264 | 1.31455 | 0.195748 | 0.00033855 | 2.47848e-05 | 4.2187e-06 | 1(Win) | true |
| simdjson (reflection) | 7563.65 | 0.132222 | 757.45ms | 2963 | 2560 | 624.671 | 373.595 | 0.15826 | 0.754338 | 1.75363 | 0.251435 | 0.000338419 | 3.16402e-05 | 1.25243e-05 | 2(Loss) | true |
| Glaze | 6727.48 | 0.186437 | 758.825ms | 2963 | 2560 | 1569.87 | 420.029 | 0.00223194 | 0.840972 | 2.53156 | 0.365171 | 0.000338682 | 4.71967e-05 | 1.58201e-05 | 3(Loss) | true |
