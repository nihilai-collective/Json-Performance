
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11297.4 | 0.14099 | 3939.29ms | 461466 | 1280 | 3.86109e+06 | 38954.8 | 0.0818925 | 0.268755 | 1(Win) | true |
| simdjson (stage-1) | 10226.8 | 0.0856597 | 4339.92ms | 461466 | 320 | 434813 | 43032.8 | 0.424464 | 0.296877 | 2(Loss) | true |
