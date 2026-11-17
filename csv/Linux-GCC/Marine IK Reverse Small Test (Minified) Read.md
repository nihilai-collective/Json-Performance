
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 849.351 | 0.052073 | 1241ms | 4604 | 2560 | 18550.7 | 5169.49 | 0.364596 | 6.06314 | 24.6661 | 5.45582 | 0.0051029 | 7.51724e-05 | 3.67378e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 741.156 | 0.0349181 | 1325.02ms | 4604 | 2560 | 10954.5 | 5924.14 | 0.0464154 | 6.99141 | 29.1405 | 5.84796 | 0.00290101 | 0.000115558 | 7.26271e-05 | 2(Loss) | true |
| Glaze | 658.743 | 0.114052 | 1392.12ms | 4604 | 320 | 18492.4 | 6665.29 | 0.0303252 | 7.85578 | 33.6911 | 6.93245 | 0.00403725 | 1.22176e-05 | 1.35752e-06 | 3(Loss) | true |
| simdjson (reflection) | 621.427 | 0.0800374 | 1443.15ms | 4604 | 160 | 5116.79 | 7065.54 | 0.0310582 | 8.34013 | 31.2881 | 6.03644 | 0.00571107 | 7.05908e-05 | 3.93679e-05 | 4(Loss) | true |
| simdjson (ondemand) | 500.378 | 0.0277649 | 1607.67ms | 4604 | 4890 | 29025.2 | 8774.79 | 0.00584232 | 10.2757 | 37.8312 | 7.69505 | 0.00488719 | 0.000142492 | 8.85244e-05 | 5(Loss) | true |
