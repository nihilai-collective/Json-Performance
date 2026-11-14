
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 2129.97 | 0.293255 | 200.724ms | 3808 | 40 | 1000 | 1705 | 0.294118 | 1.40526 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2126.85 | 0.385951 | 197.394ms | 3808 | 40 | 1737.18 | 1707.5 | 0.0488281 | 1.40894 | 1(Tie) | true |
| simdjson (ondemand) | 1931.7 | 0.340698 | 212.429ms | 3808 | 40 | 1641.03 | 1880 | 0.534759 | 1.5585 | 3(Loss) | true |
| Jsonifier | 1815.09 | 1.74374 | 228.737ms | 3808 | 640 | 779013 | 2000.78 | 0.16373 | 1.65636 | 4(Loss) | true |
