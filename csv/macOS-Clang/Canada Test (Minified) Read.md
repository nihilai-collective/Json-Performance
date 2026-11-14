
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7236.69 | 0.4915 | 8053.12ms | 2251027 | 80 | 1.70067e+08 | 296647 | 1.22179 | 1(Win) | true |
| simdjson (stage-1) | 4951.49 | 0.566597 | 5606.74ms | 2251027 | 320 | 1.93103e+09 | 433556 | 1.96482 | 2(Loss) | true |
