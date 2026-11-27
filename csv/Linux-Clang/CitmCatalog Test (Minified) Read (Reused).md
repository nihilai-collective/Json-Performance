
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1426.38 | 0.154077 | 9671.08ms | 500299 | 80 | 2.12498e+07 | 334498 | 0.14824 | 3.55023 | 16.8 | 2.95734 | 0.0111874 | 0.00836292 | 3.57536e-05 | 1(Win) | true |
| simdjson (ondemand) | 1243.76 | 0.382154 | 5364.05ms | 500299 | 160 | 3.43862e+08 | 383614 | 0.0451731 | 4.04214 | 17.4948 | 2.71984 | 0.0161202 | 0.0141209 | 4.11129e-05 | 2(Loss) | true |
