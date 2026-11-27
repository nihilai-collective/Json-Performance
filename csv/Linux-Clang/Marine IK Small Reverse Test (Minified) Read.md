
----
### Marine IK Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 337.389 | 0.17178 | 2044.43ms | 4604 | 80 | 39980.3 | 13013.8 | 0.00288163 | 15.2998 | 67.3106 | 14.8366 | 0.0178025 | 6.78758e-05 | 1.90052e-05 | 1(Win) | true |
| simdjson (ondemand) | 241.866 | 0.111821 | 2544.31ms | 4604 | 160 | 65930.5 | 18153.5 | 0.0623546 | 21.3271 | 110.267 | 22.1179 | 0.0208664 | 0.000232135 | 0.000166974 | 2(Loss) | true |
