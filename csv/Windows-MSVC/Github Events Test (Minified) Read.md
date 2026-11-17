
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15404.2 | 0.159524 | 333.957ms | 53331 | 1280 | 35509.2 | 3301.72 | 0.0615589 | 0.195167 | 1(Win) | true |
| simdjson (stage-1) | 12826.6 | 0.090014 | 398.283ms | 53331 | 4890 | 62297 | 3965.24 | 0.00786023 | 0.234477 | 2(Loss) | true |
