
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1496.24 | 0.0566291 | 326.649ms | 5094 | 40 | 135.225 | 3246.82 | 0.0720698 | 1.6418 | 1(Win) | true |
| simdjson (reflection) | 1473.67 | 0.10756 | 338.683ms | 5094 | 80 | 1005.8 | 3296.54 | 0.0793127 | 1.66671 | 2(Loss) | true |
| Jsonifier (two-stage) | 1377.1 | 0.135682 | 356.141ms | 5094 | 4890 | 112031 | 3527.71 | 0.0754977 | 1.78426 | 3(Loss) | true |
| Glaze | 1234.18 | 0.115369 | 413.378ms | 5094 | 30 | 618.668 | 3936.23 | 0.196002 | 1.99226 | 4(Loss) | true |
| simdjson (ondemand) | 1220.53 | 0.2506 | 402.949ms | 5094 | 30 | 2984.75 | 3980.27 | 0.0829778 | 2.0159 | 5(Loss) | true |
