
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 188.269 | 1.34193 | 6601.5ms | 1834197 | 30 | 4.66353e+11 | 9.29112e+06 | 0.89479 | 13.1499 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 184.449 | 0.926331 | 6798.69ms | 1834197 | 40 | 3.08695e+11 | 9.48351e+06 | 0.434223 | 13.4221 | 1(Tie) | true |
