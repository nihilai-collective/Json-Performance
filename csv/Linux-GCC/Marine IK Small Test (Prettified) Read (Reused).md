
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3177.93 | 0.0650331 | 1379.27ms | 18245 | 1280 | 16228.5 | 5475.19 | 0.00540763 | 1.62026 | 6.49 | 1.10112 | 0.00129959 | 2.59489e-05 | 9.24911e-06 | 1(Win) | true |
| Jsonifier | 2901.11 | 0.0898203 | 1421.04ms | 18245 | 1280 | 37146.6 | 5997.63 | 0.0040773 | 1.78533 | 6.79397 | 1.52239 | 0.00172162 | 3.02737e-05 | 1.15186e-05 | 2(Loss) | true |
| simdjson (reflection) | 2619.36 | 0.0943246 | 1488.38ms | 18245 | 4890 | 191979 | 6642.75 | 0.16855 | 1.96882 | 7.79907 | 1.29983 | 0.000824777 | 4.51478e-05 | 2.17893e-05 | 3(Loss) | true |
| Glaze | 2037.31 | 0.0482205 | 1660.66ms | 18245 | 2560 | 43418.7 | 8540.56 | 0.113829 | 2.52714 | 10.7784 | 2.08249 | 0.00344097 | 1.81771e-05 | 6.76555e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1989.9 | 0.0502035 | 1713.32ms | 18245 | 80 | 1541.64 | 8744.05 | 0.0145792 | 2.60225 | 9.62938 | 1.75777 | 0.0014689 | 1.50726e-05 | 0 | 5(Loss) | true |
