
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2260.71 | 0.587717 | 824.004ms | 2158 | 320 | 9160.1 | 910.347 | 0.132336 | 2.40627 | 8.08156 | 1.31511 | 0.00077763 | 0.000140466 | 7.2405e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2123.81 | 0.173031 | 828.791ms | 2158 | 80 | 224.911 | 969.025 | 0.0721854 | 2.52796 | 8.74189 | 1.34106 | 0.00139597 | 4.63392e-05 | 0 | 2(Loss) | true |
| Glaze | 2008.53 | 0.0815316 | 822.83ms | 2158 | 2560 | 1786.65 | 1024.65 | 0.0549653 | 2.66345 | 9.71733 | 1.89852 | 0.000477873 | 8.59809e-05 | 3.20392e-05 | 3(Loss) | true |
| Jsonifier | 1979.15 | 0.322084 | 826.102ms | 2158 | 4890 | 54851.8 | 1039.85 | 0.206138 | 2.69951 | 8.66172 | 1.52641 | 0.000471826 | 8.23492e-05 | 3.00399e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1896.23 | 0.209921 | 843.054ms | 2158 | 80 | 415.26 | 1085.33 | 0.204588 | 2.82913 | 8.6367 | 1.36098 | 0.000474977 | 5.7924e-05 | 0 | 5(Loss) | true |
