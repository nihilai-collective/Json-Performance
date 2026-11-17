
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1908.77 | 0.107991 | 4007.48ms | 65103 | 2560 | 3.1587e+06 | 32527.3 | 0.128996 | 2.65232 | 9.08906 | 1.55637 | 0.00797078 | 0.000145347 | 7.31173e-05 | 1(Win) | true |
| Jsonifier | 1536.64 | 0.1698 | 4811.49ms | 65103 | 1280 | 6.02485e+06 | 40404.6 | 0.125952 | 3.28835 | 9.70233 | 1.84918 | 0.0108103 | 0.000207412 | 9.92658e-05 | 2(Loss) | true |
| Glaze | 1493.3 | 0.100658 | 4908.61ms | 65103 | 1280 | 2.24191e+06 | 41577.2 | 0.16172 | 3.38742 | 10.9298 | 2.10766 | 0.0229243 | 7.59014e-05 | 3.04085e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1276.58 | 0.0486926 | 5631.93ms | 65103 | 4890 | 2.74246e+06 | 48635.4 | 0.0997859 | 3.96382 | 12.8391 | 2.27454 | 0.00310729 | 0.000122367 | 7.33367e-05 | 4(Loss) | true |
