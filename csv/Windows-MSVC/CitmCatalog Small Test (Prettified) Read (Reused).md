
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1659.76 | 0.36893 | 438.647ms | 5839 | 40 | 6128.21 | 3355 | 0.641658 | 1.82484 | 1(Win) | true |
| Jsonifier (two-stage) | 1501.29 | 0.713368 | 458.549ms | 5839 | 1280 | 896156 | 3709.14 | 0.592546 | 2.01275 | 2(Loss) | true |
| simdjson (ondemand) | 1199.46 | 0.449769 | 550.964ms | 5839 | 80 | 34879.7 | 4642.5 | 0.588865 | 2.52154 | 3(Loss) | true |
| Glaze | 1187.63 | 0.156403 | 550.772ms | 5839 | 80 | 4302.22 | 4688.75 | 0.401499 | 2.54616 | 4(Loss) | true |
