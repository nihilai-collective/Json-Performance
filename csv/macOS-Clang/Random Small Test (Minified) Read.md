
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1148.34 | 1.36947 | 407.809ms | 5094 | 160 | 537028 | 4230.46 | 0.699075 | 1(Win) | true |
| Jsonifier (two-stage) | 1036.21 | 0.133373 | 489.405ms | 5094 | 4890 | 191192 | 4688.26 | 0.714013 | 2(Loss) | true |
| Glaze | 799.686 | 0.181827 | 622.558ms | 5094 | 4890 | 596632 | 6074.91 | 2.05595 | 3(Loss) | true |
| simdjson (ondemand) | 639.406 | 0.334634 | 812.037ms | 5094 | 160 | 103425 | 7597.7 | 0.541135 | 4(Loss) | true |
