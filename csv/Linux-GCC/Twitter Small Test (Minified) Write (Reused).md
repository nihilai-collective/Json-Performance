
----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9904.01 | 0.306188 | 746.417ms | 2963 | 80 | 61.053 | 285.312 | 0.570657 | 0.592664 | 1.42558 | 0.19406 | 0.000337496 | 3.37496e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 8007.03 | 0.0473298 | 754.688ms | 2963 | 2560 | 71.4216 | 352.907 | 0.35383 | 0.724181 | 1.68579 | 0.244347 | 0.000337759 | 5.18109e-05 | 1.8325e-05 | 2(Loss) | true |
| Glaze | 6619.54 | 0.245123 | 756.966ms | 2963 | 640 | 700.736 | 426.878 | 0.0366164 | 0.851969 | 2.53156 | 0.36517 | 0.000337496 | 3.74409e-05 | 1.63475e-05 | 3(Loss) | true |
