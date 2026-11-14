
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 858.762 | 0.0731077 | 639.579ms | 4630 | 4890 | 69095.8 | 5141.72 | 0.275757 | 3.52567 | 1(Win) | true |
| Jsonifier (two-stage) | 799.47 | 0.112541 | 683.173ms | 4630 | 1280 | 49452.8 | 5523.05 | 0.0325447 | 3.78846 | 2(Loss) | true |
| simdjson (ondemand) | 395.488 | 0.0719236 | 1248.64ms | 4630 | 2560 | 165074 | 11164.7 | 0.0276324 | 7.66904 | 3(Loss) | true |
| Glaze | 386.773 | 0.0680164 | 1272.27ms | 4630 | 2560 | 154354 | 11416.3 | 0.180678 | 7.84346 | 4(Loss) | true |
