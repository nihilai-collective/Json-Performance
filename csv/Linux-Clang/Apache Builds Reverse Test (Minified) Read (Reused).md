
----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1479.76 | 0.0912418 | 8077.71ms | 94653 | 160 | 495672 | 61001.9 | 0.0806189 | 3.42604 | 17.1041 | 3.3608 | 0.00769198 | 8.84811e-06 | 4.49008e-06 | 1(Win) | true |
| simdjson (ondemand) | 817.873 | 0.130442 | 6628.02ms | 94653 | 40 | 829072 | 110369 | 0.076593 | 6.17549 | 31.3209 | 6.1945 | 0.0116346 | 1.34703e-05 | 2.11298e-06 | 2(Loss) | true |
