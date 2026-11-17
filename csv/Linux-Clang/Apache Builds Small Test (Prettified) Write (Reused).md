
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13282.2 | 0.343235 | 756.384ms | 3643 | 2560 | 2063.5 | 261.571 | 0.0353805 | 0.442643 | 1.6146 | 0.266813 | 0.000274606 | 3.05595e-05 | 5.14686e-06 | 1(Win) | true |
| Glaze | 3867.25 | 0.124445 | 823.65ms | 3682 | 4890 | 6243.45 | 907.991 | 0.300821 | 1.36914 | 4.19772 | 0.680608 | 0.000276923 | 4.421e-05 | 6.2205e-06 | 2(Loss) | true |
