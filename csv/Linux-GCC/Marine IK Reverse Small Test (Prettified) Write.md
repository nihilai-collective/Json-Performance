
----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7656.33 | 0.0608492 | 313.272ms | 24579 | 30 | 104.116 | 3061.57 | 0.0881124 | 0.320686 | 1(Win) | true |
| Glaze | 3794.45 | 0.135462 | 621.46ms | 24579 | 2560 | 179270 | 6177.54 | 0.0910044 | 0.649685 | 2(Loss) | true |
| simdjson (reflection) | 534.354 | 0.454647 | 4365.59ms | 24893 | 80 | 3.26389e+06 | 44427.2 | 0.765543 | 4.63046 | 3(Loss) | true |
