
----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10542 | 0.221543 | 763.01ms | 3643 | 4890 | 2606.76 | 329.562 | 0.744786 | 0.539504 | 1.77272 | 0.307165 | 0.000433697 | 3.97434e-05 | 8.64476e-06 | 1(Win) | true |
| Glaze | 3514.39 | 0.125511 | 833.917ms | 3682 | 4890 | 7690.18 | 999.157 | 0.34016 | 1.49974 | 4.54407 | 0.759384 | 0.000389059 | 4.02111e-05 | 4.44322e-06 | 2(Loss) | true |
