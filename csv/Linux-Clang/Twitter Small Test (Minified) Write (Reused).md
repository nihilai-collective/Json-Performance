
----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10109 | 0.242658 | 760.561ms | 2963 | 4890 | 2249.79 | 279.526 | 1.06363 | 0.575138 | 1.30948 | 0.201823 | 0.000338117 | 3.24382e-05 | 4.14105e-06 | 1(Win) | true |
| Glaze | 4432.9 | 0.469401 | 798.35ms | 2963 | 640 | 5730.02 | 637.447 | 0.537338 | 1.2065 | 2.73068 | 0.379345 | 0.000337496 | 4.32416e-05 | 2.63669e-06 | 2(Loss) | true |
