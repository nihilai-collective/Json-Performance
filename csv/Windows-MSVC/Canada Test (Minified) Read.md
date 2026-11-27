
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 389.739 | 1.1864 | 7575.67ms | 2090234 | 30 | 1.10466e+11 | 5.11472e+06 | 0.0226094 | 7.79751 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 386.456 | 1.17955 | 7630.07ms | 2090234 | 40 | 1.48075e+11 | 5.15817e+06 | 0.679192 | 7.86431 | 1(Tie) | true |
