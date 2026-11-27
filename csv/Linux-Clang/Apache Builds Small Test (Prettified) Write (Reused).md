
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12483.1 | 0.183746 | 757.995ms | 3643 | 2560 | 669.503 | 278.316 | 0.560637 | 0.466952 | 1.66813 | 0.272303 | 0.00027525 | 1.97296e-05 | 2.35898e-06 | 1(Win) | true |
| Glaze | 3695.34 | 0.118378 | 827.307ms | 3682 | 4890 | 6187.44 | 950.231 | 0.7755 | 1.42422 | 4.19772 | 0.680609 | 0.000329076 | 2.02722e-05 | 3.27687e-06 | 2(Loss) | true |
