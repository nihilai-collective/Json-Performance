
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 885.857 | 0.372129 | 6052.87ms | 108313 | 80 | 1.5063e+07 | 116605 | 0.532385 | 2.79414 | 1(Win) | true |
| simdjson (ondemand) | 787.057 | 0.66723 | 6951.21ms | 108313 | 40 | 3.06733e+07 | 131242 | 1.0536 | 3.14507 | 2(Loss) | true |
