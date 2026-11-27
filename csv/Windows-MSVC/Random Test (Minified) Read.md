
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 881.751 | 0.417545 | 6359.85ms | 461466 | 640 | 2.77955e+09 | 499107 | 2.51861 | 3.44635 | -(Win) | false |
| Jsonifier (two-stage) | 723.746 | 0.590517 | 7920.18ms | 461466 | 80 | 1.03148e+09 | 608070 | 0.400814 | 4.19869 | 2(Loss) | true |
| Glaze | 706.041 | 0.2498 | 8000.67ms | 461466 | 640 | 1.55162e+09 | 623318 | 0.0715164 | 4.30438 | 3(Loss) | true |
| simdjson (ondemand) | 570.353 | 0.487653 | 5108.25ms | 461466 | 80 | 1.13267e+09 | 771606 | 0.507548 | 5.3281 | 4(Loss) | true |
