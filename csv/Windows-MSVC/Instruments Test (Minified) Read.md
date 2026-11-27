
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2023.99 | 0.558904 | 5257.25ms | 108313 | 640 | 5.20713e+07 | 51035.5 | 3.49784 | 1.50083 | -(Win) | false |
| Jsonifier (two-stage) STATISTICAL TIE | 1375.22 | 0.690822 | 7553.48ms | 108313 | 2560 | 6.89272e+08 | 75112 | 0.195507 | 2.20911 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1368.15 | 0.801311 | 7827.82ms | 108313 | 40 | 1.46405e+07 | 75500 | 0.365108 | 2.22109 | 2(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 857.36 | 0.597412 | 6060.39ms | 108313 | 2560 | 1.32624e+09 | 120481 | 2.75479 | 3.54376 | -(Loss) | false |
