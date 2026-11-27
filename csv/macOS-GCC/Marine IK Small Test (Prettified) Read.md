
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2006.16 | 0.262547 | 878.285ms | 18245 | 640 | 331858 | 8673.2 | 0.179541 | 1(Win) | true |
| Jsonifier (two-stage) | 1956.73 | 0.128354 | 899.351ms | 18245 | 2560 | 333493 | 8892.3 | 0.0258584 | 2(Loss) | true |
| simdjson (reflection) | 1528.85 | 0.394598 | 1086.81ms | 18245 | 1280 | 2.58156e+06 | 11381 | 0.549528 | 3(Loss) | true |
| Glaze | 1337.29 | 0.120105 | 1348.43ms | 18245 | 80 | 19536.4 | 13011.2 | 0.0982801 | 4(Loss) | true |
| simdjson (ondemand) | 1324.75 | 0.167823 | 1370.71ms | 18245 | 640 | 310960 | 13134.4 | 0.0060905 | 5(Loss) | true |
