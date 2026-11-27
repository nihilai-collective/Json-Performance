
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 917.612 | 0.145238 | 8021ms | 2090234 | 30 | 2.98645e+08 | 2.17238e+06 | 0.275866 | 5.56135 | 26.7196 | 5.06239 | 0.0267052 | 0.079285 | 0.000122682 | 1(Win) | true |
| simdjson (ondemand) | 895.037 | 0.0752691 | 8096.84ms | 2090234 | 160 | 4.49636e+08 | 2.22717e+06 | 0.0198264 | 5.64492 | 26.4289 | 4.36108 | 0.021712 | 0.0787324 | 0.0011588 | 2(Loss) | true |
