
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1575.58 | 0.193181 | 1017.4ms | 4669 | 40 | 1192.23 | 2826.07 | 0.0598234 | 3.33009 | 13.9163 | 2.8006 | 0.00194903 | 3.74813e-05 | 1.60634e-05 | 1(Win) | true |
| simdjson (ondemand) | 1559.25 | 0.0463256 | 1008.93ms | 4669 | 640 | 1120.05 | 2855.67 | 0.0016415 | 3.35226 | 15.6483 | 2.29792 | 0.00164349 | 4.04931e-05 | 1.33862e-05 | 2(Loss) | true |
