
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1667.71 | 0.244614 | 1084.38ms | 18245 | 30 | 19540.2 | 10433.3 | 0.16 | 1.47967 | 1(Win) | true |
| Jsonifier | 1441.57 | 0.362216 | 1218.91ms | 18245 | 640 | 1.22329e+06 | 12070 | 0.293423 | 1.71309 | 2(Loss) | true |
| simdjson (ondemand) | 706.373 | 0.125642 | 2513.7ms | 18245 | 2560 | 2.45206e+06 | 24632.6 | 0.0351925 | 3.50066 | 3(Loss) | true |
| Glaze | 557.186 | 0.161934 | 3185.88ms | 18245 | 1280 | 3.2732e+06 | 31228 | 0.607595 | 4.439 | 4(Loss) | true |
