
----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1651.37 | 0.0845223 | 1003.1ms | 4630 | 4890 | 24976.1 | 2673.85 | 0.249745 | 3.09428 | 7.82657 | 0.457884 | 0.00029151 | 3.97956e-05 | 5.16768e-06 | 1(Win) | true |
| Glaze | 971.099 | 0.0277064 | 1192.78ms | 4630 | 4890 | 7760.78 | 4546.92 | 0.00479944 | 5.2425 | 9.81166 | 0.68661 | 0.000230117 | 5.76396e-05 | 9.14283e-06 | 2(Loss) | true |
