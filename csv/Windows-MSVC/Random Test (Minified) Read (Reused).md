
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 931.269 | 0.218316 | 6093.84ms | 409725 | 40 | 3.35635e+07 | 419582 | 0.0284093 | 3.26336 | 1(Win) | true |
| simdjson (ondemand) | 753.212 | 0.16128 | 7396.26ms | 409725 | 320 | 2.24007e+08 | 518770 | 0.0767453 | 4.03477 | 2(Loss) | true |
