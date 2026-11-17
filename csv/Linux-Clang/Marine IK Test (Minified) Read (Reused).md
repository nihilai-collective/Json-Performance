
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 644.04 | 0.556979 | 9038.55ms | 1834197 | 30 | 6.8654e+09 | 2.71602e+06 | 1.19474 | 3.84412 | 1(Win) | true |
| simdjson (ondemand) | 634.563 | 0.106093 | 9345.98ms | 1834197 | 80 | 6.84235e+08 | 2.75658e+06 | 0.245318 | 3.90161 | 2(Loss) | true |
