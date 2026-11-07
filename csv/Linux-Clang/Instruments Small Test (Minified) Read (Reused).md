
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3093.82 | 0.134907 | 148.739ms | 4669 | 40 | 150.794 | 1439.22 | 0.413438 | 0.785297 | 1(Win) | true |
| Jsonifier (two-stage) | 2504.45 | 0.0494222 | 185.87ms | 4669 | 160 | 123.534 | 1777.92 | 0.273098 | 0.97404 | 2(Loss) | true |
| Glaze | 1830.39 | 0.0959612 | 252.083ms | 4669 | 40 | 217.977 | 2432.65 | 0.149817 | 1.33813 | 3(Loss) | true |
| simdjson (ondemand) | 700.454 | 0.137595 | 643.403ms | 4669 | 2560 | 195854 | 6356.89 | 0.113336 | 3.51938 | 4(Loss) | true |
