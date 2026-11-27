
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2473.54 | 0.306326 | 282.265ms | 5839 | 4890 | 232549 | 2251.23 | 0.174852 | 1(Win) | true |
| Jsonifier (two-stage) | 2107.21 | 0.552948 | 324.36ms | 5839 | 1280 | 273301 | 2642.6 | 0.773506 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1803.04 | 0.23294 | 362.504ms | 5839 | 2560 | 132493 | 3088.4 | 0.416179 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1781.12 | 0.626487 | 399.94ms | 5839 | 320 | 122762 | 3126.4 | 0.256542 | 3(Tie) | true |
| Glaze | 1670.05 | 0.225929 | 390.713ms | 5839 | 4890 | 277506 | 3334.33 | 0.106817 | 5(Loss) | true |
