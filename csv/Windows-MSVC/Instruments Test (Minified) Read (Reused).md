
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2624.31 | 0.040148 | 4207.64ms | 108313 | 1280 | 319646 | 39360.9 | 0.0635551 | 1.15738 | 1(Win) | true |
| Jsonifier (two-stage) | 1754.93 | 0.120536 | 6261.03ms | 108313 | 80 | 402684 | 58860 | 0.00424755 | 1.73132 | 2(Loss) | true |
| Glaze | 1594.34 | 0.058161 | 6745.58ms | 108313 | 640 | 908743 | 64788.6 | 0.197608 | 1.90561 | 3(Loss) | true |
| simdjson (ondemand) | 945.279 | 0.171165 | 5688.84ms | 108313 | 40 | 1.39936e+06 | 109275 | 0.0656268 | 3.21465 | 4(Loss) | true |
