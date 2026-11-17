
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1210.75 | 0.214896 | 4505.41ms | 56369 | 1280 | 1.16531e+07 | 44400.4 | 0.402972 | 2.04346 | 1(Win) | true |
| Glaze | 1012.89 | 0.135188 | 5500.1ms | 56369 | 30 | 154437 | 53073.3 | 1.25279 | 2.44408 | 2(Loss) | true |
| Jsonifier (two-stage) | 949.816 | 0.176586 | 5645.35ms | 56369 | 640 | 6.39281e+06 | 56598 | 0.00800667 | 2.60531 | 3(Loss) | true |
| simdjson (ondemand) | 699.518 | 0.140866 | 7702.54ms | 56369 | 4890 | 5.73066e+07 | 76849.5 | 0.290826 | 3.5379 | 4(Loss) | true |
