
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 575.979 | 1.25467 | 763.216ms | 4630 | 80 | 740112 | 7666.1 | 0.0622484 | 1(Win) | true |
| Jsonifier (two-stage) | 546.61 | 0.390819 | 827.687ms | 4630 | 640 | 637880 | 8077.99 | 0.729163 | 2(Loss) | true |
| simdjson (ondemand) | 411.294 | 0.37449 | 1179.69ms | 4630 | 640 | 1.03447e+06 | 10735.7 | 0.350645 | 3(Loss) | true |
| Glaze | 391.746 | 0.278897 | 1104.42ms | 4630 | 2560 | 2.52977e+06 | 11271.4 | 0.386517 | 4(Loss) | true |
