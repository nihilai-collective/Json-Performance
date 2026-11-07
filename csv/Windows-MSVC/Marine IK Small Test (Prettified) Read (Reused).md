
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2273 | 0.161693 | 946.673ms | 18245 | 40 | 6128.21 | 7655 | 0.0217675 | 1.08538 | 1(Win) | true |
| Jsonifier | 1962.38 | 0.146435 | 1057.18ms | 18245 | 30 | 5057.47 | 8866.67 | 0.188324 | 1.25702 | 2(Loss) | true |
| simdjson (ondemand) | 745.834 | 0.107606 | 2511.82ms | 18245 | 4890 | 3.08168e+06 | 23329.3 | 0.0879622 | 3.31557 | 3(Loss) | true |
| Glaze | 641.529 | 0.119299 | 2905.76ms | 18245 | 2560 | 2.68023e+06 | 27122.4 | 0.315993 | 3.85534 | 4(Loss) | true |
