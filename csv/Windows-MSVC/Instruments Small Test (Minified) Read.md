
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1389.97 | 0.225738 | 323.209ms | 4669 | 4890 | 255715 | 3203.46 | 0.290414 | 1.76509 | 1(Win) | true |
| Jsonifier (two-stage) | 1010.26 | 0.112542 | 453.417ms | 4669 | 80 | 1968.35 | 4407.5 | 0.284414 | 2.43433 | 2(Loss) | true |
| Glaze | 901.966 | 0.265686 | 502.925ms | 4669 | 30 | 5160.92 | 4936.67 | 0.0674764 | 2.73216 | 3(Loss) | true |
| simdjson (ondemand) | 756.78 | 0.0977081 | 604.884ms | 4669 | 80 | 2643.99 | 5883.75 | 0.148494 | 3.25527 | 4(Loss) | true |
