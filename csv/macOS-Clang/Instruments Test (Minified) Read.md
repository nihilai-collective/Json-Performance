
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2739.18 | 0.0948269 | 3781.52ms | 108313 | 2560 | 3.27357e+06 | 37710.2 | 0.0837146 | 1(Win) | true |
| Jsonifier (two-stage) | 1723.28 | 0.0685312 | 6025.92ms | 108313 | 4890 | 8.25155e+06 | 59941.1 | 0.103142 | 2(Loss) | true |
| Glaze | 1539.89 | 0.0900865 | 6750.31ms | 108313 | 1280 | 4.67424e+06 | 67079.7 | 0.0695644 | 3(Loss) | true |
| simdjson (ondemand) | 677.723 | 0.200104 | 7843.22ms | 108313 | 320 | 2.97659e+07 | 152415 | 0.0401353 | 4(Loss) | true |
