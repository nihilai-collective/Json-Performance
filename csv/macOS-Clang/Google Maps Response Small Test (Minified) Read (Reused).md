
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2379.22 | 0.184928 | 192.375ms | 4390 | 30 | 317.678 | 1759.67 | 0.00378845 | 1(Win) | true |
| Jsonifier (two-stage) | 1378.89 | 0.127487 | 350.656ms | 4390 | 30 | 449.495 | 3036.23 | 0.00658754 | 2(Loss) | true |
| Glaze | 1113.35 | 0.265821 | 397.534ms | 4390 | 40 | 3996.76 | 3760.4 | 0.240801 | 3(Loss) | true |
| simdjson (ondemand) | 783.371 | 0.3022 | 542.008ms | 4390 | 2560 | 667763 | 5344.38 | 1.04477 | 4(Loss) | true |
