
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13686.3 | 0.125264 | 3277.25ms | 466906 | 320 | 531479 | 32534.4 | 0.33124 | 0.221787 | 1(Win) | true |
| simdjson (stage-1) | 11821 | 0.140763 | 3794.38ms | 466906 | 1280 | 3.59864e+06 | 37668.2 | 0.443731 | 0.25683 | 2(Loss) | true |
