
----
### Stream Formats Small Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3291.43 | 0.111823 | 7112.44ms | 16002592 | 40 | 1.07532e+09 | 4.63667e+06 | 0.151943 | 0.923319 | 1(Win) | true |
| simdjson (ondemand) | 2868.73 | 0.189033 | 8131.45ms | 16002592 | 30 | 3.03388e+09 | 5.31987e+06 | 1.44477 | 1.05936 | 2(Loss) | true |
