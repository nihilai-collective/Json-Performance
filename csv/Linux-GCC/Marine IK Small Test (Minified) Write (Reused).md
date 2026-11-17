
----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1586.5 | 0.0365475 | 281.24ms | 4604 | 80 | 81.8456 | 2767.55 | 0.0848406 | 1.54723 | 1(Win) | true |
| simdjson (reflection) | 1373.92 | 0.176327 | 346.539ms | 4918 | 2560 | 92753.7 | 3413.72 | 0.134198 | 1.78847 | 2(Loss) | true |
| Glaze | 1147.14 | 0.064324 | 397.316ms | 4604 | 40 | 242.461 | 3827.53 | 0.0198166 | 2.14368 | 3(Loss) | true |
