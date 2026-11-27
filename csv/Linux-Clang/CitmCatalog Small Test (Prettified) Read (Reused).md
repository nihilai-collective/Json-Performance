
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2310.05 | 0.194657 | 1171.71ms | 9739 | 320 | 19600.8 | 4020.62 | 0.00365318 | 2.24812 | 9.53507 | 1.59657 | 0.00169679 | 6.44958e-05 | 3.27292e-05 | 1(Win) | true |
| simdjson (ondemand) | 2281.08 | 0.093525 | 1192.96ms | 9739 | 1280 | 18561.5 | 4071.69 | 0.178126 | 2.2797 | 9.50857 | 1.46134 | 0.00242108 | 4.98158e-05 | 2.41458e-05 | 2(Loss) | true |
