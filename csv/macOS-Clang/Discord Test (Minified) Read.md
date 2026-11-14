
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1267.5 | 0.0316975 | 4279ms | 56369 | 30 | 5421.98 | 42412.5 | 0.0719646 | 1(Win) | true |
| simdjson (ondemand) | 1021.45 | 0.0625557 | 5333.27ms | 56369 | 2560 | 2.77476e+06 | 52629 | 0.0398607 | 2(Loss) | true |
