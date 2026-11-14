
----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 706.816 | 0.0407871 | 8635.3ms | 56369 | 1280 | 1.23175e+06 | 76056 | 0.043283 | 7.20553 | 32.9022 | 6.87073 | 0.0102175 | 1.93895e-05 | 8.9117e-06 | 1(Win) | true |
| simdjson (ondemand) | 216.56 | 0.0664375 | 6632.74ms | 56369 | 320 | 8.70364e+06 | 248235 | 0.0964574 | 23.5436 | 130.76 | 27.7906 | 0.0348379 | 3.415e-05 | 1.44694e-05 | 2(Loss) | true |
