
----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 838.558 | 0.0846691 | 1048.11ms | 2821 | 640 | 4722.48 | 3208.27 | 0.0547714 | 6.2179 | 25.8107 | 4.81141 | 0.00190535 | 5.37265e-05 | 1.93859e-05 | 1(Win) | true |
| simdjson (ondemand) | 400.334 | 0.0493063 | 1397.09ms | 2821 | 2560 | 28106.5 | 6720.18 | 0.034899 | 12.8929 | 58.5154 | 11.7948 | 0.0116873 | 6.23117e-05 | 1.42625e-05 | 2(Loss) | true |
