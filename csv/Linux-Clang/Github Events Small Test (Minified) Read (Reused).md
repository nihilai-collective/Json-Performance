
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1470.15 | 0.0503886 | 835.509ms | 1691 | 2560 | 782.113 | 1096.94 | 0.0146337 | 3.63348 | 13.2448 | 2.52513 | 0.00111181 | 0.00010834 | 1.50152e-05 | 1(Win) | true |
| simdjson (ondemand) | 1362.97 | 0.292083 | 844.52ms | 1691 | 30 | 358.303 | 1183.2 | 0.152362 | 3.98894 | 15.2496 | 2.52986 | 0.00114331 | 0.000216834 | 5.91366e-05 | 2(Loss) | true |
