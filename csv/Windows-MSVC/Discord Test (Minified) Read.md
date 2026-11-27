
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1271.86 | 0.216957 | 4322.95ms | 56369 | 640 | 5.38181e+06 | 42266.9 | 0.177017 | 1.94523 | 1(Win) | true |
| Jsonifier (two-stage) | 966.012 | 0.272768 | 5689.58ms | 56369 | 320 | 7.37317e+06 | 55649.1 | 0.116377 | 2.56142 | 2(Loss) | true |
| Glaze | 940.05 | 0.252721 | 5842.52ms | 56369 | 640 | 1.33672e+07 | 57185.9 | 0.551123 | 2.63239 | 3(Loss) | true |
| simdjson (ondemand) | 740.55 | 0.282783 | 7517.55ms | 56369 | 320 | 1.34843e+07 | 72591.6 | 0.398928 | 3.34197 | 4(Loss) | true |
