
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13441.4 | 0.140421 | 770.144ms | 108313 | 640 | 74527.4 | 7684.84 | 0.15226 | 0.22535 | 1(Win) | true |
| Glaze | 3986.19 | 0.0919476 | 2594.59ms | 108313 | 4890 | 2.7761e+06 | 25913.3 | 0.130909 | 0.761727 | 2(Loss) | true |
