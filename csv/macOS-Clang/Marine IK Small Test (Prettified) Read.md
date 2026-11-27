
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1964.45 | 0.0927151 | 923.832ms | 18245 | 2560 | 172643 | 8857.35 | 0.0419012 | 1(Win) | true |
| Jsonifier | 1718 | 0.55212 | 918.927ms | 18245 | 640 | 2.00119e+06 | 10127.9 | 0.863205 | 2(Loss) | true |
| Glaze | 1223.3 | 0.0751094 | 1438.42ms | 18245 | 30 | 3424.01 | 14223.7 | 0.137283 | 3(Loss) | true |
| simdjson (ondemand) | 1209.63 | 0.186571 | 1450.32ms | 18245 | 320 | 230474 | 14384.4 | 0.0034107 | 4(Loss) | true |
