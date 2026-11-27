
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2491.72 | 0.136197 | 315.273ms | 7932 | 4890 | 83600.8 | 3035.88 | 0.956632 | 1(Win) | true |
| Jsonifier | 2387.95 | 0.21697 | 315.804ms | 7932 | 4890 | 231007 | 3167.8 | 0.0664523 | 2(Loss) | true |
| simdjson (reflection) | 2066.45 | 0.227281 | 370.067ms | 7932 | 4890 | 338494 | 3660.64 | 0.173575 | 3(Loss) | true |
| Glaze | 1971.06 | 0.231668 | 390.362ms | 7932 | 2560 | 202365 | 3837.8 | 0.378985 | 4(Loss) | true |
| simdjson (ondemand) | 1743.79 | 0.634061 | 442.588ms | 7932 | 640 | 484196 | 4338 | 0.21253 | 5(Loss) | true |
