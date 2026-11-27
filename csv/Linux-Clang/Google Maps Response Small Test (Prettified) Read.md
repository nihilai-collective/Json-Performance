
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3489.31 | 0.118764 | 995.767ms | 9378 | 1280 | 11861 | 2563.13 | 0.203075 | 1.46735 | 6.81062 | 1.30987 | 0.0015071 | 1.5495e-05 | 1.16629e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2788.6 | 0.0809197 | 1058.06ms | 9378 | 1280 | 8621.16 | 3207.18 | 0.00752762 | 1.83714 | 8.40147 | 1.37161 | 0.0022008 | 2.35758e-05 | 4.49856e-06 | 2(Loss) | true |
| Glaze | 2347.78 | 0.0933505 | 1117.74ms | 9378 | 1280 | 16186.4 | 3809.37 | 0.0249938 | 2.1752 | 9.76061 | 1.91032 | 0.00282251 | 2.40756e-05 | 5.16501e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2212.75 | 0.153866 | 1136.04ms | 9378 | 1280 | 49505.3 | 4041.83 | 0.033644 | 2.33812 | 10.1286 | 1.59981 | 0.00151918 | 3.79045e-05 | 1.11631e-05 | 4(Loss) | true |
