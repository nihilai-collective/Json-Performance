
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1617.08 | 0.126559 | 1109.87ms | 18245 | 80 | 14835.4 | 10760 | 0.43951 | 1.52612 | 1(Win) | true |
| Jsonifier | 1346.37 | 0.207403 | 1294.25ms | 18245 | 2560 | 1.83921e+06 | 12923.5 | 0.541122 | 1.83367 | 2(Loss) | true |
| Glaze | 587.868 | 0.373155 | 3023.55ms | 18245 | 160 | 1.95176e+06 | 29598.1 | 0.103362 | 4.20532 | 3(Loss) | true |
| simdjson (ondemand) | 383.696 | 0.0710587 | 4620.45ms | 18245 | 4890 | 5.07758e+06 | 45347.9 | 0.120448 | 6.44832 | 4(Loss) | true |
