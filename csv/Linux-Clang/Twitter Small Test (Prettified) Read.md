
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2813.07 | 0.0893025 | 846.506ms | 3770 | 4890 | 6370.27 | 1278.09 | 0.035193 | 1.88759 | 7.16234 | 1.19655 | 0.000297147 | 0.00010008 | 3.70485e-05 | 1(Win) | true |
| simdjson (ondemand) | 2572.61 | 0.0503851 | 859.794ms | 3770 | 4890 | 2424.65 | 1397.55 | 0.0393477 | 2.06063 | 7.77109 | 1.16313 | 0.000268995 | 4.44799e-05 | 1.23133e-05 | 2(Loss) | true |
