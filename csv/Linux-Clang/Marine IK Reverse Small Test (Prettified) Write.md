
----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5382.86 | 0.103354 | 1183.38ms | 24579 | 4890 | 99053 | 4354.63 | 0.200404 | 0.947747 | 2.97587 | 0.388584 | 0.00014506 | 1.41524e-05 | 5.70757e-06 | 1(Win) | true |
| Glaze | 3537.16 | 0.0894253 | 1411.65ms | 24579 | 4890 | 171731 | 6626.89 | 0.0487155 | 1.43834 | 3.74348 | 0.481183 | 0.000322012 | 1.58497e-05 | 5.40804e-06 | 2(Loss) | true |
