
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2898.33 | 0.261433 | 165.217ms | 4669 | 30 | 483.941 | 1536.3 | 0.067216 | 0.840822 | 1(Win) | true |
| Jsonifier (two-stage) | 2389.37 | 0.104144 | 236.766ms | 4669 | 40 | 150.664 | 1863.55 | 0.172312 | 1.02072 | 2(Loss) | true |
| Glaze | 1843.58 | 0.0492572 | 256.133ms | 4669 | 80 | 113.228 | 2415.25 | 0.0258705 | 1.32816 | 3(Loss) | true |
| simdjson (ondemand) | 649.001 | 0.129042 | 700.548ms | 4669 | 2560 | 200658 | 6860.86 | 0.142164 | 3.80009 | 4(Loss) | true |
