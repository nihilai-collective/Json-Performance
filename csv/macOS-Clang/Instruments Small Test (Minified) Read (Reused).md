
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2987.18 | 0.168391 | 165.097ms | 4669 | 4890 | 30808.7 | 1490.6 | 0.211851 | 1(Win) | true |
| Jsonifier (two-stage) | 1839.99 | 0.123959 | 262.579ms | 4669 | 1280 | 11518.1 | 2419.96 | 0.135794 | 2(Loss) | true |
| Glaze | 1468.47 | 0.66888 | 319.729ms | 4669 | 4890 | 2.01151e+06 | 3032.21 | 0.585475 | 3(Loss) | true |
| simdjson (ondemand) | 622.384 | 0.0837872 | 750.2ms | 4669 | 320 | 11498.4 | 7154.27 | 0.601977 | 4(Loss) | true |
