
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1747.73 | 0.594918 | 1027.68ms | 18245 | 320 | 1.12254e+06 | 9955.62 | 0.16979 | 1.41244 | 1(Win) | true |
| Jsonifier | 1597.04 | 0.127071 | 1123.22ms | 18245 | 40 | 7666.67 | 10895 | 0.168557 | 1.54823 | 2(Loss) | true |
| simdjson (ondemand) | 685.97 | 0.156513 | 2569.44ms | 18245 | 1280 | 2.01739e+06 | 25365.2 | 0.157755 | 3.60469 | 3(Loss) | true |
| Glaze | 585.719 | 0.218829 | 3037.9ms | 18245 | 640 | 2.70457e+06 | 29706.7 | 0.0447279 | 4.22301 | 4(Loss) | true |
