
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1258.47 | 0.0527873 | 865.182ms | 9739 | 4890 | 74218 | 7380.25 | 0.139915 | 2.40851 | 1(Win) | true |
| simdjson (ondemand) | 1143.2 | 0.065951 | 920.971ms | 9739 | 4890 | 140391 | 8124.44 | 0.0238551 | 2.65137 | 2(Loss) | true |
