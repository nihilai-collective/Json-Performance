
----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6320.32 | 0.091033 | 1103.87ms | 24579 | 4890 | 55738.7 | 3708.73 | 0.088129 | 0.823186 | 1.89031 | 0.106026 | 0.000101022 | 1.40859e-05 | 5.97381e-06 | 1(Win) | true |
| Glaze | 3137.34 | 0.151533 | 1479.46ms | 24579 | 1280 | 164070 | 7471.41 | 0.0523285 | 1.64147 | 3.92176 | 0.474796 | 0.000280982 | 2.38707e-05 | 1.12838e-05 | 2(Loss) | true |
| simdjson (reflection) | 527.225 | 0.129537 | 5245.48ms | 24893 | 2560 | 8.70946e+06 | 45027.9 | 0.112029 | 9.758 | 36.801 | 6.03877 | 0.0070804 | 7.38316e-05 | 4.48168e-05 | 3(Loss) | true |
