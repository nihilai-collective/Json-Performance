
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3589.47 | 0.147989 | 809.822ms | 2632 | 80 | 85.6758 | 699.288 | 0.0232325 | 1.48959 | 5.79293 | 1.07827 | 0.000759878 | 2.84954e-05 | 4.74924e-06 | 1(Win) | true |
| Glaze | 2443.72 | 0.165024 | 844.382ms | 2632 | 320 | 919.419 | 1027.15 | 0.0974516 | 2.15402 | 9.47948 | 1.69947 | 0.00149364 | 5.10543e-05 | 7.12386e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2340.88 | 0.19252 | 849.391ms | 2632 | 40 | 170.461 | 1072.28 | 0.143982 | 2.24606 | 9.43731 | 1.45631 | 0.00114932 | 3.79939e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1693.06 | 0.134441 | 890.953ms | 2632 | 1280 | 5085.15 | 1482.57 | 0.0842422 | 3.10053 | 11.2223 | 1.82257 | 0.00185428 | 6.7083e-05 | 8.90483e-06 | 4(Loss) | true |
