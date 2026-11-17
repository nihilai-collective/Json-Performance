
----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10405.6 | 0.260417 | 757.66ms | 2632 | 4890 | 1929.67 | 241.223 | 0.0410968 | 0.569407 | 1.87804 | 0.301672 | 0.0005459 | 4.45982e-05 | 5.98268e-06 | 1(Win) | true |
| Glaze | 3456.72 | 0.185049 | 806.096ms | 2632 | 2560 | 4622.27 | 726.143 | 0.0238253 | 1.55463 | 4.77014 | 0.742781 | 0.000389438 | 6.60441e-05 | 1.00921e-05 | 2(Loss) | true |
