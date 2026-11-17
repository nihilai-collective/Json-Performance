
----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 713.938 | 0.168982 | 8627.96ms | 56369 | 30 | 485695 | 75297.4 | 0.00974011 | 7.21206 | 32.8781 | 6.86546 | 0.0102515 | 8.87012e-06 | 2.36537e-06 | 1(Win) | true |
| simdjson (ondemand) | 216.533 | 0.0728458 | 6660.98ms | 56369 | 160 | 5.23312e+06 | 248265 | 0.0669087 | 23.7043 | 130.769 | 27.8069 | 0.0428329 | 3.62566e-05 | 1.82946e-05 | 2(Loss) | true |
