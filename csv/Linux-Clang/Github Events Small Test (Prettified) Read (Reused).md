
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2703.43 | 0.195543 | 820.963ms | 2158 | 30 | 66.4782 | 761.267 | 0.170477 | 1.93692 | 7.02873 | 1.05839 | 0.000463392 | 6.17856e-05 | 0 | 1(Win) | true |
| Glaze | 2335.89 | 0.214229 | 831.557ms | 2158 | 2560 | 9120.01 | 881.048 | 0.169388 | 2.26491 | 8.59314 | 1.58248 | 0.000477692 | 4.52531e-05 | 3.07721e-06 | 2(Loss) | true |
| Jsonifier | 2260.33 | 0.318095 | 838.901ms | 2158 | 80 | 671.063 | 910.5 | 0.230112 | 2.34076 | 7.76089 | 1.41427 | 0.000463392 | 3.47544e-05 | 1.15848e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1979.32 | 0.30855 | 849.179ms | 2158 | 1280 | 13174.4 | 1039.76 | 0.0304964 | 2.65606 | 8.91336 | 1.37489 | 0.000474977 | 9.48506e-05 | 3.11342e-05 | 4(Loss) | true |
