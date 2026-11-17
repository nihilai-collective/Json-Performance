
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2665.43 | 0.031247 | 1388.52ms | 18245 | 4890 | 20345.9 | 6527.95 | 0.0472539 | 1.91199 | 7.83217 | 1.41611 | 0.00136936 | 2.54881e-05 | 1.23854e-05 | 1(Win) | true |
| Jsonifier | 2320.97 | 0.0790239 | 1488.18ms | 18245 | 640 | 22461.8 | 7496.77 | 0.0250462 | 2.22547 | 8.10918 | 1.85678 | 0.00196955 | 1.24178e-05 | 2.141e-06 | 2(Loss) | true |
| simdjson (reflection) | 2286.71 | 0.0792033 | 1500.05ms | 18245 | 640 | 23245.2 | 7609.1 | 0.0415859 | 2.22102 | 8.34546 | 1.42834 | 0.00140252 | 2.15813e-05 | 1.1647e-05 | 3(Loss) | true |
| Glaze | 1836.69 | 0.0273511 | 1684.2ms | 18245 | 2560 | 17187.2 | 9473.44 | 0.0485991 | 2.75658 | 11.7976 | 2.31461 | 0.00346291 | 6.09756e-05 | 3.5562e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1830.35 | 0.0441951 | 1688.28ms | 18245 | 2560 | 45186.5 | 9506.27 | 0.101253 | 2.77259 | 10.0311 | 1.85733 | 0.0019941 | 4.81939e-05 | 2.51781e-05 | 5(Loss) | true |
