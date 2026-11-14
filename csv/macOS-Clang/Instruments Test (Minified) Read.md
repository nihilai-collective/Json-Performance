
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1133.41 | 0.122321 | 9592.33ms | 108313 | 2560 | 3.18152e+07 | 91137.2 | 0.288918 | 1(Win) | true |
| simdjson (ondemand) | 870.044 | 0.518075 | 5894.45ms | 108313 | 640 | 2.42127e+08 | 118724 | 1.65992 | 2(Loss) | true |
