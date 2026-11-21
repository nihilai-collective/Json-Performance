
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2363.46 | 0.0938513 | 177.596ms | 4390 | 40 | 110.554 | 1771.4 | 0.0414157 | 1.03169 | 1(Win) | true |
| Jsonifier (two-stage) | 1903.29 | 0.0404112 | 224.772ms | 4390 | 320 | 252.856 | 2199.68 | 0.0847414 | 1.28457 | 2(Loss) | true |
| Glaze | 1629.58 | 0.18925 | 258.916ms | 4390 | 4890 | 115600 | 2569.15 | 0.0689975 | 1.50347 | 3(Loss) | true |
| simdjson (ondemand) | 1007.08 | 0.137003 | 418.13ms | 4390 | 4890 | 158624 | 4157.19 | 0.0685211 | 2.44225 | 4(Loss) | true |
