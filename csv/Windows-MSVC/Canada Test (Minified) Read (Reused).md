
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 198.42 | 0.438934 | 7752.85ms | 2090234 | 40 | 7.77815e+10 | 1.00464e+07 | 0.120859 | 12.4776 | 1(Win) | true |
| simdjson (ondemand) | 194.24 | 0.663998 | 7725.99ms | 2090234 | 40 | 1.85741e+11 | 1.02626e+07 | 1.62674 | 12.7463 | 2(Loss) | true |
