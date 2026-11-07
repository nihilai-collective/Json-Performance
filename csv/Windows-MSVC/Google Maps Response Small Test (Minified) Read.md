
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1195.54 | 0.120026 | 359.14ms | 4390 | 160 | 2826.65 | 3501.88 | 0.0893176 | 2.04926 | 1(Win) | true |
| Jsonifier (two-stage) | 1038.38 | 0.169449 | 418.171ms | 4390 | 160 | 7468.16 | 4031.88 | 0.0464828 | 2.36569 | 2(Loss) | true |
| Glaze | 837.64 | 0.142783 | 518.935ms | 4390 | 320 | 16297.4 | 4998.12 | 0.162297 | 2.94041 | 3(Loss) | true |
| simdjson (ondemand) | 550.872 | 0.210695 | 791.381ms | 4390 | 40 | 10256.4 | 7600 | 0.0438404 | 4.47994 | 4(Loss) | true |
