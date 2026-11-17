
----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2458.12 | 0.479317 | 192.961ms | 4630 | 2560 | 189777 | 1796.3 | 0.921125 | 1(Win) | true |
| Glaze | 1943.7 | 0.462367 | 249.443ms | 4630 | 2560 | 282433 | 2271.7 | 3.17535 | 2(Loss) | true |
| simdjson (reflection) | 882.326 | 0.386164 | 495.405ms | 4630 | 640 | 239017 | 5004.4 | 0.0878454 | 3(Loss) | true |
