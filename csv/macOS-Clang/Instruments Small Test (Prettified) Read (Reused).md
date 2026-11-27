
----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3291.71 | 0.108009 | 249.073ms | 7932 | 4890 | 30126.4 | 2298.06 | 0.111138 | 1(Win) | true |
| Jsonifier (two-stage) | 2873.19 | 0.0895402 | 282.422ms | 7932 | 80 | 444.592 | 2632.8 | 0.0199447 | 2(Loss) | true |
| Glaze | 2010.16 | 0.0385285 | 396.394ms | 7932 | 640 | 1345.39 | 3763.15 | 0.0969822 | 3(Loss) | true |
| simdjson (ondemand) | 1105.13 | 0.176895 | 697.763ms | 7932 | 1280 | 187663 | 6844.92 | 0.040707 | 4(Loss) | true |
