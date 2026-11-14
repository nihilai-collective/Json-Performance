
----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13171.6 | 1.39817 | 70.198ms | 9255 | 2560 | 224718 | 670.1 | 1.28167 | 1(Win) | true |
| Glaze | 2458.29 | 0.913562 | 385.256ms | 9255 | 320 | 344280 | 3590.4 | 0.990099 | 2(Loss) | true |
| simdjson (reflection) | 307.107 | 0.329628 | 2820.36ms | 9255 | 1280 | 1.14877e+07 | 28740 | 0.501302 | 3(Loss) | true |
