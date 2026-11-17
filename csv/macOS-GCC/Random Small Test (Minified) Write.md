
----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11677.9 | 4.71228 | 46.154ms | 5094 | 640 | 245939 | 416 | 0.952381 | 1(Win) | true |
| simdjson (reflection) | 8045.74 | 1.65458 | 62.1481ms | 5094 | 2560 | 255506 | 603.8 | 0.165344 | 2(Loss) | true |
| Glaze | 1852.08 | 0.627873 | 239.425ms | 5094 | 1280 | 347176 | 2623 | 1.16476 | 3(Loss) | true |
