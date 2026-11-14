
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 396.029 | 0.788331 | 7747ms | 2090234 | 30 | 4.72361e+10 | 5.03348e+06 | 0.413372 | 7.67439 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 394.862 | 0.625497 | 7699.04ms | 2090234 | 80 | 7.97698e+10 | 5.04835e+06 | 2.08176 | 7.69693 | 1(Tie) | true |
