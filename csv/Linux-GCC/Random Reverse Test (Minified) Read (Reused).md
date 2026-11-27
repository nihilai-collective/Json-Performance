
----
### Random Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 984.693 | 0.0865152 | 5739.42ms | 409725 | 320 | 3.77153e+07 | 396818 | 0.180252 | 5.1862 | 25.1434 | 4.95329 | 0.0114832 | 0.0132947 | 1.16694e-05 | 1(Win) | true |
| simdjson (ondemand) | 496.158 | 0.162072 | 5326.04ms | 409725 | 40 | 6.51658e+07 | 787540 | 0.0663568 | 10.3117 | 43.8515 | 8.73732 | 0.0323613 | 0.0222142 | 3.81964e-05 | 2(Loss) | true |
