
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1817.31 | 0.186238 | 430.979ms | 7932 | 40 | 2403.85 | 4162.5 | 0.301205 | 1.34908 | 1(Win) | true |
| Jsonifier | 1611.43 | 0.229572 | 488.94ms | 7932 | 4890 | 567924 | 4694.31 | 0.32227 | 1.52723 | 2(Loss) | true |
| Glaze | 1369.69 | 0.627459 | 564.747ms | 7932 | 320 | 384274 | 5522.81 | 0.153009 | 1.79868 | 3(Loss) | true |
| simdjson (ondemand) | 1075.53 | 0.124461 | 736.752ms | 7932 | 30 | 2298.85 | 7033.33 | 0 | 2.29352 | 4(Loss) | true |
