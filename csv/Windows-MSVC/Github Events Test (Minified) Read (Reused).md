
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1207.8 | 0.186735 | 4920.45ms | 53331 | 160 | 989333 | 42110 | 0.0889732 | 2.51535 | 1(Win) | true |
| simdjson (ondemand) | 904.047 | 0.439872 | 6184.74ms | 53331 | 2560 | 1.56773e+08 | 56258.6 | 0.414461 | 3.36025 | 2(Loss) | true |
