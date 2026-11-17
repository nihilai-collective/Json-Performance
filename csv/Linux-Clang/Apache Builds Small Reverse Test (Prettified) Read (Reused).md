
----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1759.26 | 0.038096 | 911.991ms | 3370 | 4890 | 2368.48 | 1826.84 | 0.027802 | 2.99207 | 12.162 | 2.30653 | 0.00354517 | 5.30969e-05 | 2.44549e-05 | 1(Win) | true |
| simdjson (ondemand) | 1027.58 | 0.075854 | 1044.54ms | 3370 | 1280 | 7204.37 | 3127.63 | 0.0183879 | 5.12583 | 22.7214 | 4.25341 | 0.00801906 | 6.56065e-05 | 3.176e-05 | 2(Loss) | true |
