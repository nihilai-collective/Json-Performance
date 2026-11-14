
----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 714.34 | 0.082946 | 1352.81ms | 4630 | 160 | 4205.93 | 6181.24 | 0.0583078 | 7.26173 | 36.4246 | 6.66436 | 0.00604887 | 2.42981e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 680.584 | 0.0545424 | 1371.83ms | 4630 | 2560 | 32055.8 | 6487.82 | 0.0239087 | 7.49918 | 36.322 | 7.10238 | 0.00393063 | 5.32364e-05 | 1.88985e-05 | 2(Loss) | true |
