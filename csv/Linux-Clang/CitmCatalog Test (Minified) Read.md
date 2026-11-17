
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22393.8 | 0.105074 | 2130.97ms | 500299 | 4890 | 2.45079e+06 | 21306 | 0.0401698 | 0.110418 | 1(Win) | true |
| simdjson (stage-1) | 19285.8 | 0.180797 | 2484.55ms | 500299 | 640 | 1.28041e+06 | 24739.5 | 0.0879775 | 0.128241 | 2(Loss) | true |
