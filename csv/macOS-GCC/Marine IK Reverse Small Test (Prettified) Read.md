
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1734.98 | 0.272479 | 1114.84ms | 18245 | 40 | 29869.3 | 10028.8 | 0.98989 | 1(Win) | true |
| Jsonifier (two-stage) | 1682.11 | 0.718564 | 1047.15ms | 18245 | 160 | 883950 | 10344 | 1.2374 | 2(Loss) | true |
| Jsonifier | 1554.16 | 0.665946 | 1160.96ms | 18245 | 1280 | 7.11512e+06 | 11195.6 | 0.0214416 | 3(Loss) | true |
| simdjson (ondemand) | 1313.67 | 0.237621 | 1371.08ms | 18245 | 640 | 633968 | 13245.2 | 0.063379 | 4(Loss) | true |
| Glaze | 1173.85 | 0.608509 | 1540.57ms | 18245 | 1280 | 1.04137e+07 | 14822.8 | 0.0889728 | 5(Loss) | true |
