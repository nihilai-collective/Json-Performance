
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9043.1 | 0.113726 | 37.3235ms | 3223 | 160 | 23.9069 | 339.894 | 0.0716622 | 0.252019 | 1(Win) | true |
| simdjson (reflection) | 8840.05 | 0.0537593 | 41.6362ms | 3223 | 1280 | 44.7228 | 347.701 | 0.108856 | 0.258181 | 2(Loss) | true |
| Glaze | 2649.42 | 0.168257 | 115.535ms | 3223 | 80 | 304.829 | 1160.14 | 0.273342 | 0.911856 | 3(Loss) | true |
