
----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 617.828 | 0.0675539 | 9108.64ms | 56369 | 1280 | 4.42239e+06 | 87010.8 | 0.178509 | 1(Win) | true |
| simdjson (ondemand) | 159.893 | 0.0762131 | 8773.45ms | 56369 | 640 | 4.20205e+07 | 336210 | 0.222223 | 2(Loss) | true |
