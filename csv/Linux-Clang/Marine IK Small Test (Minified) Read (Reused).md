
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 645.137 | 0.0577481 | 1500.46ms | 4604 | 640 | 9886.06 | 6805.87 | 0.0234228 | 8.02877 | 31.7843 | 6.68549 | 0.0102672 | 4.07255e-05 | 3.73317e-06 | 1(Win) | true |
| simdjson (ondemand) | 618.927 | 0.0446836 | 1526.78ms | 4604 | 1280 | 12861.7 | 7094.07 | 0.00445995 | 8.3662 | 34.4881 | 6.06147 | 0.00898098 | 4.37799e-05 | 7.29664e-06 | 2(Loss) | true |
