
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2365.95 | 0.0998897 | 194.449ms | 4390 | 160 | 499.898 | 1769.54 | 0.0127136 | 1(Win) | true |
| Jsonifier (two-stage) | 1434.88 | 0.044303 | 346.641ms | 4390 | 80 | 133.677 | 2917.76 | 0.0372856 | 2(Loss) | true |
| simdjson (ondemand) | 897.674 | 0.175977 | 488.109ms | 4390 | 30 | 2020.81 | 4663.87 | 0.058641 | 3(Loss) | true |
| Glaze | 819.136 | 2.05428 | 465.214ms | 4390 | 30 | 330719 | 5111.03 | 1.47342 | 4(Loss) | true |
