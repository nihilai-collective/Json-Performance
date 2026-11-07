
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1632.71 | 0.410868 | 243.318ms | 3370 | 1280 | 83725.5 | 1968.44 | 0.655161 | 1.49169 | 1(Win) | true |
| Jsonifier (two-stage) | 1600.94 | 0.129147 | 238.618ms | 3370 | 160 | 1075.47 | 2007.5 | 0.124378 | 1.52978 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1437.98 | 0.341728 | 271.084ms | 3370 | 40 | 2333.33 | 2235 | 0.223214 | 1.71503 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1433.57 | 0.123212 | 265.313ms | 3370 | 320 | 2441.61 | 2241.88 | 0.0837054 | 1.70777 | 3(Tie) | true |
