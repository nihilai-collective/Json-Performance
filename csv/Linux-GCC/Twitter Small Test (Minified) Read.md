
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2894.02 | 0.378918 | 817.046ms | 2889 | 1280 | 16656.8 | 952.02 | 0.016251 | 1.85372 | 6.11873 | 0.996539 | 0.000352631 | 5.30028e-05 | 9.19436e-06 | 1(Win) | true |
| Glaze | 2375.69 | 0.0723441 | 835.023ms | 2889 | 4890 | 3442.17 | 1159.73 | 0.0136929 | 2.24389 | 8.85739 | 1.54552 | 0.0003506 | 5.58497e-05 | 1.86873e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2312.3 | 0.140981 | 851.541ms | 2889 | 80 | 225.746 | 1191.53 | 0.050381 | 2.3041 | 7.92593 | 1.17653 | 0.000601419 | 8.65351e-05 | 1.29803e-05 | 3(Loss) | true |
| simdjson (reflection) | 1923.67 | 0.0990232 | 868.108ms | 2889 | 2560 | 5149.31 | 1432.25 | 0.0955571 | 2.74661 | 9.23226 | 1.30772 | 0.000350873 | 0.000126422 | 6.3414e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1314.76 | 0.210807 | 931.92ms | 2889 | 640 | 12489.7 | 2095.56 | 0.110549 | 3.96704 | 12.0893 | 2.41502 | 0.0014446 | 0.000220665 | 0.000118986 | 5(Loss) | true |
