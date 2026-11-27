
----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12196.9 | 2.44035 | 45.355ms | 5094 | 2560 | 241861 | 398.3 | 2.23368 | 1(Win) | true |
| simdjson (reflection) | 8532.94 | 1.3644 | 61.3379ms | 5094 | 4890 | 295063 | 569.325 | 0.640826 | 2(Loss) | true |
| Glaze | 1878.73 | 0.47063 | 263.383ms | 5094 | 2560 | 379130 | 2585.8 | 1.12632 | 3(Loss) | true |
