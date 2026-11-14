
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1654.23 | 0.0682466 | 1043.49ms | 4926 | 2560 | 9616.11 | 2839.87 | 0.121145 | 3.15837 | 13.962 | 2.59968 | 0.00380356 | 7.85849e-05 | 3.4257e-05 | 1(Win) | true |
| simdjson (ondemand) | 1242.95 | 0.0562309 | 1130.85ms | 4926 | 2560 | 11563 | 3779.55 | 0.0418814 | 4.18444 | 15.8973 | 2.86906 | 0.00557612 | 6.13771e-05 | 2.45826e-05 | 2(Loss) | true |
