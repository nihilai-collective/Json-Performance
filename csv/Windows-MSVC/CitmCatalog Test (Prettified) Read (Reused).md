
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1687.01 | 0.0712864 | 8797.9ms | 1151920 | 640 | 1.37912e+08 | 651184 | 0.168149 | 1.80144 | 1(Win) | true |
| simdjson (ondemand) | 1443.55 | 0.176281 | 5037.53ms | 1151920 | 160 | 2.87945e+08 | 761009 | 0.1445 | 2.10527 | 2(Loss) | true |
