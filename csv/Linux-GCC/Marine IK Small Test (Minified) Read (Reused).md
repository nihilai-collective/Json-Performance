
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 650.777 | 0.0717212 | 1488.3ms | 4604 | 320 | 7492.94 | 6746.89 | 0.384159 | 7.96259 | 30.7285 | 6.26868 | 0.00891209 | 4.27617e-05 | 2.71503e-06 | 1(Win) | true |
| simdjson (ondemand) | 647.699 | 0.0539689 | 1491.55ms | 4604 | 1280 | 17132.5 | 6778.95 | 0.102859 | 7.98207 | 32.4466 | 6.03345 | 0.0100398 | 5.29431e-05 | 1.35752e-05 | 2(Loss) | true |
