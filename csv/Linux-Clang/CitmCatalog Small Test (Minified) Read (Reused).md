
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1306.94 | 0.0530932 | 1137.38ms | 5092 | 1280 | 4981.41 | 3715.62 | 0.0334637 | 3.98422 | 16.7756 | 3.10207 | 0.00318944 | 3.37539e-05 | 5.83022e-06 | 1(Win) | true |
| simdjson (ondemand) | 1284.03 | 0.0589156 | 1135.46ms | 5092 | 640 | 3177.38 | 3781.94 | 0.135738 | 4.0556 | 17.0927 | 2.74764 | 0.00220352 | 2.36277e-05 | 9.20562e-07 | 2(Loss) | true |
