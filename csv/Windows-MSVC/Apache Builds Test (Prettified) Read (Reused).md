
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1466.6 | 0.214594 | 5081.58ms | 124597 | 640 | 1.93468e+07 | 81020.9 | 0.331374 | 1.68755 | 1(Win) | true |
| simdjson (ondemand) | 1419.87 | 0.130091 | 5317.36ms | 124597 | 1280 | 1.51714e+07 | 83687.4 | 0.529394 | 1.74316 | 2(Loss) | true |
| Jsonifier (two-stage) | 1356.77 | 0.206261 | 5939.31ms | 124597 | 320 | 1.04421e+07 | 87579.4 | 0.347317 | 1.82426 | 3(Loss) | true |
| Glaze | 1294.43 | 0.11111 | 5811.15ms | 124597 | 1280 | 1.33159e+07 | 91797.1 | 0.0805306 | 1.91205 | 4(Loss) | true |
