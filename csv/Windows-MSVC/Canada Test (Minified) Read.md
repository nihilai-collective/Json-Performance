
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 182.822 | 0.531655 | 7795.76ms | 2090234 | 30 | 1.00812e+11 | 1.09035e+07 | 1.06091 | 13.5421 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE DID NOT CONVERGE | 180.408 | 1.38695 | 7688.27ms | 2090234 | 40 | 9.39411e+11 | 1.10494e+07 | 12.4871 | 13.7232 | -(Tie) | false |
