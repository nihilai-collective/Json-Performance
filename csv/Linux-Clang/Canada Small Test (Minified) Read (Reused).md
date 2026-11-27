
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 933.194 | 0.21782 | 1284.65ms | 4630 | 320 | 33991.1 | 4731.61 | 0.0117547 | 5.55452 | 27.4695 | 4.60821 | 0.00368723 | 4.58963e-05 | 1.61987e-05 | 1(Win) | true |
| Jsonifier (generic) | 924.276 | 0.0733116 | 1292.38ms | 4630 | 1280 | 15700.5 | 4777.26 | 0.187681 | 5.61442 | 27.6294 | 5.29482 | 0.00219543 | 5.11272e-05 | 1.29927e-05 | 2(Loss) | true |
