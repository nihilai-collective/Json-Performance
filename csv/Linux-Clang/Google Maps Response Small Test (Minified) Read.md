
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2296.94 | 0.103334 | 193.313ms | 4390 | 30 | 106.424 | 1822.7 | 0.386206 | 1.06172 | 1(Win) | true |
| Jsonifier (two-stage) | 1805.51 | 0.266653 | 240.498ms | 4390 | 1280 | 48936.4 | 2318.81 | 0.265493 | 1.35454 | 2(Loss) | true |
| Glaze | 1604.3 | 0.0988465 | 268.679ms | 4390 | 30 | 199.62 | 2609.63 | 0.242103 | 1.52623 | 3(Loss) | true |
| simdjson (ondemand) | 936.592 | 0.565148 | 477.885ms | 4390 | 30 | 19145.8 | 4470.07 | 1.62707 | 2.62604 | 4(Loss) | true |
