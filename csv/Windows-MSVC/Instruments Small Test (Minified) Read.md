
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1477.67 | 0.307437 | 309.783ms | 4669 | 30 | 2574.71 | 3013.33 | 0 | 1.66613 | 1(Win) | true |
| Jsonifier (two-stage) | 1090.46 | 0.169481 | 418.256ms | 4669 | 30 | 1436.78 | 4083.33 | 0.163532 | 2.24638 | 2(Loss) | true |
| Glaze | 924.637 | 0.0912225 | 496.417ms | 4669 | 160 | 3087.66 | 4815.62 | 0.0649351 | 2.66145 | 3(Loss) | true |
| simdjson (ondemand) | 807.564 | 0.10071 | 571.149ms | 4669 | 80 | 2466.77 | 5513.75 | 0.0226757 | 3.0495 | 4(Loss) | true |
