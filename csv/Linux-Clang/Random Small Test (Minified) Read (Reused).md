
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2251.24 | 0.0228717 | 263.569ms | 5094 | 160 | 38.9755 | 2157.93 | 0.0776812 | 1.08663 | 1(Win) | true |
| Jsonifier (two-stage) | 2006.31 | 0.081929 | 294.217ms | 5094 | 40 | 157.42 | 2421.38 | 0.10094 | 1.2206 | 2(Loss) | true |
| Glaze | 1597.74 | 0.210476 | 353.452ms | 5094 | 1280 | 52422.5 | 3040.55 | 0.379113 | 1.53638 | 3(Loss) | true |
| simdjson (ondemand) | 1031.6 | 0.235638 | 515.587ms | 5094 | 2560 | 315229 | 4709.22 | 0.00217322 | 2.38656 | 4(Loss) | true |
