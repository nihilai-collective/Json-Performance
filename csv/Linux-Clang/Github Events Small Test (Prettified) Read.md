
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2556.65 | 0.233378 | 811.195ms | 2158 | 4890 | 17257.9 | 804.97 | 0.303147 | 2.09079 | 6.88462 | 1.31696 | 0.000473342 | 0.000108504 | 2.67232e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2116.65 | 0.219866 | 831.407ms | 2158 | 2560 | 11699.4 | 972.305 | 0.210639 | 2.49161 | 8.943 | 1.443 | 0.000472624 | 0.000103901 | 2.73329e-05 | 2(Loss) | true |
| Glaze | 1958.86 | 0.148452 | 839.774ms | 2158 | 4890 | 11895.3 | 1050.63 | 0.104757 | 2.67623 | 9.8304 | 1.88554 | 0.00097047 | 0.000104903 | 2.56808e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1717.27 | 0.204166 | 858.157ms | 2158 | 2560 | 15326.2 | 1198.43 | 0.334408 | 3.05569 | 9.92261 | 1.61029 | 0.00104897 | 9.05063e-05 | 1.81013e-05 | 4(Loss) | true |
