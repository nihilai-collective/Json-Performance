
----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2356.7 | 0.396763 | 190.58ms | 4630 | 2560 | 141467 | 1873.6 | 0.159864 | 1(Win) | true |
| simdjson (reflection) | 2114.91 | 0.287764 | 212.477ms | 4630 | 2560 | 92404.1 | 2087.8 | 0.230437 | 2(Loss) | true |
| Glaze | 1492.69 | 0.435274 | 291.694ms | 4630 | 2560 | 424415 | 2958.1 | 0.986618 | 3(Loss) | true |
