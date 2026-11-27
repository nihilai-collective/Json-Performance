
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2221.27 | 0.31141 | 6198.3ms | 466906 | 160 | 6.2351e+07 | 200461 | 0.0477254 | 1.36814 | 1(Win) | true |
| Glaze | 1611.5 | 0.558569 | 8047.3ms | 466906 | 1280 | 3.04904e+09 | 276312 | 0.225201 | 1.88566 | 2(Loss) | true |
| Jsonifier (two-stage) | 1531.8 | 0.265187 | 8837.59ms | 466906 | 160 | 9.5078e+07 | 290688 | 1.08485 | 1.98386 | 3(Loss) | true |
| simdjson (ondemand) | 1190.01 | 0.718063 | 5165.27ms | 466906 | 320 | 2.31011e+09 | 374179 | 0.924304 | 2.55336 | 4(Loss) | true |
