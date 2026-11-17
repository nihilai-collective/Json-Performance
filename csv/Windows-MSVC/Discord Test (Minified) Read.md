
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 888.453 | 0.182828 | 6099.25ms | 56369 | 640 | 7.83211e+06 | 60507 | 0.017815 | 2.78529 | 1(Win) | true |
| simdjson (ondemand) | 787.309 | 0.0861703 | 6903.36ms | 56369 | 2560 | 8.86229e+06 | 68280.3 | 0.0427534 | 3.14341 | 2(Loss) | true |
