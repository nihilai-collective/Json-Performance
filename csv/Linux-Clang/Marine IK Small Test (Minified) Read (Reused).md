
----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 661.369 | 0.0526884 | 1481.67ms | 4604 | 1280 | 15661.1 | 6638.83 | 0.0595339 | 7.80621 | 31.4639 | 6.51694 | 0.00918648 | 5.41309e-05 | 1.32358e-05 | 1(Win) | true |
| simdjson (ondemand) | 608.334 | 0.0344054 | 1540.56ms | 4604 | 4890 | 30154.2 | 7217.61 | 0.183288 | 8.42298 | 34.3778 | 6.01597 | 0.0110046 | 9.64752e-05 | 4.76157e-05 | 2(Loss) | true |
