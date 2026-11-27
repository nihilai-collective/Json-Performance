
----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1680.77 | 0.208691 | 1010.49ms | 4918 | 640 | 21704.4 | 2790.49 | 0.0428729 | 3.03364 | 8.90626 | 0.571371 | 0.000601744 | 7.33911e-05 | 2.95471e-05 | 1(Win) | true |
| Glaze | 819.247 | 0.149066 | 1264.72ms | 4604 | 640 | 40848.6 | 5359.45 | 0.299931 | 6.23576 | 12.9353 | 1.08428 | 0.00176545 | 7.7039e-05 | 2.44353e-05 | 2(Loss) | true |
