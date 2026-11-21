
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3109.16 | 0.0397714 | 60.0219ms | 1691 | 640 | 27.2347 | 518.681 | 0.113741 | 0.755035 | 1(Win) | true |
| Jsonifier (two-stage) | 2836.53 | 0.18682 | 66.0371ms | 1691 | 30 | 33.8437 | 568.533 | 0.0058627 | 0.828208 | 2(Loss) | true |
| Glaze | 2376.22 | 0.168423 | 76.2869ms | 1691 | 30 | 39.1954 | 678.667 | 0.04914 | 1.00193 | 3(Loss) | true |
| simdjson (ondemand) | 1762.47 | 0.259633 | 99.3065ms | 1691 | 30 | 169.31 | 915 | 0.0619692 | 1.36929 | 4(Loss) | true |
