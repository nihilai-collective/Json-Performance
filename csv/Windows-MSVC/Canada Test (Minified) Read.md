
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 563.243 | 1.8975 | 5705.48ms | 2251027 | 40 | 2.09215e+11 | 3.8114e+06 | 3.99121 | 4.39534 | -(Win) | false |
| Jsonifier (two-stage) | 531.675 | 1.68938 | 6132.51ms | 2251027 | 80 | 3.72233e+11 | 4.0377e+06 | 1.55238 | 4.65645 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 183.661 | 1.06468 | 8293.07ms | 2251027 | 40 | 6.19473e+11 | 1.16886e+07 | 0.0662172 | 13.4802 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 183.319 | 1.4707 | 8255.26ms | 2251027 | 30 | 8.89847e+11 | 1.17105e+07 | 0.273138 | 13.5052 | 3(Tie) | true |
