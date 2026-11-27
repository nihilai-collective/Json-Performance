
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 743.055 | 1.53651 | 8283.45ms | 1834197 | 30 | 3.925e+10 | 2.3541e+06 | 0.207574 | 4.08995 | 1(Win) | true |
| Jsonifier (two-stage) | 586.751 | 1.49752 | 9761.74ms | 1834197 | 30 | 5.9793e+10 | 2.98121e+06 | 1.51519 | 5.17934 | 2(Loss) | true |
| simdjson (ondemand) | 373.165 | 0.570077 | 7516.19ms | 1834197 | 40 | 2.85639e+10 | 4.68754e+06 | 0.534858 | 8.14425 | 3(Loss) | true |
| Glaze | 327.319 | 0.718511 | 8724.81ms | 1834197 | 40 | 5.89762e+10 | 5.34411e+06 | 1.25351 | 9.28545 | 4(Loss) | true |
