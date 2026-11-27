
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1140.5 | 0.195444 | 542.985ms | 5839 | 80 | 7284.81 | 4882.5 | 0.0512295 | 2.14719 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1139.34 | 0.168276 | 512.494ms | 5839 | 80 | 5411.39 | 4887.5 | 0.205023 | 2.14708 | 1(Tie) | true |
| simdjson (ondemand) | 787.068 | 0.344658 | 729.476ms | 5839 | 1280 | 761095 | 7075 | 0.0882613 | 3.13389 | 3(Loss) | true |
| Glaze | 762.213 | 0.274777 | 756.711ms | 5839 | 1280 | 515816 | 7305.7 | 0.00748615 | 3.22621 | 4(Loss) | true |
