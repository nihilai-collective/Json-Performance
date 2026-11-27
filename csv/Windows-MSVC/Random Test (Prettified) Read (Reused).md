
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1476.41 | 0.113227 | 6367.67ms | 676745 | 640 | 1.56789e+08 | 437137 | 0.146478 | 2.05847 | 1(Win) | true |
| simdjson (ondemand) | 1198.14 | 0.101172 | 7661.46ms | 676745 | 640 | 1.9008e+08 | 538662 | 0.18337 | 2.53652 | 2(Loss) | true |
