
----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1703.88 | 0.0842714 | 1009.65ms | 4918 | 4890 | 26312.8 | 2752.63 | 0.0899311 | 3.0215 | 8.83937 | 0.555308 | 0.000478523 | 0.000167824 | 9.41826e-05 | 1(Win) | true |
| Glaze | 861.697 | 0.0469922 | 1245.73ms | 4604 | 4890 | 28036.4 | 5095.43 | 0.12251 | 5.94836 | 12.437 | 0.970896 | 0.00104244 | 7.87081e-05 | 2.76722e-05 | 2(Loss) | true |
