
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2128.56 | 0.0407172 | 847.854ms | 2821 | 2560 | 677.998 | 1263.91 | 0.00380159 | 2.49698 | 9.19 | 1.70188 | 0.000663135 | 5.70498e-05 | 8.72364e-06 | 1(Win) | true |
| simdjson (ondemand) | 1975.32 | 0.0557486 | 854.272ms | 2821 | 2560 | 1475.84 | 1361.96 | 0.0389353 | 2.68196 | 10.0411 | 1.56257 | 0.000709522 | 3.39252e-05 | 1.06622e-05 | 2(Loss) | true |
