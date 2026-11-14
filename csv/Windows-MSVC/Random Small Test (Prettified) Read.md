
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1312.57 | 0.0854203 | 589.366ms | 8051 | 4890 | 122091 | 5849.61 | 0.0508125 | 2.30789 | 1(Win) | true |
| Jsonifier | 1176.94 | 0.138914 | 656.114ms | 8051 | 2560 | 210245 | 6523.75 | 0.0623113 | 2.57478 | 2(Loss) | true |
| Glaze | 974.969 | 0.112347 | 793.348ms | 8051 | 1280 | 100195 | 7875.16 | 0.0793006 | 3.10848 | 3(Loss) | true |
| simdjson (ondemand) | 855.552 | 0.0674782 | 899.736ms | 8051 | 4890 | 179326 | 8974.36 | 0.0720928 | 3.54383 | 4(Loss) | true |
