
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7815.96 | 0.101857 | 300.466ms | 24893 | 80 | 765.699 | 3037.35 | 0.0675386 | 0.314016 | 1(Win) | true |
| Glaze | 4037.97 | 0.197926 | 592.672ms | 24579 | 1280 | 168974 | 5804.99 | 0.67964 | 0.610342 | 2(Loss) | true |
| simdjson (reflection) | 572.931 | 0.31458 | 4340.77ms | 24893 | 80 | 1.35926e+06 | 41435.7 | 0.150489 | 4.31862 | 3(Loss) | true |
