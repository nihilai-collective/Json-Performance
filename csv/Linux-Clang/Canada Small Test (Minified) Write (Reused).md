
----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1902.54 | 0.096034 | 969.938ms | 4630 | 2560 | 12716.9 | 2320.85 | 0.0877335 | 2.66588 | 7.83974 | 0.433262 | 0.000226107 | 3.06257e-05 | 6.15888e-06 | 1(Win) | true |
| Glaze | 1005.61 | 0.0294793 | 1168.97ms | 4630 | 4890 | 8193 | 4390.87 | 0.00923778 | 5.05664 | 9.27775 | 0.568036 | 0.000231927 | 4.05023e-05 | 1.30296e-05 | 2(Loss) | true |
