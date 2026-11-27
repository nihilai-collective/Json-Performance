
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2121 | 0.170419 | 231.994ms | 5094 | 30 | 457.082 | 2290.43 | 0.090149 | 1.15434 | 1(Win) | true |
| Jsonifier (two-stage) | 1737.25 | 0.403389 | 281.857ms | 5094 | 640 | 81437.1 | 2796.38 | 0.0625081 | 1.4121 | 2(Loss) | true |
| Glaze | 1282.71 | 0.0523539 | 382.32ms | 5094 | 80 | 314.521 | 3787.31 | 0.0617573 | 1.91662 | 3(Loss) | true |
| simdjson (ondemand) | 906.966 | 0.12883 | 538.823ms | 5094 | 4890 | 232853 | 5356.34 | 0.00695095 | 2.71596 | 4(Loss) | true |
