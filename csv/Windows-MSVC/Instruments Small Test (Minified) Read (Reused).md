
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2338.53 | 0.108263 | 207.315ms | 4669 | 2560 | 10878.4 | 1904.06 | 0.0369413 | 1.28601 | 1(Win) | true |
| Jsonifier (two-stage) | 1573.44 | 0.120331 | 300.961ms | 4669 | 1280 | 14842.8 | 2829.92 | 0.11306 | 1.9207 | 2(Loss) | true |
| Glaze | 1458.11 | 0.0936849 | 321.771ms | 4669 | 320 | 2619.12 | 3053.75 | 0.0204625 | 2.07476 | 3(Loss) | true |
| simdjson (ondemand) | 914.72 | 0.0679715 | 502.257ms | 4669 | 4890 | 53534.5 | 4867.83 | 0.0421528 | 3.30961 | 4(Loss) | true |
