
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 836.932 | 0.140725 | 1267.03ms | 4604 | 1280 | 69765.5 | 5246.2 | 0.0166666 | 6.08565 | 24.3034 | 5.30017 | 0.00681557 | 4.29314e-05 | 6.10882e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 728.462 | 0.0810377 | 1347.35ms | 4604 | 4890 | 116665 | 6027.38 | 0.139974 | 6.96875 | 29.2083 | 6.06234 | 0.00601735 | 7.80419e-05 | 3.01152e-05 | 2(Loss) | true |
| Glaze | 631.48 | 0.0850848 | 1443.16ms | 4604 | 2560 | 89597.6 | 6953.06 | 0.0299351 | 8.04339 | 33.1649 | 6.74664 | 0.00693079 | 8.56931e-05 | 2.94411e-05 | 3(Loss) | true |
| simdjson (ondemand) | 512.28 | 0.0954689 | 1605.01ms | 4604 | 2560 | 171404 | 8570.93 | 0.0102373 | 9.91408 | 39.9543 | 7.13879 | 0.00771722 | 0.000218051 | 0.000107838 | 4(Loss) | true |
