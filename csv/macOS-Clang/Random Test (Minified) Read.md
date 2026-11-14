
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (stage-1) | 6285.51 | 0.229595 | 7512.11ms | 461466 | 320 | 8.26942e+06 | 70016.3 | 0.139006 | 1(Win) | true |
| Jsonifier | 6076.21 | 0.253523 | 7333.26ms | 461466 | 80 | 2.69735e+06 | 72428.1 | 0.0302115 | 2(Loss) | true |
