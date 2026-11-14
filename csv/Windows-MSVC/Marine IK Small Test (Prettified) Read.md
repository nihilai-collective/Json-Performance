
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1804.96 | 0.117699 | 970.413ms | 18245 | 30 | 3862.07 | 9640 | 0.0692042 | 1.6781 | 1(Win) | true |
| Jsonifier | 1566.42 | 0.147397 | 1113.66ms | 18245 | 640 | 171564 | 11108 | 0.0295309 | 1.93597 | 2(Loss) | true |
| simdjson (ondemand) | 1178.81 | 0.0619163 | 1471.75ms | 18245 | 4890 | 408430 | 14760.4 | 0.124536 | 2.57407 | 3(Loss) | true |
| Glaze | 974.386 | 0.144168 | 1796.54ms | 18245 | 640 | 424174 | 17857.2 | 0.0174969 | 3.11516 | 4(Loss) | true |
