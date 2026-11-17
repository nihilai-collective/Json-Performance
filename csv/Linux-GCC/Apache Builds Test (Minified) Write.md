
----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26345.3 | 0.0469157 | 350.637ms | 94653 | 40 | 103.362 | 3426.35 | 0.171028 | 0.0932282 | 1(Win) | true |
| simdjson (reflection) | 14755.1 | 0.225541 | 614.268ms | 94653 | 2560 | 487387 | 6117.75 | 0.356187 | 0.167066 | 2(Loss) | true |
| Glaze | 6280.48 | 0.0324774 | 1486.42ms | 94653 | 30 | 653.683 | 14372.8 | 0.116057 | 0.39347 | 3(Loss) | true |
